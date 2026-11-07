/* ROM6 0xA25F FRAG_A25F -- 5w.
 * Verified encoding: src/rom6/kernel/a25f_frag_a25f.asm (recombine MATCH).
 * ORIGIN 0xA25F
 * EXPECT: F274 A2B9 7715 DD9B FC00
 *
 * Intent: A2B9 primitive wrapper. AR5 preset -8805 (calld delay slot, executes before the call takes effect), then the table-walker primitive, return. Same family as FRAG_A269 call sites.
 */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_A25F(int ***ppp5)
{
    G_AR5 = (int *)-8805;                        /* calld delay slot */
    msg_primitive_A2B9(ppp5);                    /* calld 0xa2b9 */
    /* ret */
}
