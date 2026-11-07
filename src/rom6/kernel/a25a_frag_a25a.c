/* ROM6 0xA25A FRAG_A25A -- 5w.
 * Verified encoding: src/rom6/kernel/a25a_frag_a25a.asm (recombine MATCH).
 * ORIGIN 0xA25A
 * EXPECT: F274 A2B9 7715 DD93 FC00
 *
 * Intent: A2B9 primitive wrapper. AR5 preset -8813 (calld delay slot, executes before the call takes effect), then the table-walker primitive, return. Same family as FRAG_A269 call sites.
 */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_A25A(int ***ppp5)
{
    G_AR5 = (int *)-8813;                        /* calld delay slot */
    msg_primitive_A2B9(ppp5);                    /* calld 0xa2b9 */
    /* ret */
}
