/* ROM6 0x8611 COPY14_8611 -- 13w.
 * Verified encoding: src/rom6/kernel/8611_copy14_8611.asm (recombine MATCH).
 * ORIGIN 0x8611
 * EXPECT: 4A15 EC05 E58B 8A15 7712 04F5 4492 1A8A 4595 1B8D F1C0 8395 818D FC00
 *
 * Intent: 32-bit XOR combine. Copy 6 cells AR2 to AR5 (AR5
 * save/restored), then form two 32-bit words (high cell shifted 16
 * plus low cell) and XOR them back into the AR5 pair. All values
 * stay within 32 bits, so unsigned-long C matches the accumulator
 * bitwise; exact 40-bit wrap lives in the .asm.
 */
void copy14_8611(int *p2, int *p5)
{
    int i;
    unsigned long a, b;
    for (i = 0; i < 6; i++)                       /* pshm; rpt #5 */
        p5[i] = p2[i];                            /* mvdd; popm */
    p2 = (int *)1269;                             /* stm #1269,ar2 */
    a = ((unsigned long)(unsigned short)p2[0] << 16)   /* ld, or */
        | (unsigned short)p2[1];
    b = ((unsigned long)(unsigned short)p5[0] << 16)
        | (unsigned short)p5[1];
    b ^= a;                                       /* xor a,b */
    p5[0] = (unsigned short)(b >> 16);            /* sth b,*ar5+ */
    p5[1] = (unsigned short)b;                    /* stl b,*ar5- */
    /* ret @861E (exit; gap orphan annexed wave-13) */
}
