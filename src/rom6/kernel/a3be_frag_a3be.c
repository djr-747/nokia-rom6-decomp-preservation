/* ROM6 0xA3BE FRAG_A3BE -- 7w.
 * Verified encoding: src/rom6/kernel/a3be_frag_a3be.asm (recombine MATCH).
 * ORIGIN 0xA3BE
 * EXPECT: FC45 F274 3E53 6882 F3FF E900 FC00
 *
 * Intent: flag-gated call. A is live-in (branch entry F84D@A3AC). When
 * A reads zero (rc aeq conditional prefix, exact skip semantics in the
 * .asm), call 0x3E53. The two calld delay-slot ops always execute:
 * clear low bits of *AR2 (andm -3073), then B = 0. Return.
 */
extern void sub_3E53(void);

void frag_A3BE(int a_in, int *par2)
{
    *par2 &= -3073;                            /* calld delay slot: always */
    if (a_in == 0)                             /* rc aeq */
        sub_3E53();                            /* calld 0x3e53 */
    /* ld #0,b runs in the second delay slot either way; ret */
}
