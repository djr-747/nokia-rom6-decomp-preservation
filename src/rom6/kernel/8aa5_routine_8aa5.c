/* ROM6 0x8AA5 ROUTINE_8AA5 -- 36w gate + RPTBD retry lane.
 * Verified encoding: src/rom6/kernel/8aa5_routine_8aa5.asm (recombine MATCH).
 * ORIGIN 0x8AA5
 * EXPECT: 10E5 0003 F110 000F FA4F 8AB0 762C 0000 F45D 086F 802C 102C 11E5 0003 F523 812D FA4D 8ACA 7629 0008 771A 0002 F072 8AC5 016E FA4E 8AC6 112D F495 F761 016F 086F 812D F273 8ACE F6BF
 *
 * Intent: Threshold gate plus a 3-pass retry loop that
 * always transfers out via BD. A = AR5[3]; B = A - 15
 * (SUB #lk,src,dst); BCD delays run always (cell 0x2C =
 * 0; A >>= 3), branching to 8AB0 when B <= 0; else
 * A -= cell 0x6F << 16, cell 0x2C = AL, A = cell 0x2C
 * (reload, sign per SXM dark, flagged), B = AR5[3],
 * B -= A << 3, cell 0x2D = BL. At 8AB0: BCD delay (cell
 * 0x29 = 8, fills both delay words) runs always, branching
 * out to 8ACA (next-span +1 join, exterior transfer) when
 * issue-time B == 0; else fall through (BRC = 2) to the
 * RPTBD block 8ABD-8AC5 x3: B += cell
 * 0x6E << 16; BCD delays run always (B = cell 0x2D; NOP),
 * B-issue > 0 abandons the block for the BD (taken path
 * skips sfta/add/sub/stl); else B <<= 1, B += cell 0x6F
 * << 16, A -= cell 0x6F << 16, cell 0x2D = BL; block end.
 * Exit BD to 0x8ACE (mid-8AC9-span join at +5, past the
 * 3 head stores -- asm-owned, provisional join extern;
 * delays: RSBX BRAF then the shared 8AC9 head word run,
 * then transfer). In AR5 (dark, flagged); out cells.
 * (Wave-13: EXPECT from the image; BCD = issue-time
 * condition + 2 delay words; BD = 2 delay words.)
 */
extern void frag_8ACA(void); /* joins 8AC9 span at 8ACA (st #-4 word), asm-verified, no C entry yet */
extern void frag_8ACE(void); /* joins 8AC9 span at 8ACE (past 3 head stores), asm-verified, no C entry yet */

void routine_8AA5(void)
{
    long a;
    long b;
    int *ar5;  /* live-in (dark, flagged) */
    long b_issue;
    int i;

    a = (long)*(ar5 + 3);                                      /* ld *ar5(0x3),a */
    b = a - 15;                                                /* sub #15,a,b */
    { long bcd = b;
    *(volatile int *)0x2C = 0;                                 /* bcd delays: st #0,0x2c */
    a >>= 3;                                                   /* ld a,-3,a */
    if (bcd <= 0)                                              /* bcd 0x8ab0,bleq (issue-time B) */
        goto l8ab0; }
    a -= (long)*(volatile int *)0x6F << 16;                    /* sub 0x6f,a */
    *(volatile int *)0x2C = (int)(a & 0xFFFFL);                /* stl a,0x2c */
l8ab0:
    a = (long)*(volatile int *)0x2C;                           /* ld 0x2c,a (8AB0 join) */
    b = (long)*(ar5 + 3);                                      /* ld *ar5(0x3),b */
    b -= a << 3;                                               /* sub a,3,b */
    *(volatile int *)0x2D = (int)(b & 0xFFFFL);                /* stl b,0x2d */
    { long bcd = b;
    *(volatile int *)0x29 = 8;                                 /* bcd delay: st #8,0x29 (fills both delay words) */
    if (bcd == 0) {                                            /* bcd 0x8aca,beq (issue-time B) */
        frag_8ACA();                                           /* (exterior transfer to 8AC9+1, not a call) */
        return;
    } }
    /* stm #2,brc (fall-through instruction, not a delay) */
    for (i = 0; i < 3; i++) {                                  /* rptbd 0x8ac5 */
        b += (long)*(volatile int *)0x6E << 16;                /* add 0x6e,b */
        b_issue = b;
        b = (long)*(volatile int *)0x2D;                       /* bcd delays: ld 0x2d,b */
        /* nop */
        if (b_issue > 0)                                       /* bcd 0x8ac6,bgt (issue-time B) */
            break;                                             /* (abandons block for the BD) */
        b <<= 1;                                               /* sfta b,1 */
        b += (long)*(volatile int *)0x6F << 16;                /* add 0x6f,b */
        a -= (long)*(volatile int *)0x6F << 16;                /* sub 0x6f,a */
        *(volatile int *)0x2D = (int)(b & 0xFFFFL);           /* stl b,0x2d */
    }
    /* bd 0x8ace (delays run, then transfer): */
    /* rsbx st1,braf (BRAF off, no C form, flagged) */
    /* (shared 8AC9 head word runs as delay 2) */
    frag_8ACE();                                               /* (transfer, not a call) */
    /* (transfer, no return) */
    (void)i;
}
