/* ROM6 0x688D SUB14_688D -- 20w polled negate with delayed return.
 * Verified encoding: src/rom6/kernel/688d_sub14_688d.asm (recombine MATCH).
 * ORIGIN 0x688D
 * EXPECT: 61F8 051E 0800 11F8 2FD7 FF20 11F8 0915 F784 F300 0002 F495 F495 FF4B F300 0033 FC30 0986 FE00 E800 F586
 *
 * Intent: TC = bit 11 of cell 0x51E (bitf #2048, TC-only). B = cell 0x2FD7
 * sign-extended (ld); TC clear swaps in cell 0x915 instead (xc 2,ntc over
 * the ld; LD preserves TC per ti-c54x op_ld_k.c). B = -B (neg, TC
 * preserved per op_neg_acc.c) + 2 (add); two nops (pipeline padding). B <
 * 0 adds 51 (xc 2,blt over add #51,b). TC set returns B as-is (rc tc; TC
 * still the bitf result: xc/neg/add/nop all TC-preserving per
 * op_logical.c-op_neg_acc.c-op_add_lk.c-oracle chain). Else B -= *AR6
 * (live-in; sub Smem sign-extends under SXM = 1 per op_sub_smem.c) and
 * returns via retd (delays always run; noted). B the
 * only live-out (long, 40-bit, max lane unmodeled -- flagged). AR6 entry-live.
 * Bound 688D-68A1 (exit retd FE00@689F + delays E800@68A0/F586@68A1; gap orphan annexed wave-13).
 */
long sub14_688D(int *par6)
{
    int tc = (*(volatile int *)0x51E & 2048) != 0;  /* bitf (TC) */
    long b = (long)*(volatile int *)0x2FD7;          /* ld *(0x2fd7),b */

    if (!tc)                                       /* xc 2,ntc */
        b = (long)*(volatile int *)0x915;            /* ld *(0x915),b */
    b = -b;                                        /* neg b */
    b += 2L;                                       /* add #2,b */
    /* nop; nop */
    if (b < 0)                                     /* xc 2,blt */
        b += 51L;                                  /* add #51,b */
    if (tc)                                        /* rc tc */
        return b;
    b -= (long)*par6;                              /* sub *ar6,b */
    /* retd @689F; delays always run: ld #0,a (A = 0 dead, noted); max b @68A1:
       B = max(A=0,B) per SPRU172C MAX (not modeled -- MAX_ACC row-but-no-leaf, flagged) */
    return b;
}
