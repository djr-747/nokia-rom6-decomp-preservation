/* ROM6 0x45A0 FRAG_45A0 -- 9w.
 * Verified encoding: src/rom6/kernel/45a0_frag_45a0.asm (recombine MATCH).
 * ORIGIN 0x45A0
 * EXPECT: F074 2E2F 69F8 051F 2000 E910 F074 B461 FC00
 *
 * Intent: Dispatcher plus flag-set call. Runs the 0x2E2F dispatcher entry, sets bit 13 of cell 0x51F (orm #8192), passes B = 16 to 0xB461, returns.
 */
extern void dispatcher_entry_2E2F(void);
extern void sub_B461(int b);

void frag_45A0(void)
{
    dispatcher_entry_2E2F();                    /* call 0x2e2f */
    *(volatile int *)0x51F |= 8192;          /* orm #8192,*(0x51f) */
    sub_B461(16);                                /* ld #16,b; call 0xb461 */
    /* ret */
}
