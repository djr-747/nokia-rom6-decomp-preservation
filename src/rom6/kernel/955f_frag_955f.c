/* ROM6 0x955F FRAG_955F -- 15w.
 * Verified encoding: src/rom6/kernel/955f_frag_955f.asm (recombine MATCH).
 * ORIGIN 0x955F
 * EXPECT: F820 95A2 6182 0400 E902 F495 FD30 E904 81F8 21FE E800 F273 9667 6982 0080
 *
 * Intent: Flag-store fork. The bc delay bitf always runs (TC =
 * (*AR2 & 1024) != 0, 32b4 precedent); entry-TC clear tail-enters
 * FRAG_95A2 with entry A and AR3 (both untouched before the bc, proven
 * live by the 95a2 bytes: add reads A, ldm reads AR3). Else B = 2,
 * entry-... recomputed TC set makes B = 4 (xc 1,tc: taken runs the
 * 1-word LD, per ti-c54x op_xc); cell 0x21FE = B; the bd delay
 * *AR2 |= 128 always runs; tail-branches 0x9667 with A = 0 (9667
 * stores entry A first, so the zero is consumed, flagged).
 * frag_95A2/frag_9667 have .asm only (forward externs, 89b3 precedent).
 * Bound 955F-956D.
 */
extern void frag_95A2(long a_live, int ar3_live);
extern void frag_9667(long a_live, int *ar2_live, long b_live);

void frag_955F(int tc_live, long a_live, int ar3_live, int *ar2)
{
    int tc;
    int b;
    tc = (*ar2 & 1024) != 0;                       /* bc delay: bitf (always runs) */
    if (!tc_live) {                                /* bc 0x95a2,ntc */
        frag_95A2(a_live, ar3_live);
        return;
    }
    b = 2;                                         /* ld #2,b */
    /* nop */
    if (tc)                                        /* xc 1,tc (taken runs ld) */
        b = 4;                                     /* ld #4,b */
    *(volatile int *)0x21FE = b;                   /* stl b,*(0x21fe) */
    *ar2 |= 128;                                   /* bd delay: orm (always runs) */
    /* A = 0 (ld #0,a); B passes through to 9667 or-cell */
    frag_9667(0L, ar2, (long)b);                    /* bd 0x9667 */
}
