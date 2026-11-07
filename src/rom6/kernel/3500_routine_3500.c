/* ROM6 0x3500 ROUTINE_3500 -- 29w (idle loop + 350C tail).
 * Verified encoding: src/rom6/kernel/3500_routine_3500.asm (recombine MATCH).
 * ORIGIN 0x3500
 * EXPECT: 6FF8 04FA 0C43 1AF8 0866 F040 0040 80F8 0866 F5E1 F073 3500 1082 F030 F0F0 6FD2 0D48 F330 0F00 F2A0 6F82 0D58 F330 000F F2A0 1C95 F844 3500 FC00
 *
 * Intent: Idle wait with fold tail. Head loops forever: A =
 * cell0x4FA << 3 (LD Smem,SHFT per the 71d8 precedent; DP = 0
 * assumed, flagged) OR cell0x866 OR 64, cell0x866 = A-low,
 * cpu_idle(3) (IDLE extern-op placeholder), branch to self.
 * The 350C entry (separate callers) folds: A = *AR2 & 0xF0F0
 * (AND imm16 zero-extends: upper cleared, per ti-c54x
 * op_logical_immediate), B = (*AR2 << 8) & 0xFFFF... A |= B
 * with B = (*AR2>>8 arith) & 15 stages (LD shift -8 per the 457f
 * precedent, SXM = 1 flagged; circular +0% needs caller-live AR0
 * + BK, linear flagged), A ^= *AR5++ (XOR Smem, logical exactly),
 * nonzero tail-enters the head loop, else returns. AR2/AR5/AR0
 * caller-live, dead after. Bound 3500-351C.
 */
extern void cpu_idle(int mode);

void routine_3500(void)
{
    long a;
    for (;;) {
        a = (long)*(volatile int *)0x4FA << 3;       /* ld *(0x4fa),3,a */
        a |= (long)*(volatile int *)0x866;           /* or *(0x866),a */
        a |= 64;                                     /* or #64,a */
        *(volatile int *)0x866 = (int)(a & 0xFFFF);  /* stl a,*(0x866) */
        cpu_idle(3);                                 /* idle 3 */
        /* b 0x3500 (loop) */
    }
}

void frag_350C(int *ar2_in, int *ar5_in, int ar0_live)
{
    int *ar2 = ar2_in;
    int *ar5 = ar5_in;
    long a;
    long b;
    a = (long)*ar2;                                  /* ld *ar2,a */
    a &= 0xF0F0L;                                    /* and #-3856,a (imm16 zero-ext) */
    b = (long)*ar2 << 8;                             /* ld *ar2+%,8,b */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    b &= 3840;                                       /* and #3840,b */
    a |= b;                                          /* or b,a */
    b = (long)*ar2 >> 8;                             /* ld *ar2,-8,b (arith, flagged) */
    b &= 15;                                         /* and #15,b */
    a |= b;                                          /* or b,a */
    a ^= (long)*ar5++;                               /* xor *ar5+,a */
    if (a != 0) {                                    /* bc 0x3500,aneq */
        routine_3500();
        return;
    }
    /* ret */
}
