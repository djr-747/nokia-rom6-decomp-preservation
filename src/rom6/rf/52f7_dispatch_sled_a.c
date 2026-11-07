/* ROM6 0x52F7 DISPATCH_SLED_A_52F7 -- 10w.
 * Verified encoding: src/rom6/rf/52f7_dispatch_sled_a.asm (recombine MATCH).
 * ORIGIN 0x52F7
 * EXPECT: 7711 2479 1381 F84D 5301 F310 0001 8181 F073 56B9
 *
 * Intent: Decrement-or-join gate. B = cell 9337 unsigned (stm plus ldu, AR1 dead after); zero tail-enters 0x5301 (bc 0x5301,beq: has .asm, no C yet, forward extern). Else B - 1 stored back to cell 9337 (sub plus stl), tail-enters dark 0x56B9 (b, forward extern). 10w per .asm header (Bound 52F7-5300; recombine MATCH).
 */
extern void frag_5301(void);
extern void frag_56B9(void);

void frag_52F7(void)
{
    int b;
    /* stm #9337,ar1 */
    b = (unsigned)*(volatile int *)9337;        /* ldu *ar1,b */
    if (b == 0) {                                    /* bc 0x5301,beq */
        frag_5301();                                 /* tail, unbound C */
        return;
    }
    b -= 1;                                          /* sub #1,b */
    *(volatile int *)9337 = b;                   /* stl b,*ar1 */
    frag_56B9();                                     /* b 0x56b9 tail */
}
