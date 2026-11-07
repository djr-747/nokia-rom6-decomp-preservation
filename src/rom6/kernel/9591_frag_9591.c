/* ROM6 0x9591 FRAG_9591 -- 17w.
 * Verified encoding: src/rom6/kernel/9591_frag_9591.asm (recombine MATCH).
 * ORIGIN 0x9591
 * EXPECT: 6182 0600 F820 95A2 6182 0400 E902 F495 FD30 E904 81F8 21FE E800 F273 9667 6982 0080
 *
 * Intent: Two-bit select with delayed away-branch. Bits 9-10 of *AR2-live-in clear jumps away to FRAG_95A2 (bc 0x95a2,ntc: has .asm, no C yet, forward extern). Else B = 2, or 4 when bit 10 set (bitf plus xc 1,tc pair), stored to cell 0x21FE; A = 0 is dead (noted); orm #128,*AR4-live-in is the bd delay slot (always runs); branch to FRAG_9667 (bd 0x9667: has .asm, no C yet, forward extern). Bound 9591-95A1.
 */
extern void frag_95A2(void);
extern void frag_9667(void);

void frag_9591(int *par2, int *par4)
{
    int b;
    if ((*par2 & 1536) == 0) {                   /* bitf, bc ntc */
        frag_95A2();                             /* away, unbound C */
        return;
    }
    /* bitf *ar2,#1024; ld #2,b; xc 1,tc; ld #4,b */
    b = ((*par2 & 1024) != 0) ? 4 : 2;
    *(volatile int *)0x21FE = b;             /* stl b,*(0x21fe) */
    /* ld #0,a (dead, A unused after) */
    *par4 |= 128;                               /* bd delay: orm #128,*ar4 */
    frag_9667();                                 /* bd 0x9667 */
}
