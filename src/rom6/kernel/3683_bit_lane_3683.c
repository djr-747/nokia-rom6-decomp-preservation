/* ROM6 0x3683 BIT_LANE_3683 -- 14w.
 * Verified encoding: src/rom6/kernel/3683_bit_lane_3683.asm (recombine MATCH).
 * ORIGIN 0x3683
 * EXPECT: 6182 0001 7714 3ACA E800 FD30 10DA 8084 F074 2E2F F073 2E64 F074 05B2
 *
 * Intent: Single-bit conditional store then dispatcher tail. TC = *AR2 & 1 (bitf); AR4 = 15050 (stm);
 * A = 0 (ld); TC taken loads A = *AR2 (xc 1,tc skips ld only -- stl always runs); *AR4 = A (stl);
 * dispatcher_entry_2E2F(); b-tail frag_2E64(). Words 368F (call 0x5B2, 2w) sit past the unconditional b
 * -- dead, not modeled (5886 precedent); falls into 3691 frag (dead past b, noted). Post-branch head
 * (prev b 2e64); no exterior callers, entry unconfirmed, flagged.
 */
extern void dispatcher_entry_2E2F(void);
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

void frag_3683(int *par2)
{
    long a;
    int *ar4;
    int taken;


    taken = (*par2 & 1) != 0;                              /* bitf *ar2,#1 */
    ar4 = (int *)15050;                                    /* stm #15050,ar4 */
    a = 0;                                                 /* ld #0,a */
    if (taken)                                             /* xc 1,tc (skips ld only) */
        a = *par2;                                         /* ld *ar2+0%,a (wrap flagged) */
    *ar4 = (int)a;                                         /* stl a,*ar4 (always runs) */
    dispatcher_entry_2E2F();                               /* call 0x2e2f */
    frag_2E64();                                           /* b 0x2e64 (tail) */
    /* dead 368F (past unconditional b, not modeled) */
}
