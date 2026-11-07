/* ROM6 0x38F6 FRAG_38F6 -- 5w.
 * Verified encoding: src/rom6/kernel/38f6_frag_38f6.asm (recombine MATCH).
 * ORIGIN 0x38F6
 * EXPECT: 69F8 000C 6000 F640 FC00
 *
 * Intent: Status OR plus move. ORs 0x6000 into MMR cell 0x0C (hardware state op), copies B into A, returns.
 */
int frag_38F6(int b_in)
{
    /* orm #24576,*(0x0c): status-bit OR (hardware state, no C form) */
    return b_in;                               /* ld b,a; ret */
}
