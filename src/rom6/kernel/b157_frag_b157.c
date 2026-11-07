/* ROM6 0xB157 FRAG_B157 -- 5w.
 * Verified encoding: src/rom6/kernel/b157_frag_b157.asm (recombine MATCH).
 * ORIGIN 0xB157
 * EXPECT: F274 A2B9 7715 DE44 FC00
 *
 * Intent: A2B9 primitive wrapper. AR5 preset -8636 (calld delay slot), then the table-walker primitive, return. Same family as FRAG_A269 call sites.
 */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_B157(int ***ppp5)
{
    G_AR5 = (int *)-8636;                        /* calld delay slot */
    msg_primitive_A2B9(ppp5);                    /* calld 0xa2b9 */
    /* ret */
}
