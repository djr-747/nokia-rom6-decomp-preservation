/* ROM6 0x2867 FRAG_2867 -- 14w.
 * Verified encoding: src/rom6/boot/2867_frag_2867.asm (recombine MATCH).
 * ORIGIN 0x2867
 * EXPECT: 69F8 0866 0001 74F8 0008 0002 F040 0002 F495 75F8 0008 0002 F073 283D
 *
 * Intent: Port 2 set-bit strobe. Sets bit 0 of cell 0x866; A = port 2 (portr 2,*(0x8): AL alias) OR 2, written back to the cell and out to port 2 (portw *(0x8),2); tail-enters dark 0x283D (b, forward extern). Bound 2867-2874.
 */
extern int port_read_2(void);                                         /* HW port 2 (FRAME sample combine per 27EB span); no ROM definition */
extern void port_write_2(int v);                                      /* HW port 2 (supervisor per 2875 precedent); no ROM definition */
extern void frag_283D(void); /* joins 2800_stretch_2800 interior @+0x3D; see docs/evidence/extern-triage.md */

void frag_2867(void)
{
    int a;
    *(volatile int *)0x866 |= 1;             /* orm #1 */
    a = port_read_2();                           /* portr 2,*(0x8) */
    a |= 2;                                      /* or #2,a */
    *(volatile int *)0x8 = a;                /* AL alias write */
    /* nop */
    port_write_2(a);                             /* portw *(0x8),2 */
    frag_283D();                                 /* b 0x283d tail */
}
