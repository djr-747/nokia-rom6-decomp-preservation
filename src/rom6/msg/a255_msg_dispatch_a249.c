/* ROM6 0xA255 MSG_DISPATCH_A249 table -- 5w.
 * Verified encoding: src/rom6/msg/a255_msg_dispatch_a249.asm (recombine MATCH).
 * ORIGIN 0xA255
 * EXPECT: A25A A25F A264 A269 A2AC
 *
 * Intent: NOT code. Jump table of 5 code pointers consumed by the
 * BACC dispatch head at A249 (exit BACC F5E2@A254). Every entry names
 * an existing fragment symbol (FRAG_A25A/A25F/A264/A269/A2AC).
 * The checked-in .asm round-trips the same bytes through objdump
 * mnemonics; this file states what the bytes are.
 */
static const unsigned int msg_dispatch_a249[5] = {
    0xA25A, 0xA25F, 0xA264, 0xA269, 0xA2AC
};
