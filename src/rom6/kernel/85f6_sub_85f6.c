/* ROM6 0x85F6 SUB_85F6 -- 7w.
 * Verified encoding: src/rom6/kernel/85f6_sub_85f6.asm (recombine MATCH).
 * ORIGIN 0x85F6
 * EXPECT: 108A F493 1A8B 6D8C 1C84 8084 FC00
 *
 * Intent: bitwise combine leaf. Complement the *AR2 cell, OR in
 * the *AR3 cell, step AR4 back one, XOR with that cell and store
 * back. All single-word 16-bit ops; C matches bitwise exactly.
 */
void sub_85F6(int **pp2, int **pp3, int **pp4)
{
    int a;
    a = ~(*(*pp2)--);                     /* ld *ar2-,a; cmpl a */
    a |= (unsigned short)*(*pp3)--;        /* or *ar3-,a (Smem zero-ext) */
    (*pp4)--;                             /* mar *ar4- */
    a ^= (unsigned short)**pp4;            /* xor *ar4,a (Smem zero-ext) */
    **pp4 = a;                            /* stl a,*ar4 */
    /* ret */
}
