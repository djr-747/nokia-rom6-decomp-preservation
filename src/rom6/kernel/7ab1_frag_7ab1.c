/* ROM6 0x7AB1 FRAG_7AB1 -- 45w tune-guard cascade.
 * Verified encoding: src/rom6/kernel/7ab1_frag_7ab1.asm (recombine MATCH).
 * ORIGIN 0x7AB1
 * EXPECT: 60F8 250F 0022 F820 7AE5 60F8 34BF 0001 F830 7AE5 60F8 34BF 0004 F830 7AE5 7713 2636 60F8 34BF 0003 F820 7AE5 1081 F010 00E0 F845 7ADE 61F8 3490 0080 F820 7AE5 61F8 3490 0100 F820 7AD8 7713 34BE 6D90 68F8 3490 FF7F F073 7AE5
 *
 * Intent: Exit to the 7AE5 tail (next span owns; modeled as
 * return) unless every guard passes: *(0x250F) == 34
 * (cmpm equality, oracle op_cmpm_smem_lk; bc ntc);
 * *(0x34BF) != 1 (bc tc); *(0x34BF) != 4 (bc tc); AR3 =
 * 9782; *(0x34BF) == 3 (bc ntc); A = *(AR1) - 224 (AR1
 * dark; ld SXM dark flagged; sub unshifted); A == 0 exits
 * forward to 7ADE (bc aeq; next span owns); bit 7 of
 * *(0x3490) set (bitf any-bit TC, oracle; bc ntc); bit 8
 * test joins immediately (bc 0x7ad8,ntc targets the next
 * word either way -- no-op, noted); AR3 = 13502; AR0++
 * (mar, AR0 dark flagged); *(0x3490) &= -129 (andm clears
 * bit 7); b 0x7ae5 (tail owns). Out cells/ARs.
 * EXPECT from the image.
 */
void frag_7AB1(void)
{
    long a;
    int *ar0;  /* live-in (dark, flagged) */
    int *ar1;  /* live-in (dark, flagged) */
    int *ar3;

    if (*(volatile int *)0x250F != 34)                       /* cmpm, bc 0x7ae5,ntc */
        return;
    if (*(volatile int *)0x34BF == 1)                        /* cmpm, bc tc */
        return;
    if (*(volatile int *)0x34BF == 4)                        /* cmpm, bc tc */
        return;
    ar3 = (int *)9782;                                       /* stm #9782,ar3 */
    if (*(volatile int *)0x34BF != 3)                        /* cmpm, bc ntc */
        return;
    a = (long)*ar1;                                          /* ld *ar1,a (SXM dark, flagged) */
    a -= 224;                                                /* sub #224,a */
    if (a == 0)                                              /* bc 0x7ade,aeq (next span owns) */
        return;
    if ((*(volatile int *)0x3490 & 128) == 0)                /* bitf #128, bc ntc */
        return;
    /* bitf *(0x3490),#256; bc 0x7ad8,ntc (joins next word either way) */
    ar3 = (int *)13502;                                      /* stm #13502,ar3 */
    ar0++;                                                   /* mar *ar0+ */
    *(volatile int *)0x3490 &= -129;                         /* andm #-129 (clears bit 7) */
    /* b 0x7ae5 (next span owns) */
    (void)ar3;
}
