/* ROM6 ORIGIN 0x5886 (90w): FRAG_5886 -- mpy/accumulate lanes, BCD-word-model join.
 * Verified encoding: src/rom6/kernel/5886_frag_5886.asm (recombine MATCH).
 * ORIGIN 0x5886
 * EXPECT: F074 059C 60F8 2510 00B0 F820 5890 76F8 2F02 00C1 62F8 261E 0039 7210 264C F274 58E0 7714 0160 E804 00F8 261E 62F8 0008 0039 7210 264D F274 58E0 7714 0161 F7B9 44F8 01D2 3CF8 2622 82F8 2622 44F8 01D3 3CF8 2621 82F8 2621 F6B9 E801 00F8 261E F110 0003 FA4E 58C0 7712 2F02 F273 58DD 7682 0000 7712 264D 108A 4D82 8082 10F8 2620 F845 58D0 E800 80F8 2620 F273 58D7 80F8 2F02 11F8 2621 F84A 58D7 76F8 2F02 00B0 7712 2622 7182 2621 E800 8082 80F8 261E FC00
 *
 * Intent: Guard, two mpy-plus-call lanes, OVM add pair, BCD-word-model
 * fan, flag epilogue. Runs dark SUB_059C (opaque, forward extern; A/B
 * rewritten after, outputs dead). Cell 0x2510 != 176 chains to 5890
 * (cmpm equal-sets-TC, bc ntc). Else *0x2F02 = 193 (st #lk direct).
 * A = *(0x261E) * 57 (mpy Smem,#lk, 311f precedent: plain signed long
 * multiply, T = Smem side effect dead in-span, flagged). AR0 =
 * *(0x264C) is a dead lane (never read in-span nor in the pooled
 * callee body below; noted, not modeled per the 3199 precedent).
 * calld SUB_58E0 (pooled asm-only span, forward extern void; the stm
 * #352,ar4 fills the whole 2-word delay window per the word-count
 * rule, so the call fires before the ld; return address 5899 runs
 * ld #4,a AFTER the call, modeled in call position). AR4 = 352/353
 * feeds the pooled span implicitly (it reads *ar4 at its andm/add);
 * the void extern cannot carry it, flagged. A += *(0x261E).
 * A = ALIAS(0x8) * 57 (mpy *(0x8): DATA 0x8 mirrors AL per the
 * 3a8e/311f MMR-alias correction, modeled as the alias-cell read
 * exactly like 311f; T dead flagged). AR0 = *(0x264D) dead lane
 * (same note). calld SUB_58E0 again (stm #353,ar4 fills window;
 * return runs the ssbx below -- ssbx st1,ovm is hardware, no C form,
 * OVM = 1 for the adds, flagged). A = *(0x1D2)<<16 += *(0x2622)<<16,
 * *0x2622 = A-high; A = *(0x1D3)<<16 += *(0x2621)<<16, *0x2621 =
 * A-high (LD-shifted + ADD Smem,SHIFT; SXM-sign assumed, oracle
 * op_add_smem_shift; low-32 exact, OVM saturation corners need |Y|
 * near 32768, values assumed small, flagged). rsbx st1,ovm
 * (hardware, no C form). A = 1 + *(0x261E); B = A - 3.
 * bcd 0x58C0,bgt uses WORD-count delay slots (ti-c54x delayed_branch
 * oracle: arm replaces pending, 2-word consume fires at once --
 * test_two_word_instruction_takes_effect_at_once): the 2-word stm
 * fills the window, so the bcd fires before the bd decodes; B>0
 * jumps to 58C0 (bd and its delays skipped) while B<=0 falls into
 * the bd at 58BC, whose own 2-word st delay fills ITS window before
 * firing to 58DD (the stm #9805 at 58C0 belongs to the taken path,
 * not to the bd). Taken path: AR2 = 0x264D; A = *AR2, AR2-- (now
 * 0x264C); delay *ar2 is a cycle burn (no state, noted); *AR2 =
 * A-low. Untaken path: *0x2F02 = 0 via the bd delay, then 58DD.
 * 58C5: A = *(0x2620); A == 0 chains to the 58D0 flag test (bc aeq),
 * else A = 0, *0x2620 = 0, bd 0x58D7 with delay *0x2F02 = A-low = 0
 * (2-word stl fills window, fires after; bd skips the flag test).
 * 58D0: B = *(0x2621); B >= 0 chains to 58D7 (bc bgeq, full-40
 * signed, exact on cells), else *0x2F02 = 176 (fallthrough).
 * 58D7: AR2 = 0x2622; *(0x2621) = *AR2 (mvdk decodes MVDK_SMEM
 * 0x7180: Smem to dmad, dest-second, catalog P3-S61); A = 0;
 * *AR2 = 0; 58DD: *(0x261E) = A-low; return (ret, no delay). A/B
 * live-outs are concrete residues (A = *0x264D or cell-2, B = A-3)
 * with no documented consumer (zero in-image callers per header
 * evidence): void, noted. No params (AR2/AR4 set in-span; AR0 dead;
 * AR1/AR3/AR5 untouched; A/B rewritten after the dark head call).
 * Bound 5886-58DF (ret FC00@58DF; abuts pooled SUB_58E0 at 58E0).
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_58E0(void); /* joins 58e0_sub_58e0; see docs/evidence/extern-triage.md */

