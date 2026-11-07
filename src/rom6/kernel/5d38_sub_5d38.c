/* ROM6 ORIGIN 0x5D38 (188w): SUB_5D38 -- init lanes plus flag epilogue.
 * Verified encoding: src/rom6/kernel/5d38_sub_5d38.asm (recombine MATCH).
 * ORIGIN 0x5D38
 * EXPECT: F074 0598 61F8 2628 0001 FA20 5D7C 4A16 4A17 E800 61F8 058F 000F F820 5D49 80F8 2453 61F8 3EB5 0200 F820 5D50 80F8 0586 80F8 2629 80F8 0535 68F8 054F 7FFB 68F8 054F FEFF 80F8 056C 7711 051E 6881 FBFF 80F8 053C 80F8 050F 80F8 2614 80F8 2634 68F8 2627 FF7E 68F8 054F FFF7 6881 FFF7 7711 2633 EC02 8091 80F8 050B 68F8 051D F8FF 68F8 054F FF9F 61F8 2628 E000 F920 5DF4 F074 5E7D F074 69BE F074 69E4 F074 5EF7 61F8 2628 C000 F920 5F4B 7711 2629 F020 EE80 1889 1A81 8091 F074 05A4 10F8 0535 80F8 0534 61F8 3EB5 0200 F820 5DE3 61F8 054F 0008 F820 5DAA 60F8 0586 0000 F830 5DDC 10F8 250F F010 0019 F846 5DDC 61F8 0586 0002 F830 5DBD 60F8 262A 0060 F820 5DDC 69F8 0586 0002 76F8 262A 0060 76F8 0535 0000 F274 6155 7681 0000 61F8 0586 0004 F820 5DE3 61F8 0586 0001 68F8 0586 FFFE F830 5DD7 76F8 0586 0000 76F8 262A 0000 F073 5DE3 76F8 0535 0000 F274 6155 7681 0000 61F8 3EB5 0200 F830 5DEF 76F8 0535 0000 F274 6155 7681 0000 F074 640F 8A17 8A16 FC00
 *
 * Intent: Zero-init lane block, two conditional calls, RMW lane, flag
 * epilogue with shared tail. Runs dark SUB_0598 (opaque, forward
 * extern void per the 5e7d precedent; A rewritten at 5D41 before
 * first read, outputs dead). BITF bit 0 of cell 0x2628 plus bcd
 * 0x5D7C,ntc: the two 1-word pshm delays (ar6, ar7) fill the 2-word
 * window, so the bcd fires after them; NTC-taken jumps to 5D7C,
 * TC-fallthrough continues at 5D41 (word-count rule, no divergence
 * beyond the target). The pshm/popm pair balances with net SP zero
 * (AR6/AR7 never touched in-span, caller-live, preserved: modeled as
 * comments only, no params, per the dead-lane precedent).
 * 5D41 lane (A = 0): cell 0x58F bits 0-3 set stores A to 0x2453
 * (bc ntc skips); cell 0x3EB5 bit 9 set stores A to 0x586; then
 * A to 0x2629/0x535, cell 0x54F &= 0x7FFB then &= ~257 (andm pair:
 * clears bits 2+15, then bit 8), A to 0x56C, AR1 = 0x051E,
 * *(0x051E) &= ~1025 (andm indirect), A to 0x53C/0x50F/0x2614/
 * 0x2634, cell 0x2627 &= ~130, cell 0x54F &= ~9, *(0x051E) &= ~9
 * (andm; AR1 still 0x051E), AR1 = 0x2633, rpt #2 + stl *ar1+ x3
 * zeroes 0x2633-0x2635 (RPT #k runs k+1), A to 0x50B,
 * cell 0x51D &= ~1793, cell 0x54F &= ~97. 5D7C join: cell 0x2628
 * & 0xE000 clear calls ROUTINE_5DF4 (bitf #-8192 mask test, cc ntc:
 * call iff NTC; asm-only, forward extern void; no delays); then
 * SUB_5E7D (linked C, void), SUB_69BE, SUB_69E4, SUB_5EF7 (asm-only,
 * forward externs void). Cell 0x2628 & 0xC000 clear calls SUB_5F4B
 * (bitf #-16384 mask test, cc ntc; asm-only, forward extern void). AR1 = 0x2629; A = -4480;
 * A &= *(AR1--) (AR1 0x2629->0x2628); A |= *(AR1); *AR1++ = A-low
 * (AR1 back to 0x2629). SUB_05A4 (asm-only, no symbol, forward
 * extern void sub_05A4 per the sub_0598 naming pattern). A =
 * *(0x535); *(0x534) = A-low. Cell 0x3EB5 bit 9 clear chains to
 * 5DE3 (bc ntc); cell 0x54F bit 3 clear chains to 5DAA; cell
 * 0x586 == 0 chains to 5DDC (cmpm equal-sets-TC, bc tc); A =
 * *(0x250F) - 25, A > 0 chains to 5DDC (bc agt, full-40 signed,
 * exact on small A); cell 0x586 bit 1 set chains to 5DBD (bc tc,
 * skipping the cmpm); cell 0x262A != 96 chains to 5DDC (bc ntc),
 * else cell 0x586 |= 2 (orm). 5DBD: *(0x262A) = 96; *(0x535) = 0;
 * calld SUB_6155 (asm-only, forward extern void; single 2-word
 * st #0,*ar1 delay fills the window, fires, return address is the
 * next word). Cell 0x586 bit 2 clear chains to 5DE3 (bc ntc).
 * Cell 0x586 bit 0 read to TC, cell &= ~2 (andm runs
 * unconditionally, then bc tests the saved TC); TC set chains to
 * 5DD7, else *(0x586) = 0, *(0x262A) = 0 (fallthrough), jump 5DE3.
 * 5DDC: *(0x535) = 0; calld SUB_6155 (delay *ar1 = 0). 5DE3 join:
 * cell 0x3EB5 bit 9 set chains to 5DEF (bc tc, skipping the
 * st+calld); else *(0x535) = 0; calld SUB_6155 (delay *ar1 = 0).
 * 5DEF: SUB_640F (asm-only, no symbol, forward extern void
 * sub_640F); popm ar7/ar6 (balance the head pshms); return (ret,
 * no delay). No params (AR1 set on all paths before use; AR6/AR7
 * preserved-not-read; A/B rewritten after the dark head call) and
 * void (A/B live-outs are the tail stores, consumed in memory).
 * Bound 5D38-5DF3 (ret FC00@5DF3; next span at 5DF4 is the cc
 * target ROUTINE_5DF4). Entry call F074@5C93 (per header evidence).
 */
