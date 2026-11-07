/* ROM6 0x9B5C MSG_LEAF_9B5C -- 7w.
 * Verified encoding: src/rom6/msg/9b5c_msg_leaf_9b5c.asm (recombine MATCH).
 * ORIGIN 0x9B5C
 * EXPECT: 6D95 6C83 9B63 6D93 FE00 6F81 0C88
 *
 * Intent: null-check gate with chained continuation. Advance the
 * caller AR5 pointer, test *AR3: nonzero chains forward to stage
 * 0x9B63, zero returns delayed with a shifted store (stl a,8,*ar1)
 * in the delay slots.
 */
extern void stage_9B63(void);   /* chained continuation, extern to link */

void msg_leaf_9B5C(int **p5, int *p3, int a, int **p1)
{
    (*p5)++;                      /* mar *ar5+ */
    if (*p3)                      /* banz 0x9b63,*ar3 */
        stage_9B63();
    else {
        **p1 = a >> 8;            /* retd / stl a,8,*ar1 */
        return;
    }
}
