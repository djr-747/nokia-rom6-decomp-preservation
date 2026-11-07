/* ROM6 0x2B45 FRAG_2B45 -- 14w.
 * Verified encoding: src/rom6/boot/2b45_frag_2b45.asm (recombine MATCH).
 * ORIGIN 0x2B45
 * EXPECT: F074 064E 7682 0040 F495 7582 0001 EC0D F495 69F8 0552 2000 F073 283D
 *
 * Intent: Port 1 strobe plus flag. Runs 0x64E (dark, forward extern); stores 64 through live-in AR2 and out to port 1 (portw *ar2,1); 14 idle cycles (rpt #13 nop); sets bit 13 of cell 0x552 (orm #8192); tail-enters dark 0x283D (b, forward extern). Bound 2B45-2B52.
 */
extern void sub_064E(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void port_write_1(int v);                                      /* HW port 1 (RF/codec per 3EE1 sweep); no ROM definition */
extern void frag_283D(void); /* joins 2800_stretch_2800 interior @+0x3D; see docs/evidence/extern-triage.md */

void frag_2B45(int *par2)
{
    int i;
    sub_064E();                                  /* call 0x64e */
    *par2 = 64;                                  /* st #64,*ar2 */
    /* nop */
    port_write_1(64);                            /* portw *ar2,1 */
    for (i = 0; i < 14; i++) {}                  /* rpt #13; nop */
    *(volatile int *)0x552 |= 8192;          /* orm #8192 */
    frag_283D();                                 /* b 0x283d tail */
}
