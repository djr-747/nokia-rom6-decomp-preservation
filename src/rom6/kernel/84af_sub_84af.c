/* ROM6 0x84AF SUB_84AF -- 32w.
 * Verified encoding: src/rom6/kernel/84af_sub_84af.asm (recombine MATCH).
 * ORIGIN 0x84AF
 * EXPECT: F074 05A0 69F8 0029 0004 7758 FFFD 61F8 0058 0001 F830 84B6 7758 0000 F495 75F8 0015 0000 F5E1 7758 51EE 61F8 0058 0001 F820 84C4 68F8 0029 FFFB EC03 F495 FC00
 *
 * Intent: clock-gated idle/wake handshake. CLKMD is the
 * memory-mapped clock register at data address 0x58 -- the same
 * cell the bitf spins read. Helper call, set bit 2 of 0x29,
 * program CLKMD to -3, spin until its bit 0 reads set (84B6 loop),
 * clear CLKMD, strobe port 0, IDLE 3 (DSP sleep until interrupt),
 * restore CLKMD to 20974, spin until bit 0 clears (84C4 loop),
 * clear bit 2 of 0x29, short nop delay, return.
 */
extern void helper_05A0(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void cpu_idle_3(void);   /* idle 3: sleep until interrupt */

void sub_84AF_clock_gate(void)
{
    volatile int *clkmd = (volatile int *)0x58;
    helper_05A0();                        /* call 0x5a0 */
    *(volatile int *)0x29 |= 4;          /* orm #4,*(0x29) */
    *clkmd = -3;                          /* stm #-3,clkmd */
    while (!(*clkmd & 1)) {}              /* L_84B6: bc tc spin */
    *clkmd = 0;                           /* stm #0,clkmd */
    *(volatile int *)0x15 = 0;            /* portw *(0x15),0 */
    cpu_idle_3();                         /* idle 3 */
    *clkmd = 20974;                       /* stm #20974,clkmd */
    while (*clkmd & 1) {}                 /* L_84C4: bc ntc spin */
    *(volatile int *)0x29 &= ~4;           /* andm #-5 (bit2 off) */
    { int i; for (i = 0; i < 4; i++) {} } /* rpt #3, nop */
    /* ret */
}
