/* ROM6 0x296A FRAG_296A -- 25w.
 * Verified encoding: src/rom6/boot/296a_frag_296a.asm (recombine MATCH).
 * ORIGIN 0x296A
 * EXPECT: F074 05F8 7682 1000 F495 7582 0001 EC09 F495 7712 263A 6182 0060 F830 2983 61F8 3EC8 0020 F820 283D 68F8 13D0 FBFF F073 283D
 *
 * Intent: Port 1 strobe with flag joins. Runs dark 0x5F8 (call, forward extern); stores 4096 through live-in AR2 and out to port 1 (portw *ar2,1); 10 idle cycles (rpt #9 nop); AR2 = 9786; bit 5-6 of cell 9786 set tail-enters FRAG_2983 (bc tc: has .asm, no C yet, forward extern). Bit 5 of cell 0x3EC8 clear jumps away to dark 0x283D (bc ntc, forward extern). Else clears bit 10 of cell 0x13D0 (andm #-1025), tail-enters dark 0x283D (b, forward extern). Bound 296A-2982.
 */
extern void sub_05F8(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void port_write_1(int v);                                      /* HW port 1 (RF/codec per 3EE1 sweep); no ROM definition */
extern void frag_2983(void);
extern void frag_283D(void); /* joins 2800_stretch_2800 interior @+0x3D; see docs/evidence/extern-triage.md */

void frag_296A(int *par2)
{
    int i;
    sub_05F8();                                  /* call 0x5f8 */
    *par2 = 4096;                                /* st #4096,*ar2 */
    /* nop */
    port_write_1(4096);                          /* portw *ar2,1 */
    for (i = 0; i < 10; i++) {}                  /* rpt #9; nop */
    /* stm #9786,ar2 (dead preset, bitf target follows) */
    if ((*(volatile int *)9786 & 96) != 0) {     /* bitf *ar2,#96; bc tc */
        frag_2983();                             /* tail, unbound C */
        return;
    }
    if ((*(volatile int *)0x3EC8 & 32) == 0) {   /* bitf, bc ntc */
        frag_283D();                             /* away, dark */
        return;
    }
    *(volatile int *)0x13D0 &= -1025;        /* andm #-1025 */
    frag_283D();                                 /* b 0x283d tail */
}