void frag_5886(void)
{
    long a;
    long b;
    int *ar2;
    int *ar4;
    int taken;

    sub_059C();                                            /* call 0x59c */
    if (*(volatile int *)0x2510 != 176)                   /* cmpm; bc ntc */
        goto lane_5890;
    *(volatile int *)0x2F02 = 193;                        /* st #193 */
lane_5890:                                                /* 5890 mpy lane */
    a = (long)*(volatile int *)0x261E * 57L;              /* mpy (T flagged) */
    /* mvdm 0x264c,ar0: dead lane (never read), not modeled */
    ar4 = (int *)352;                                     /* calld delay (fills window) */
    sub_58E0();                                           /* calld 0x58e0 */
    a = 4;                                                /* ld #4,a (return addr) */
    a += (long)*(volatile int *)0x261E;                   /* add *(0x261e),a */
    a = (long)*(volatile int *)0x8 * 57L;                 /* mpy AL-alias (T flagged) */
    /* mvdm 0x264d,ar0: dead lane (never read), not modeled */
    ar4 = (int *)353;                                     /* calld delay (fills window) */
    sub_58E0();                                           /* calld 0x58e0 */
    (void)ar4;  /* set-but-unread in C: feeds pooled SUB_58E0 implicitly, flagged above */
    /* ssbx st1,ovm (hardware, no C form; return addr) */
    a = (long)*(volatile int *)0x01D2 << 16;              /* ld *(0x1d2),16,a */
    a += (long)*(volatile int *)0x2622 << 16;             /* add shifted */
    *(volatile int *)0x2622 = (int)(((unsigned long)a >> 16) & 0xFFFF); /* sth */
    a = (long)*(volatile int *)0x01D3 << 16;              /* ld *(0x1d3),16,a */
    a += (long)*(volatile int *)0x2621 << 16;             /* add shifted */
    *(volatile int *)0x2621 = (int)(((unsigned long)a >> 16) & 0xFFFF); /* sth */
    /* rsbx st1,ovm (hardware, no C form) */
    a = 1;                                                /* ld #1,a */
    a += (long)*(volatile int *)0x261E;                   /* add *(0x261e),a */
    b = a - 3L;                                           /* sub #3,a,b */
    ar2 = (int *)0x2F02;                                  /* bcd delay (fills window) */
    taken = (b > 0);                                      /* bcd pre-decode test */
    if (taken)                                            /* bcd taken: bd skipped */
        goto lane_58C0;
    *ar2 = 0;                                             /* bd delay (fills window) */
    goto tail_58DD;                                       /* bd 0x58dd fires */
lane_58C0:                                                /* bcd-taken path */
    ar2 = (int *)0x264D;                                  /* stm #9805,ar2 */
    a = (long)*ar2--;                                     /* ld *ar2-,a */
    /* delay *ar2 (cycle burn, no state change) */
    *ar2 = (int)(a & 0xFFFF);                             /* stl a,*ar2 */
    a = (long)*(volatile int *)0x2620;                    /* ld *(0x2620),a */
    if (a == 0)                                           /* bc 0x58d0,aeq */
        goto test_58D0;
    a = 0;                                                /* ld #0,a */
    *(volatile int *)0x2620 = (int)(a & 0xFFFF);          /* stl a,0x2620 */
    *(volatile int *)0x2F02 = (int)(a & 0xFFFF);          /* bd delay (fills window) */
    goto epi_58D7;                                        /* bd fires (skips test) */
test_58D0:                                                /* 58D0 flag test */
    b = (long)*(volatile int *)0x2621;                    /* ld *(0x2621),b */
    if (b >= 0)                                           /* bc 0x58d7,bgeq */
        goto epi_58D7;
    *(volatile int *)0x2F02 = 176;                        /* st #176 (fallthrough) */
epi_58D7:                                                 /* 58D7 epilogue */
    ar2 = (int *)0x2622;                                  /* stm #9762,ar2 */
    *(volatile int *)0x2621 = *ar2;                       /* mvdk *ar2,dmad */
    a = 0;                                                /* ld #0,a */
    *ar2 = (int)(a & 0xFFFF);                             /* stl a,*ar2 */
    goto ret_58DF;
tail_58DD:                                                /* bd-untaken path (A = 1+cell flows) */
ret_58DF:                                                 /* 58DD join */
    *(volatile int *)0x261E = (int)(a & 0xFFFF);          /* stl a,0x261e */
    /* ret */
}
