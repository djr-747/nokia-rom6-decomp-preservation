/* ROM6 0xAF7E LEAF_AF7E -- 5w.
 * Verified encoding: src/rom6/kernel/af7e_leaf_af7e.asm (recombine MATCH).
 * ORIGIN 0xAF7E
 * EXPECT: F274 A2B9 7715 DD73 FC00
 *
 * Intent: A2B9 primitive wrapper. AR5 preset -8845 (calld delay slot, executes before the call takes effect), then the table-walker primitive, return. Same family as FRAG_A269 call sites.
 */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_AF7E(int ***ppp5)
{
    G_AR5 = (int *)-8845;                        /* calld delay slot */
    msg_primitive_A2B9(ppp5);                    /* calld 0xa2b9 */
    /* ret */
}
