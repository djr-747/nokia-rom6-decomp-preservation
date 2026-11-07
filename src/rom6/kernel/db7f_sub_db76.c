/* ROM6 0xDB7F SUB_DB76 -- 2w guarded high-store, one EXPECT.
 * Verified encoding: src/rom6/kernel/db7f_sub_db76.asm (recombine MATCH).
 * ORIGIN 0xDB7F
 * EXPECT: FD30 825B
 *
 * Intent: TC clear stores *(0x5B) = A-high (xc 1,tc skips the sth iff
 * TC set; XC skips WORDS per op_xc). A and TC ride in from entry.
 * Called via F074 @DCE2 + calld @DD2B (per header); the span is the
 * RETD @DB7E delay pair. Bound DB7F-DB80.
 */
void sub_DB76(long a_live, int tc_live)
{
    if (!tc_live)                                    /* xc 1,tc */
        *(volatile int *)0x5B = (int)((a_live >> 16) & 0xFFFF); /* sth */
}
