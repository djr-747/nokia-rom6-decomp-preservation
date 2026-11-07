/* ROM6 0x2A02 FRAG_2A02 -- 12w.
 * Verified encoding: src/rom6/boot/2a02_frag_2a02.asm (recombine MATCH).
 * ORIGIN 0x2A02
 * EXPECT: 6183 1000 F820 2A0E 7683 0010 7713 1278 7712 1272 F073 2A8A
 *
 * Intent: Preset gate. Bit 12 of *AR3-live-in set tail-enters FRAG_2A0E (bc 0x2a0e,ntc, C: frag_2A0E). Else stores 16 through AR3, presets AR3 = 4728 and AR2 = 4722, tail-enters FRAG_2A73 at 0x2A8A (b, forward extern). Bound 2A02-2A0D.
 */
extern void frag_2A0E(void);
extern void frag_2A73(void);

void frag_2A02(int *par3)
{
    if ((*par3 & 4096) != 0) {                   /* bitf, bc ntc */
        frag_2A0E();                             /* tail call */
        return;
    }
    *par3 = 16;                                  /* st #16,*ar3 */
    /* stm #4728,ar3; stm #4722,ar2 (dead presets) */
    frag_2A73();                                 /* b 0x2a8a tail */
}
