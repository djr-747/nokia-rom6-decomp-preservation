/* ROM6 0x2BED FRAG_2BAA_SEG2 -- 22w.
 * Verified encoding: src/rom6/boot/2bed_frag_2baa.asm (recombine MATCH).
 * ORIGIN 0x2BED
 * EXPECT: 74F8 0008 0038 F030 FFF7 F495 75F8 0008 0038 F495 74F8 0008 0002 F040 0800 F495 75F8 0008 0002 F495 F073 283D
 *
 * Intent: Port 56/2 relay segment. A = port 56 (portr, AL alias) AND -9, out to port 56; A = port 2 OR 2048, out to port 2; tail-enters dark 0x283D (b, forward extern). Second segment of FRAG_2BAA (bounds 2BAA-2BEC + 2BED-2C02 per .asm header; entered via interior join, exit to 283D; recombine MATCH).
 */
extern int port_read_56(void);
extern void port_write_56(int v);
extern int port_read_2(void);
extern void port_write_2(int v);
extern void frag_283D(void);

void frag_2BAA_seg2(void)
{
    int a;
    a = port_read_56();                          /* portr 56,*(0x8) */
    *(volatile int *)0x8 = a;                /* AL alias write */
    a &= -9;                                     /* and #-9,a */
    /* nop */
    port_write_56(a);                            /* portw *(0x8),56 */
    /* nop */
    a = port_read_2();                           /* portr 2,*(0x8) */
    *(volatile int *)0x8 = a;                /* AL alias write */
    a |= 2048;                                   /* or #2048,a */
    /* nop */
    port_write_2(a);                             /* portw *(0x8),2 */
    /* nop */
    frag_283D();                                 /* b 0x283d tail */
}
