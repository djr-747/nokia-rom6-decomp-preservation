/* ROM6 0x8433 FRAG_8433 -- 22w.
 * Verified encoding: src/rom6/kernel/8433_frag_8433.asm (recombine MATCH).
 * ORIGIN 0x8433
 * EXPECT: 69F8 2648 0800 7714 2648 7713 2578 6984 0010 12D2 6F93 0C98 F030 00FF 8093 F072 8447 12D2 F0E8 F0B0 8093 FC00
 *
 * Intent: Pack-and-fold loop. cell0x2648 |= 2048; AR4 = 9800,
 * AR3 = 9592 (locals, entry AR3 clobbered); cellAR4 |= 16; A =
 * unsigned *AR2 (ldu, 3691 precedent; upper zero) with AR2 +=
 * AR0-live (circular +0%, wrap needs caller-live BK, linear modeled
 * flagged); *(AR3++) = HIGH of (A arith>>8), i.e. A[39:24] -- always
 * 0 here since A < 2^16 via ldu (objdump renders `stl a,-8,*ar3+`
 * but the 6F93 encoding is STH_SHIFT_SMEM_MOD2 per the oracle, store
 * HIGH, exact); A &= 255; *(AR3++) = A-low. Then BRC + 1 passes
 * (BRC caller-live) of A = unsigned *AR2 (AR2 += AR0), A <<= 8
 * logical (sftl, 381b precedent; no overflow: A < 2^24, exact),
 * A |= A >> 16 logical (OR_ACC_SHIFT dest = A per the F0B0 S/D-bit
 * decode, 40-bit logical per the oracle leaf; exact), *(AR3++) =
 * A-low; return (ARs dead, flagged). Bound 8433-8448.
 */
void frag_8433(int *ar2_in, int ar0_live, int brc_live)
{
    int *ar2 = ar2_in;
    int *ar4;
    int *ar3;
    long a;
    int i;
    *(volatile int *)0x2648 |= 2048;                 /* orm #2048,*(0x2648) */
    ar4 = (int *)9800;                               /* stm #9800,ar4 */
    ar3 = (int *)9592;                               /* stm #9592,ar3 */
    *ar4 |= 16;                                      /* orm #16,*ar4 */
    a = (unsigned long)(unsigned)*ar2;               /* ldu *ar2+%,a */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    *ar3++ = (int)((unsigned long)a >> 24);          /* sth-shift (0 here, exact) */
    a &= 255;                                        /* and #255,a */
    *ar3++ = (int)(a & 0xFFFF);                      /* stl a,*ar3+ */
    for (i = 0; i < brc_live + 1; i++) {              /* rptb 0x8447 */
        a = (unsigned long)(unsigned)*ar2;           /* ldu *ar2+%,a */
        ar2 += ar0_live;
        a <<= 8;                                     /* sftl a,8 (logical) */
        a |= (unsigned long)a >> 16;                 /* or a,-16 (dest=A, logical) */
        *ar3++ = (int)(a & 0xFFFF);                  /* stl a,*ar3+ */
    }
    /* ret */
}
