/* ROM6 0x2262 SUB_2262 -- 10w.
 * Verified encoding: src/rom6/boot/2262_sub_2262.asm (recombine MATCH).
 * ORIGIN 0x2262
 * EXPECT: F074 2282 FC30 7312 0536 F274 2D5E 7713 0871 FC00
 *
 * Intent: TC-gated dispatcher tail. Runs SUB_2282 (forward extern, C-bound below; TC-out = retd-delay
 * bitt over cell 0x537, uncarried); TC taken returns (rc). Cell 0x536 = AR2-live (mvmd; AR2 caller-live,
 * never set in-span, unbound, flagged). AR3 = 2161 (calld delay, runs first); delayed tail into SUB_2D5E
 * (C-bound, AR2 unbound + AR3 passed); return. Entry: exterior calld x5 (PROM 0x4516/0x451E/0x4524/0x54D7 +
 * in-gap); no caller-live regs modeled.
 */
extern void sub_2282(void);
extern void sub_2D5E(int *par2, int *par3);

void sub_2262(void)
{
    int *ar2_unbound;  /* AR2 caller-live, never set in-span (flagged) */
    int *ar3;
    int tc_dark;  /* TC from 2282 bitt (uncarried, unbound, flagged) */


    sub_2282();                                            /* call 0x2282 */
    if (tc_dark)                                           /* rc tc */
        return;
    *(volatile int *)0x536 = (int)(long)ar2_unbound;      /* mvmd ar2,0x536 */
    ar3 = (int *)2161;                                     /* calld delay: stm (runs first) */
    sub_2D5E(ar2_unbound, ar3);                            /* calld 0x2d5e */
    /* ret @226B */
    (void)tc_dark;
}
