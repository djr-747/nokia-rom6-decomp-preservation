/* ROM6 0x226C SUB_226C -- 22w.
 * Verified encoding: src/rom6/boot/226c_sub_226c.asm (recombine MATCH).
 * ORIGIN 0x226C
 * EXPECT: F074 2282 F820 2271 FC00 F7BB 61F8 0866 0002 F830 227B F6BB F4E1 F073 2271 F6BB 4A12 F074 2E39 8A12 F073 226C
 *
 * Intent: TC-gated idle-wait with dispatcher retry. Loops: runs SUB_2282; TC taken returns (bc ntc to ret
 * inverted: TC set exits, TC clear enters the wait lane). Wait lane: INTM guard (ssbx, hardware); spins on
 * cell 0x866 bit 1 (bitf/bc/idle-1/rsbx wait loop, cpu_idle extern-op placeholder); INTM restore (rsbx);
 * AR2-save (pshm/popm, balanced, caller-live, comment only); runs leaf_2E39 (C-bound void); retries the head
 * (b 0x226C). AR2 caller-live, never read through (flagged). Entry: exterior call x5 (PROM + in-gap).
 */
extern void sub_2282(void);
extern void leaf_2E39(void);
extern void cpu_idle(int mode);                                       /* IDLE sleep (84af precedent: sleep until interrupt); no ROM definition */

void sub_226C(void)
{
    int tc_dark;  /* TC from 2282 bitt (uncarried, unbound, flagged) */


    for (;;) {
        sub_2282();                                        /* call 0x2282 */
        if (tc_dark)                                       /* bc 0x2271,ntc (inverted exit) */
            return;
        /* ssbx st1,intm (hardware, no C form) */
        while ((*(volatile int *)0x866 & 2) == 0) {        /* bitf; bc spin */
            /* rsbx st1,intm (hardware, no C form) */
            cpu_idle(1);                                   /* idle 1 */
            /* b 0x2271 (spin) */
        }
        /* rsbx st1,intm (hardware, no C form) */
        /* pshm ar2 (balanced by popm; caller-live, comment only) */
        leaf_2E39();                                       /* call 0x2e39 */
        /* popm ar2 (restore entry state) */
        /* b 0x226c (retry head) */
    }
}
