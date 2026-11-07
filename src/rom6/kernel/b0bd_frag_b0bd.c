/* ROM6 0xB0BD FRAG_B0BD -- 5w.
 * Verified encoding: src/rom6/kernel/b0bd_frag_b0bd.asm (recombine MATCH).
 * ORIGIN 0xB0BD
 * EXPECT: F274 A2B9 7715 DE02 FC00
 *
 * Intent: A2B9 primitive wrapper. AR5 preset -8702 (calld delay slot, executes before the call takes effect), then the table-walker primitive, return. Same family as FRAG_A269 call sites.
 */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_B0BD(int ***ppp5)
{
    G_AR5 = (int *)-8702;                        /* calld delay slot */
    msg_primitive_A2B9(ppp5);                    /* calld 0xa2b9 */
    /* ret */
}
