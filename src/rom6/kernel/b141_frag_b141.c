/* ROM6 0xB141 FRAG_B141 -- 5w.
 * Verified encoding: src/rom6/kernel/b141_frag_b141.asm (recombine MATCH).
 * ORIGIN 0xB141
 * EXPECT: F274 A2B9 7715 DE1C FC00
 *
 * Intent: A2B9 primitive wrapper. AR5 preset -8676 (calld delay slot, executes before the call takes effect), then the table-walker primitive, return. Same family as FRAG_A269 call sites.
 */
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_B141(int ***ppp5)
{
    G_AR5 = (int *)-8676;                        /* calld delay slot */
    msg_primitive_A2B9(ppp5);                    /* calld 0xa2b9 */
    /* ret */
}
