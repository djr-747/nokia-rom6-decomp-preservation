/* ROM6 0x6867 FRAG_6867 -- 10w.
 * Verified encoding: src/rom6/kernel/6867_frag_6867.asm (recombine MATCH).
 * ORIGIN 0x6867
 * EXPECT: 74F8 0008 0003 F030 0100 FC44 69F8 263A 0080 FC00
 *
 * Intent: Port-bit gate. AL = port 3 (portr 3,*(0x8): DATA 0x8 aliases AL, accumulator follows the MMR alias as established at FRAG_3A8E); bit 8 set (rc aneq skips only when clear) sets bit 7 of cell 0x263A, return.
 */
extern int port_read_3(void);                                         /* HW port 3 (supervisor cell per 2088 span); no ROM definition */

void frag_6867(void)
{
    int a = port_read_3();                       /* portr; AL alias */
    *(volatile int *)0x8 = a;
    if ((a & 256) != 0)                          /* and #256,a; rc aneq */
        *(volatile int *)0x263A |= 128;       /* orm #128 */
    /* ret */
}
