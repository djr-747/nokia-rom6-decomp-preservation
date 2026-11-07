/* ROM6 0x29B9 FRAG_29B9 -- 26w.
 * Verified encoding: src/rom6/boot/29b9_frag_29b9.asm (recombine MATCH).
 * ORIGIN 0x29B9
 * EXPECT: 6183 0002 F820 29D3 7683 0800 7713 1274 7712 126E 61F8 263B 0004 10F8 3F0F FF20 10F8 3F10 8093 768B 4A80 6BE2 0001 0028 F073 2A8A
 *
 * Intent: Conditional stage with live tail. Bit 1 of *AR3-live-in clear tail-enters FRAG_29D3 (bc ntc, C: frag_29D3 with entry AR3). Else stores 2048 through AR3; AR3 = 4724, AR2 = 4718 (locals now); A = cell 0x3F0F; bit 2 of cell 0x263B clear runs the next two (xc 2,ntc): A = cell 0x3F10 stored to *AR3++ (4724, AR3 to 4725); cell 4724/4725 = 19072 (st post-dec address is path-dependent, unobserved after, noted); cell 4719 += 40 (addm #40,*ar2(0x1)); tail-enters FRAG_2A73 at 0x2A8A (b: has .asm, no C yet, forward extern). BITF any-bit TC per op_bitf. Bound 29B9-29D2.
 */
extern void frag_29D3(int *par3);
extern void frag_2A73(void);

void frag_29B9(int *par2, int *par3)
{
    int a;
    int *ar2;
    int *ar3;
    if ((*par3 & 2) == 0) {                       /* bitf, bc ntc */
        frag_29D3(par3);                           /* tail call */
        return;
    }
    *par3 = 2048;                                 /* st #2048,*ar3 */
    ar3 = (int *)4724;                            /* stm #4724,ar3 */
    ar2 = (int *)4718;                            /* stm #4718,ar2 */
    a = *(volatile int *)0x3F0F;              /* ld *(0x3f0f),a */
    if ((*(volatile int *)0x263B & 4) == 0) {     /* bitf, xc 2,ntc */
        a = *(volatile int *)0x3F10;          /* ld *(0x3f10),a */
        *ar3++ = a;                                /* stl a,*ar3+ */
    }
    /* (xc 2nd slot is the stl above; A dead on tc path, noted) */
    *ar3-- = 19072;                               /* st #19072,*ar3- */
    *(ar2 + 1) += 40;                             /* addm #40,*ar2(0x1) */
    frag_2A73();                                   /* b 0x2a8a tail */
}
