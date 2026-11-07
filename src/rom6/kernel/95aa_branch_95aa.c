/* ROM6 0x95AA BRANCH_95AA -- 14w.
 * Verified encoding: src/rom6/kernel/95aa_branch_95aa.asm (recombine MATCH).
 * ORIGIN 0x95AA
 * EXPECT: 76F8 20FA 0000 F030 FF00 F130 FDFF F310 1C00 F84D 95B8 E800 F073 9667
 *
 * Intent: Accumulator-gated fork to next-span join vs far tail. Cell 0x20FA = 0 (st); A &= -256 (and);
 * B = A & -513 (and); B -= 7168 (sub); zero tail-calls frag_95B8 (bc 95B8,beq -- join next span,
 * A_live = full masked A); else A = 0 (ld) and b-tails frag_9667 (B_live = tested B, AR2 caller-live,
 * unbound, flagged). Post-bacc head (prev bacc b @95A9); no exterior callers, entry unconfirmed, flagged.
 */
extern void frag_95B8(int a_live, int *par4);
extern void frag_9667(long a_live, int *ar2, long b_live);

void frag_95AA(long a_live, int *par4, int *par2)
{
    long b;


    *(volatile int *)0x20FA = 0;                           /* st #0,*(0x20fa) */
    a_live &= -256L;                                       /* and #-256,a */
    b = a_live & -513L;                                    /* and #-513,a,b */
    b -= 7168;                                             /* sub #7168,b */
    if (b == 0) {                                          /* bc 0x95b8,beq */
        frag_95B8((int)a_live, par4);
        return;
    }
    frag_9667(0L, par2, b);                                /* ld #0,a; b 0x9667 (tail) */
}
