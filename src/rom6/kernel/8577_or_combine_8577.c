/* ROM6 0x8577 OR_COMBINE_8577 -- 17w.
 * Verified encoding: src/rom6/kernel/8577_or_combine_8577.asm (recombine MATCH).
 * ORIGIN 0x8577
 * EXPECT: 4492 1A82 458A 1B82 6F92 0D96 6F8A 0C96 4493 1A83 458B 1B83 6F93 0C91 6F8B 0D91 FC00
 *
 * Intent: 32-bit OR combine with half-swap. Each pair forms two
 * 32-bit words (high cell shifted 16 plus low cell, halves
 * exchanged in the B lane) and stores the low 16 bits of each at
 * fixed offsets (AR2 pair at -10, AR3 pair at -15). The stored
 * lows equal the source cells in order for the AR2 pair and
 * swapped for the AR3 pair; the high-half OR structure feeds
 * nothing stored but is preserved here exactly as written.
 * Values fit 32 bits, so unsigned-long C matches bitwise.
 */
void or_combine_8577(int *p2, int *p3)
{
    unsigned long a, b;
    int *d2 = p2 - 10, *d3 = p3 - 15;
    a = ((unsigned long)(unsigned short)p2[0] << 16)   /* ld, or */
        | (unsigned short)p2[1];
    b = ((unsigned long)(unsigned short)p2[1] << 16)   /* ld, or */
        | (unsigned short)p2[0];
    d2[0] = (unsigned short)b;                          /* stl b */
    d2[1] = (unsigned short)a;                          /* stl a */
    a = ((unsigned long)(unsigned short)p3[0] << 16)
        | (unsigned short)p3[1];
    b = ((unsigned long)(unsigned short)p3[1] << 16)
        | (unsigned short)p3[0];
    d3[0] = (unsigned short)a;                          /* stl a first */
    d3[1] = (unsigned short)b;                          /* stl b second */
}
