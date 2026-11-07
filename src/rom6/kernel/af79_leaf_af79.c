/* ROM6 0xAF79 LEAF_AF79 -- 5w.
 * Verified encoding: src/rom6/kernel/af79_leaf_af79.asm (recombine MATCH).
 * ORIGIN 0xAF79
 * EXPECT: F274 A2B9 7715 DD67 FC00
 *
 * Intent: A2B9 primitive wrapper. AR5 preset -8857 (calld delay slot, executes before the call takes effect), then the table-walker primitive, return. Same family as FRAG_A269 call sites.
 */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_AF79(int ***ppp5)
{
    G_AR5 = (int *)-8857;                        /* calld delay slot */
    msg_primitive_A2B9(ppp5);                    /* calld 0xa2b9 */
    /* ret */
}
