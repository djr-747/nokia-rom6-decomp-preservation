/* ROM6 0xB146 FRAG_B146 -- 5w.
 * Verified encoding: src/rom6/kernel/b146_frag_b146.asm (recombine MATCH).
 * ORIGIN 0xB146
 * EXPECT: F274 A2B9 7715 DE28 FC00
 *
 * Intent: A2B9 primitive wrapper. AR5 preset -8664 (calld delay slot), then the table-walker primitive, return. Same family as FRAG_A269 call sites.
 */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_B146(int ***ppp5)
{
    G_AR5 = (int *)-8664;                        /* calld delay slot */
    msg_primitive_A2B9(ppp5);                    /* calld 0xa2b9 */
    /* ret */
}
