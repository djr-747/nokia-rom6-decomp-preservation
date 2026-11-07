/* ROM6 0x44AF FRAG_44AF -- 3w.
 * Verified encoding: src/rom6/kernel/44af_frag_44af.asm (recombine MATCH).
 * ORIGIN 0x44AF
 * EXPECT: 7594 000D FC00
 *
 * Intent: Single port write. PORT[13] = *AR4++ (live-in pointer, post-increment), return.
 */
extern void port_write_13(int v);

void frag_44AF(int **ppar4)
{
    port_write_13(**ppar4);                      /* portw *ar4+,13 */
    (*ppar4)++;
    /* ret */
}
