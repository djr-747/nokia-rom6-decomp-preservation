/* ROM6 0xA2B9 MSG_PRIMITIVE_A2B9 -- 10w.
 * Verified encoding: src/rom6/msg/a2b9_msg_primitive_a2b9.asm (recombine MATCH).
 * ORIGIN 0xA2B9
 * EXPECT: 1095 4A15 F4E3 8A15 F495 6085 00FF F820 A2B9 FC00
 *
 * Intent: computed-call table walker -- the identity dispatch
 * mechanism. Call the address in the current table cell (cala a,
 * AR5 save/restored around the call), advance, and repeat until
 * the next cell reads the 255 terminator. pshm/popm bracket the
 * indirect call; the self-branch (bc 0xa2b9,ntc) is the loop.
 */
typedef void (*msg_fn_t)(void);

void msg_primitive_A2B9(int ***ppp5)
{
    for (;;) {
        msg_fn_t f = (msg_fn_t)**ppp5;   /* ld *ar5+,a */
        (*ppp5)++;                        /* (post-increment) */
        f();                               /* pshm ar5 / cala a / popm ar5 */
        if (***ppp5 == 255)                /* cmpm *ar5,#255; bc ntc */
            return;
    }
}
