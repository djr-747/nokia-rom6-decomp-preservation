/* ROM6 0x6973 SUB_6973 -- 12w.
 * Verified encoding: src/rom6/kernel/6973_sub_6973.asm (recombine MATCH).
 * ORIGIN 0x6973
 * EXPECT: F640 F073 6978 F110 0001 0181 0982 F520 F84A 697A F500 FC00
 *
 * Intent: Modulo-by-subtraction loop. A = live-in B; entry jumps over sub #1,a,b (b 0x6978 tail-merge, dead on entry, kept in bytes); B += *AR1, B -= *AR2; then B -= A until negative (sub a,b plus bc 0x697a,bgeq self-loop), B += A restores the remainder, return. Zero A hangs in asm and here alike.
 */
int sub_6973(int b_in, int *par1, int *par2)
{
    int a = b_in;                                /* ld b,a */
    int b = b_in + *par1 - *par2;                /* b 0x6978; add; sub */
    /* L6976 sub #1,a,b skipped on entry (tail-merge) */
    while ((b -= a) >= 0) {}                     /* sub a,b; bc bgeq */
    b += a;                                      /* add a,b */
    return b;                                    /* ret */
}
