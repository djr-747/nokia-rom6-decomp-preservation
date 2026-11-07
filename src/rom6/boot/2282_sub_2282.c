/* ROM6 0x2282 SUB_2282 -- 7w.
 * Verified encoding: src/rom6/boot/2282_sub_2282.asm (recombine MATCH).
 * ORIGIN 0x2282
 * EXPECT: E80F 08F8 0012 880E FE00 34F8 0537
 *
 * Intent: ST1-based T preset with bitt TC-out. A = 15 - ST1 (ld/sub; ST1 = *(0x12), volatile MMR);
 * T = A-low (stlm; T hardware, dark lane may read, flagged). Delayed return (retd) with the bitt
 * *(0x537) delay running first (TC = bitT of the cell per 692C row, uncarried); return to caller.
 * TC-out read by the 2262/226C rc/bc gates (modeled unbound there, flagged). Entry: exterior calld x5
 * (PROM) + in-gap calls (F1 lanes). No caller-live regs.
 */

void sub_2282(void)
{
    long a;
    int t_new;


    a = 15 - (long)*(volatile int *)0x12;                  /* ld #15,a; sub *(0x12),a */
    t_new = (int)(a & 0xFFFF);                             /* stlm a,t (T hardware) */
    /* retd delay: bitt *(0x537) (runs; TC = bitT, uncarried) */
    /* retd @2286 */
    (void)t_new;
}
