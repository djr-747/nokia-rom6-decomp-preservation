/* ROM6 0x3CC9 FRAG_3CC9 -- 9w.
 * Verified encoding: src/rom6/kernel/3cc9_frag_3cc9.asm (recombine MATCH).
 * ORIGIN 0x3CC9
 * EXPECT: F020 3A98 F495 75F8 0008 0007 EC11 F495 FC00
 *
 * Intent: Port write plus delay. A = 15000 (AL alias cell 0x8 follows); PORT[7] = AL; 18-nop delay (rpt #17), return.
 */
extern void port_write_7(int v);                                      /* HW port 7 (RF sweep per 3EE1 span); no ROM definition */

void frag_3CC9(void)
{
    int i;
    *(volatile int *)0x8 = 15000;                /* ld #15000,a (AL) */
    port_write_7(*(volatile int *)0x8);          /* portw *(0x8),7 */
    for (i = 0; i < 18; i++) {}                  /* rpt #17, nop */
    /* ret */
}
