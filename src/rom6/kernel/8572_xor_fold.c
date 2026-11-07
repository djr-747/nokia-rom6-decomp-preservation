/* ROM6 0x8572 XOR_FOLD_8572 -- 5w leaf.
 * Verified encoding: src/rom6/kernel/8572_xor_fold.asm (recombine MATCH).
 * ORIGIN 0x8572
 * EXPECT: E800 1C82 1C93 8092 FC00
 *
 * Intent: fold two 16-bit cells into one. A holds the running value,
 * AR2 points at the accumulator cell (updated in place), AR3 at the
 * second source (advanced past). Callers pass both pointers in AR2/AR3.
 * TI C54x dialect: int is 16 bits. No cl500 codegen check yet: this file
 * states intent; tools/check_c.py binds the EXPECT words to the ROM.
 */
int xor_fold(int *acc, int *src)
{
    int a = 0;      /* ld #0,a */
    a ^= (unsigned short)*acc;   /* xor *ar2,a (Smem zero-ext) */
    a ^= (unsigned short)*src++; /* xor *ar3+,a (Smem zero-ext) */
    *acc++ = a;     /* stl a,*ar2+ */
    return a;       /* ret: A holds return */
}