extern void sub_0598(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void routine_5DF4(void); /* joins 5df4_routine_5df4; see docs/evidence/extern-triage.md */
extern void sub_5E7D(void);
extern void sub_69BE(void); /* joins 69be_sub_69be; see docs/evidence/extern-triage.md */
extern void sub_69E4(void); /* joins 69e4_sub_69e4; see docs/evidence/extern-triage.md */
extern void sub_5EF7(void); /* joins 5ef7_sub_5ef7; see docs/evidence/extern-triage.md */
extern void sub_5F4B(void); /* joins 5f4b_sub_5f4b; see docs/evidence/extern-triage.md */
extern void sub_05A4(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_6155(void); /* joins 6155_sub_6155; see docs/evidence/extern-triage.md */
extern void sub_640F(void); /* joins 63da_cmpd_63da interior @+0x35; see docs/evidence/extern-triage.md */

void sub_5D38(void)
{
    long a;
    int i;
    int *ar1;

    sub_0598();                                            /* call 0x598 */
    /* pshm ar6/ar7 (bcd delays, balanced by popm; caller-live, noted) */
    if ((*(volatile int *)0x2628 & 1) == 0)               /* bcd taken */
        goto lane_5D7C;
    a = 0;                                                /* ld #0,a */
    if ((*(volatile int *)0x058F & 15) != 0)              /* bitf; bc fall */
        *(volatile int *)0x2453 = (int)(a & 0xFFFF);      /* stl (bit set) */
    if ((*(volatile int *)0x3EB5 & 512) == 0)             /* bitf; bc ntc */
        goto lane_5D50;
    *(volatile int *)0x0586 = (int)(a & 0xFFFF);          /* stl a,0x586 */
lane_5D50:                                                /* 5D50 zero lane */
    *(volatile int *)0x2629 = (int)(a & 0xFFFF);          /* stl a,0x2629 */
    *(volatile int *)0x0535 = (int)(a & 0xFFFF);          /* stl a,0x535 */
    *(volatile int *)0x054F &= 0x7FFB;                    /* andm #32763 */
    *(volatile int *)0x054F &= 0xFEFF;                    /* andm #-257 */
    *(volatile int *)0x056C = (int)(a & 0xFFFF);          /* stl a,0x56c */
    ar1 = (int *)0x051E;                                  /* stm #1310,ar1 */
    *ar1 &= 0xFBFF;                                       /* andm #-1025,*ar1 */
    *(volatile int *)0x053C = (int)(a & 0xFFFF);          /* stl a,0x53c */
    *(volatile int *)0x050F = (int)(a & 0xFFFF);          /* stl a,0x50f */
    *(volatile int *)0x2614 = (int)(a & 0xFFFF);          /* stl a,0x2614 */
    *(volatile int *)0x2634 = (int)(a & 0xFFFF);          /* stl a,0x2634 */
    *(volatile int *)0x2627 &= 0xFF7E;                    /* andm #-130 */
    *(volatile int *)0x054F &= 0xFFF7;                    /* andm #-9 */
    *ar1 &= 0xFFF7;                                       /* andm #-9,*ar1 */
    ar1 = (int *)0x2633;                                  /* stm #9779,ar1 */
    for (i = 0; i < 3; i++)                               /* rpt #2 */
        *ar1++ = (int)(a & 0xFFFF);                       /* stl a,*ar1+ */
    *(volatile int *)0x050B = (int)(a & 0xFFFF);          /* stl a,0x50b */
    *(volatile int *)0x051D &= 0xF8FF;                    /* andm #-1793 */
    *(volatile int *)0x054F &= 0xFF9F;                    /* andm #-97 */
lane_5D7C:                                                /* 5D7C join */
    if ((*(volatile int *)0x2628 & 0xE000) == 0)          /* bitf; cc ntc */
        routine_5DF4();                                   /* cc 0x5df4,ntc */
    sub_5E7D();                                           /* call 0x5e7d */
    sub_69BE();                                           /* call 0x69be */
    sub_69E4();                                           /* call 0x69e4 */
    sub_5EF7();                                           /* call 0x5ef7 */
    if ((*(volatile int *)0x2628 & 0xC000) == 0)          /* bitf; cc ntc */
        sub_5F4B();                                       /* cc 0x5f4b,ntc */
    ar1 = (int *)0x2629;                                  /* stm #9769,ar1 */
    a = -4480L;                                           /* ld #-4480,a */
    a &= (long)*ar1--;                                    /* and *ar1-,a */
    a |= (long)*ar1;                                      /* or *ar1,a */
    *ar1++ = (int)(a & 0xFFFF);                           /* stl a,*ar1+ */
    sub_05A4();                                           /* call 0x5a4 */
    a = (long)*(volatile int *)0x0535;                    /* ld *(0x535),a */
    *(volatile int *)0x0534 = (int)(a & 0xFFFF);          /* stl a,0x534 */
    if ((*(volatile int *)0x3EB5 & 512) == 0)             /* bitf; bc ntc */
        goto tail_5DE3;
    if ((*(volatile int *)0x054F & 8) == 0)               /* bitf; bc ntc */
        goto lane_5DAA;
    if (*(volatile int *)0x0586 == 0)                     /* cmpm; bc tc */
        goto lane_5DDC;
    a = (long)*(volatile int *)0x250F;                    /* ld *(0x250f),a */
    a -= 25L;                                             /* sub #25,a */
    if (a > 0)                                            /* bc 0x5ddc,agt */
        goto lane_5DDC;
    if ((*(volatile int *)0x0586 & 2) != 0)               /* bitf; bc tc */
        goto lane_5DBD;
    if (*(volatile int *)0x262A != 96)                    /* cmpm; bc ntc */
        goto lane_5DDC;
    *(volatile int *)0x0586 |= 2;                         /* orm #2,0x586 */
lane_5DBD:                                                /* 5DBD set lane */
    *(volatile int *)0x262A = 96;                         /* st #96,0x262a */
    *(volatile int *)0x0535 = 0;                          /* st #0,0x535 */
    *ar1 = 0;                                             /* calld delay (fills window) */
    sub_6155();                                           /* calld 0x6155 */
    if ((*(volatile int *)0x0586 & 4) == 0)               /* bitf; bc ntc */
        goto tail_5DE3;
    {                                                     /* bitf + andm + bc */
        int tc = ((*(volatile int *)0x0586 & 1) != 0);
        *(volatile int *)0x0586 &= 0xFFFE;                /* andm #-2 (always) */
        if (tc)                                           /* bc 0x5dd7,tc */
            goto lane_5DD7;
    }
    *(volatile int *)0x0586 = 0;                          /* st #0,0x586 */
    *(volatile int *)0x262A = 0;                          /* st #0,0x262a */
    goto tail_5DE3;                                       /* b 0x5de3 */
lane_5DAA:                                                /* 5DAA sub lane */
    a = (long)*(volatile int *)0x250F;                    /* ld *(0x250f),a */
    a -= 25L;                                             /* sub #25,a */
    if (a > 0)                                            /* bc 0x5ddc,agt */
        goto lane_5DDC;
    if ((*(volatile int *)0x0586 & 2) != 0)               /* bitf; bc tc */
        goto lane_5DBD;
    if (*(volatile int *)0x262A != 96)                    /* cmpm; bc ntc */
        goto lane_5DDC;
    *(volatile int *)0x0586 |= 2;                         /* orm #2,0x586 */
    goto lane_5DBD;
lane_5DD7:                                                /* 5DD7 clear lane */
    *(volatile int *)0x262A = 0;                          /* st #0,0x262a */
    goto tail_5DE3;                                       /* b 0x5de3 */
lane_5DDC:                                                /* 5DDC alt tail */
    *(volatile int *)0x0535 = 0;                          /* st #0,0x535 */
    *ar1 = 0;                                             /* calld delay (fills window) */
    sub_6155();                                           /* calld 0x6155 */
tail_5DE3:                                                /* 5DE3 join */
    if ((*(volatile int *)0x3EB5 & 512) != 0)             /* bitf; bc tc */
        goto epi_5DEF;
    *(volatile int *)0x0535 = 0;                          /* st #0,0x535 */
    *ar1 = 0;                                             /* calld delay (fills window) */
    sub_6155();                                           /* calld 0x6155 */
epi_5DEF:                                                 /* 5DEF epilogue */
    sub_640F();                                           /* call 0x640f */
    /* popm ar7/ar6 (balance the head pshms) */
    /* ret */
}
