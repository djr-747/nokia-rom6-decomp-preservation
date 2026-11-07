/* ROM6 0x629F LOOP_629C -- 21w (post-RET head).
 * Verified encoding: src/rom6/kernel/629f_loop_628c.asm (recombine MATCH).
 * ORIGIN 0x629F
 * EXPECT: FC00 6086 0050 F830 62F2 6086 0052 F830 62F2 F274 698B 7711 0920 F274 69A9 7711 0920 7710 2629 7711 091F
 *
 * Intent: Compare-gated helper pair. Word0 is the prior span's RET
 * (verified, not modeled). *AR6 == 80 or == 82 tail-enters FRAG_62F2
 * (cmpm sets TC on equality per op_cmpm_smem_lk, 3691 precedent; 62f2
 * takes no entry value per its head: cell-first reads). Else AR1 =
 * 2336 feeds SUB_698B (calld delay stm, 80fc precedent; C:
 * sub_698B) then AR1 = 2336 feeds dark SUB_69A9 (reads *AR1 first per
 * its head, param grounded, flagged); AR0 = 9769, AR1 = 2335 run live
 * into the next span (no binding yet, flagged). Bound 629F-62B2, falls
 * through.
 */
extern void sub_698B(int **pp1);
extern void sub_69A9(int *ar1_live);
extern void frag_62F2(void);

void loop_629F(int *par6)
{
    int *ar1;
    int *ar0;
    if (*par6 == 80) {                               /* cmpm *ar6,#80; bc tc */
        frag_62F2();
        return;
    }
    if (*par6 == 82) {                               /* cmpm *ar6,#82; bc tc */
        frag_62F2();
        return;
    }
    ar1 = (int *)2336;                               /* calld delay: stm */
    sub_698B(&ar1);                                  /* calld 0x698b */
    ar1 = (int *)2336;                               /* calld delay: stm */
    sub_69A9(ar1);                                   /* calld 0x69a9 (dark) */
    ar0 = (int *)9769;                               /* stm #9769,ar0 */
    ar1 = (int *)2335;                               /* stm #2335,ar1 */
    (void)ar0;                                       /* ARs live into next span (flagged) */
    (void)ar1;
}
