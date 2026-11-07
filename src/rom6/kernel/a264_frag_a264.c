/* ROM6 0xA264 FRAG_A264 -- 5w.
 * Verified encoding: src/rom6/kernel/a264_frag_a264.asm (recombine MATCH).
 * ORIGIN 0xA264
 * EXPECT: F274 A2B9 7715 DDA3 FC00
 *
 * Intent: A2B9 primitive wrapper. AR5 preset -8797 (calld delay slot, executes before the call takes effect), then the table-walker primitive, return. Same family as FRAG_A269 call sites.
 */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_A264(int ***ppp5)
{
    G_AR5 = (int *)-8797;                        /* calld delay slot */
    msg_primitive_A2B9(ppp5);                    /* calld 0xa2b9 */
    /* ret */
}
