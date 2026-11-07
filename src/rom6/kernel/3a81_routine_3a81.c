/* ROM6 0x3A81 ROUTINE_3A81 -- 13w.
 * Verified encoding: src/rom6/kernel/3a81_routine_3a81.asm (recombine MATCH).
 * ORIGIN 0x3A81
 * EXPECT: F074 0632 F074 3ADE F110 0040 F84D 3A8E F110 0020 FC4D E800 FC00
 *
 * Intent: Measure router. Runs 0x632 then 0x3ADE; A == 64 tail-enters FRAG_3A8E with B = 0 (bc 0x3a8e,beq, exact). Else B = A - 32; zero keeps A (rc beq skips the clear), nonzero clears A; returns A. Routine entry also reachable via calld F274@4D17.
 */
extern void sub_0632(void);
extern void sub_3ADE(void);
extern int frag_3A8E(int b_in);

int routine_3A81(int a_in)
{
    sub_0632();                                  /* call 0x632 */
    sub_3ADE();                                  /* call 0x3ade */
    if (a_in == 64)                              /* sub #64; bc beq */
        return frag_3A8E(0);                     /* tail entry, B = 0 */
    if (a_in - 32 != 0)                          /* sub #32; rc beq */
        a_in = 0;                                /* ld #0,a */
    return a_in;                                 /* ret */
}
