/* ROM6 0x2A8A FRAG_2A73 seg2 -- 66w (span 2A8A-2ACB, single entry).
 * Verified encoding: src/rom6/boot/2a8a_frag_2a73.asm (recombine MATCH).
 * ORIGIN 0x2A8A
 * EXPECT: F074 05B8 F495 7592 0030 F495 F495 7593 0031 F495 F495 7593 0032 F495 F495 7582 0004 EC14 F495 7192 058E 60E3 FFFF 4180 F820 2AC0 E800 12F8 3F00 0AE3 FFFE F844 2AB2 6DEB FFFE 56F8 3F04 4E83 F073 2ABD 12F8 3F02 0AE3 FFFE F844 2AC0 6DEB FFFE 56F8 3F06 4E83 6D8A 6B8A 0032 10F8 13D0 F030 FFFE F844 2979 7312 265E 7313 2660 F073 2979
 *
 * Intent: Boot port-strobe plus trim-compare tail (second half of
 * the FRAG_2A73 fragment; seg1 2A73-2A89 ends with its own bd to
 * dark 0x2979, so this span is a separately-entered mid-entry,
 * named frag_2A8A per the 5371 entry-address convention; no
 * fall-through from seg1). Entry AR2/AR3 live (cursor pair);
 * entry A/B unread (A recomputed, B untouched in-span).
 * Runs dark SUB_05B8 (call, forward extern void); settle nop;
 * *AR2++ out to port 48; settles; *AR3++ out to ports 49, 50
 * (portw pair with settle nops); *AR2 (no step) out to port 4;
 * 21 settle cycles (rpt #20, 2a5f precedent); cell 0x58E =
 * *AR2++ (mvdk); TC = (*(AR3-1) == 16768) (cmpm with -1
 * offset, equality per the 5362 precedent); clear detours to
 * dark 0x2AC0 (bc ntc). Else A = 0 (ld); A = *(0x3F00)
 * unsigned (ldu absolute); A -= unsigned *(AR3-2) (subs with
 * -2 offset, zero-extend regardless of SXM per the
 * op_subs_smem leaf; TI-int (unsigned) idiom per the ldu
 * precedent); nonzero runs dark 0x2AB2 (bc aneq). Else AR3 -=
 * 2 (mar +(-2)); A = 32-bit *(0x3F04) (dld absolute,
 * high-first per op_dld_long32 and the 2a1c precedent, SXM dark,
 * sign-extended form assumes SXM = 1, flagged); 32-bit store
 * to *AR3 (dst, high first per op_dst_long32 and the 2a1c/3d79
 * precedent, no step); joins the L2ABD tail (b). Second lane
 * (bc target 0x2AB2): same shape from *(0x3F02) with the
 * AR3 -= 2 / dld *(0x3F06) / dst sequence; nonzero runs dark
 * 0x2AC0; else falls into the shared tail. L2ABD tail: AR2--
 * (mar); MEM[AR2] += 50 then AR2-- (addm with post-step, RMW
 * then step); A = *(0x13D0) signed (ld); A &= -2 (and, 2bed
 * precedent); nonzero runs dark 0x2979 (bc aneq). Else cell
 * 0x265E = AR2, cell 0x2660 = AR3 (mvmd pair, 2a73 precedent);
 * runs dark 0x2979 (b). AR2/AR3 net zero (entry values
 * stored); void.
 */
extern void sub_05B8(void);                              /* dark, no symbol */
extern void port_write_48(int v);
extern void port_write_49(int v);
extern void port_write_50(int v);
extern void port_write_4(int v);
extern void frag_2AC0(void);                             /* dark */
extern void frag_2AB2(void);                             /* dark */
extern void frag_2ABD(void);                             /* dark */
extern void frag_2979(void);                             /* dark */

void frag_2A8A(int *ar2_in, int *ar3_in)
{
    long a;
    int tc;
    int i;
    int *ar2 = ar2_in;
    int *ar3 = ar3_in;
    sub_05B8();                                          /* call 0x5b8 */
    /* nop (settle) */
    port_write_48(*ar2++);                               /* portw *ar2+,48 */
    /* nop; nop */
    port_write_49(*ar3++);                                /* portw *ar3+,49 */
    /* nop; nop */
    port_write_50(*ar3++);                                /* portw *ar3+,50 */
    /* nop; nop */
    port_write_4(*ar2);                                  /* portw *ar2,pa4 */
    for (i = 0; i < 21; i++) {}                          /* rpt #20; nop */
    *(volatile int *)0x58E = *ar2++;                     /* mvdk *ar2+,0x58e */
    tc = (*(ar3 - 1) == 16768);                          /* cmpm *ar3(0xffff),#16768 */
    if (!tc) {                                           /* bc 0x2ac0,ntc */
        frag_2AC0();
        return;
    }
    a = 0;                                               /* ld #0,a */
    a = (long)(unsigned)*(volatile int *)0x3F00;         /* ldu *(0x3f00),a */
    a -= (long)(unsigned)*(ar3 - 2);                     /* subs *ar3(0xfffe),a */
    if (a != 0) {                                        /* bc 0x2ab2,aneq */
        a = (long)(unsigned)*(volatile int *)0x3F02;     /* ldu *(0x3f02),a */
        a -= (long)(unsigned)*(ar3 - 2);                 /* subs *ar3(0xfffe),a */
        if (a != 0) {                                    /* bc 0x2ac0,aneq */
            frag_2AC0();
            return;
        }
        ar3 -= 2;                                        /* mar *+ar3(0xfffe) */
        a = ((long)*(volatile int *)0x3F06 << 16) |      /* dld *(0x3f06),a */
            ((unsigned)*(volatile int *)0x3F07 & 0xFFFF);
    } else {
        ar3 -= 2;                                        /* mar *+ar3(0xfffe) */
        a = ((long)*(volatile int *)0x3F04 << 16) |      /* dld *(0x3f04),a */
            ((unsigned)*(volatile int *)0x3F05 & 0xFFFF);
    }
    *ar3 = (int)((a >> 16) & 0xFFFF);                    /* dst a,*ar3 (high) */
    *(ar3 + 1) = (int)(a & 0xFFFF);                      /* dst (low) */
    /* L2ABD shared tail (b 0x2abd joins here) */
    ar2--;                                               /* mar *ar2- */
    *ar2 += 50;                                          /* addm #50,*ar2- (RMW) */
    ar2--;                                               /* (post-step) */
    a = (long)*(volatile int *)0x13D0;                   /* ld *(0x13d0),a */
    a &= -2L;                                            /* and #-2,a */
    if (a != 0) {                                        /* bc 0x2979,aneq */
        frag_2979();
        return;
    }
    *(volatile int *)0x265E = (int)(long)ar2;            /* mvmd ar2,0x265e */
    *(volatile int *)0x2660 = (int)(long)ar3;            /* mvmd ar3,0x2660 */
    frag_2979();                                         /* b 0x2979 */
}
