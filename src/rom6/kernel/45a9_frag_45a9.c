/* ROM6 0x45A9 FRAG_45A9 -- 9w.
 * Verified encoding: src/rom6/kernel/45a9_frag_45a9.asm (recombine MATCH).
 * ORIGIN 0x45A9
 * EXPECT: F074 2E2F 68F8 051F DFFF E910 F074 B4A8 FC00
 *
 * Intent: Dispatcher plus flag-clear call. Runs the 0x2E2F dispatcher entry, clears bit 13 of cell 0x51F (andm -8193), passes B = 16 to 0xB4A8, returns.
 */
extern void dispatcher_entry_2E2F(void);
extern void sub_B4A8(int b); /* joins b4a8_routine_b4a8; see docs/evidence/extern-triage.md */

void frag_45A9(void)
{
    dispatcher_entry_2E2F();                    /* call 0x2e2f */
    *(volatile int *)0x51F &= -8193;         /* andm #-8193,*(0x51f) */
    sub_B4A8(16);                                /* ld #16,b; call 0xb4a8 */
    /* ret */
}
