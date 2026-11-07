/* ROM6 0x57A3 SUB_57A3 -- 41w head lane, tail-calls FRAG_57CC entries.
 * Verified encoding: src/rom6/kernel/57a3_sub_57a3.asm (recombine MATCH).
 * ORIGIN 0x57A3
 * EXPECT: F074 059C 10F8 250F F030 FFFE 60F8 0008 0020 F820 57D3 10F8 0918 F110 0034 60F8 250F 0021 FD4A F640 FF30 F010 000E 11F8 2628 F845 57EE FC43 F010 0006 F845 57CC F010 0001 F845 57F2 FC46 F273 57F4 F340 0004
 *
 * Intent: Two-lane magic-value classifier on cell 0x918, steered by cell
 * 0x250F (id) with state in cell 0x2628; B-out. Runs dark SUB_059C (call).
 * A = id & -2 (and; dead: A reloaded below, transcribed hand-asm quirk).
 * Lane select: TC = (*(0x8) == 32) (cmpm; memory ops keep TC per
 * op_cmpm_smem_lk); mismatch tail-enters FRAG_57D3 (bc ntc).
 * Lane 1: A = cell 0x918; B = A - 52 (sub #52,a,b: A kept, SUB preserves
 * TC per ti-c54x op_sub_lk). TC = (id == 33) (cmpm). B < 0 reloads
 * A = B (xc 1,bgeq skips one word; XC skips WORDS per op_xc). TC skips
 * A -= 14 (xc 2,tc). B = state cell 0x2628 (ld). A == 0 takes the 57EE
 * entry (bc aeq; dead in this lane -- pre-sub A is cell (skip path needs
 * cell >= 52) or cell - 52 (ld path needs cell < 52), never 14;
 * HYPOTHESIS, kept as written). A < 0 returns B (rc alt; RC 1-word,
 * not-taken falls through per op_rc). A -= 6, zero takes the 57CC entry
 * (bc aeq; cell == 72 non-TC / cell == 58 TC lane). A -= 1, zero takes
 * the 57F2 entry (bc aeq; cell == 73 / 59). A > 0 returns B (rc agt).
 * Else B |= 4 runs in the bd delay slot (always executes) and control
 * takes the 57F4 entry (bd). Falls into the 57CC tail (abut 57A3+41 =
 * 57CC), modeled as tail call frag_57CC (exact: 57CC body executes next).
 * Bound 57A3-57CB; whole-routine RET FC00@57FD in the 57CC tail module.
 */
extern void sub_059C(void);
extern int frag_57D3(void);
extern int frag_57CC(int b_live);
extern int frag_57EE(int b_live);
extern int frag_57F2(int b_live);
extern int frag_57F4(int b_live);

int sub_57A3(void)
{
    long a;
    long b;
    int tc;

    sub_059C();                                        /* call 0x59c */
    a = *(volatile int *)0x250F;                       /* ld */
    a &= -2;                        /* and (dead, A reloaded; quirk) */
    tc = (*(volatile int *)0x8 == 32);                 /* cmpm */
    if (!tc)                                           /* bc ntc */
        return frag_57D3();
    a = *(volatile int *)0x918;                        /* ld */
    b = a - 52L;                       /* sub #52,a,b (A kept) */
    tc = (*(volatile int *)0x250F == 33);              /* cmpm */
    if (b < 0)                                         /* xc 1,bgeq */
        a = b;                                         /* ld b,a */
    if (!tc)                                           /* xc 2,tc */
        a -= 14;                                       /* sub #14,a */
    b = *(volatile int *)0x2628;                       /* ld */
    if (a == 0)                                        /* bc aeq (dead) */
        return frag_57EE((int)b);
    if (a < 0)                                         /* rc alt */
        return (int)b;
    a -= 6;                                            /* sub #6,a */
    if (a == 0)                                        /* bc aeq */
        return frag_57CC((int)b);
    a -= 1;                                            /* sub #1,a */
    if (a == 0)                                        /* bc aeq */
        return frag_57F2((int)b);
    if (a > 0)                                         /* rc agt */
        return (int)b;
    b |= 4;                               /* bd delay slot, always */
    return frag_57F4((int)b);                          /* bd 0x57f4 */
}
