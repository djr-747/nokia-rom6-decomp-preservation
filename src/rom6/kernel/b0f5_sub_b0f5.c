/* ROM6 0xB0F5 SUB_B0F5 -- 27w.
 * Verified encoding: src/rom6/kernel/b0f5_stub_b0f5.asm (recombine MATCH).
 * ORIGIN 0xB0F5
 * EXPECT: F074 0678 7713 0914 1083 F110 000D 7714 2EF8 FD4B F540 F210 000C FA44 B110 6284 0004 1183 09F8 2652 7712 0008 F000 0005 FD4D 8812 FC00
 *
 * Intent: Conditional select with taken tail. Runs 0x678
 * (dark, extern); AR3 = 2324, A = *AR3; B = A - 13 (sub lk
 * grounded); xc 1,blt skips the B = A reload iff B < 0
 * (XC-taken-skips per the oracle); A = B - 12; bcd on A != 0
 * tests the PRE-delay accumulator (the leaf evaluates the
 * single condition over input state; delays are subsequent
 * instructions): both delays always run (A = *AR4 x 4 via
 * mpy Smem,K16, grounded row with T = cell side effect
 * flagged; B = sign-extended *AR3, SXM = 1 flagged); taken
 * path tail-enters frag_B110 with A-low/B-low, AR4 (= 12024)
 * and the AR2 out-pointer (the 16-bit intake truncates the
 * 18-bit product, flagged), whose ret returns to our caller;
 * fall path runs B -= cell 0x2652, AR2 = 8, A += 5
 * (add lk grounded), xc 1,beq skips AR2 = A-low iff A == 0,
 * then returns with AR2 live-out through the out-pointer.
 * Bound B0F5-B10F.
 */
extern void sub_0678(void);
extern int frag_B110(int a_in, int b_in, int *par4, int **ppar2);

void sub_B0F5(int **ppar2)
{
    int *ar3 = (int *)2324;                          /* stm #2324,ar3 */
    int *ar4 = (int *)12024;                         /* stm #12024,ar4 */
    int *ar2 = *ppar2;
    long a;
    long b;
    int taken;
    sub_0678();                                      /* call 0x678 */
    a = (long)*ar3;                                  /* ld *ar3,a */
    b = a - 13;                                      /* sub #13,a,b */
    if (b >= 0)                                      /* xc 1,blt */
        b = a;                                       /* ld a,b */
    a = b - 12;                                      /* sub #12,b,a */
    taken = (a != 0);                                /* bcd tests pre-delay A */
    a = (long)*ar4 * 4;                              /* delay-1: mpy (T flagged) */
    b = (long)*ar3;                                  /* delay-2: ld (SXM flagged) */
    if (taken) {                                     /* bcd 0xb110,aneq */
        (void)frag_B110((int)(a & 0xFFFF), (int)(b & 0xFFFF), ar4, ppar2);
        return;
    }
    b -= (long)*(volatile int *)0x2652;              /* sub *(0x2652),b */
    ar2 = (int *)8;                                  /* stm #8,ar2 */
    a += 5;                                          /* add #5,a */
    if (a != 0)                                      /* xc 1,beq */
        ar2 = (int *)(a & 0xFFFF);                   /* stlm a,ar2 */
    *ppar2 = ar2;
    /* ret */
}
