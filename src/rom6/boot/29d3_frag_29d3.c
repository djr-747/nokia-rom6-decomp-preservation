/* ROM6 0x29D3 FRAG_29D3 -- 14w.
 * Verified encoding: src/rom6/boot/29d3_frag_29d3.asm (recombine MATCH).
 * ORIGIN 0x29D3
 * EXPECT: 6183 0800 F820 29E1 7683 0004 7713 1276 7712 1270 6883 7FFF F073 2A8A
 *
 * Intent: Preset gate plus mask. Bit 11 of *AR3-live-in set jumps away to FRAG_29E1 (bc 0x29e1,ntc: has .asm, no C yet, forward extern). Else stores 4 through AR3, presets AR3 = 4726 and AR2 = 4720, clears bit 15 of cell 4726 (andm #32767), tail-enters FRAG_2A73 at 0x2A8A (b, forward extern). Bound 29D3-29E0.
 */
extern void frag_29E1(void);
extern void frag_2A73(void);

void frag_29D3(int *par3)
{
    if ((*par3 & 2048) != 0) {                   /* bitf, bc ntc */
        frag_29E1();                             /* away, unbound C */
        return;
    }
    *par3 = 4;                                   /* st #4,*ar3 */
    /* stm #4726,ar3; stm #4720,ar2 (dead presets) */
    *(volatile int *)4726 &= 32767;          /* andm #32767,*ar3 */
    frag_2A73();                                 /* b 0x2a8a tail */
}
