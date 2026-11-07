/* ROM6 0xAB78 LEAF_AB78 -- 10w.
 * Verified encoding: src/rom6/kernel/ab78_leaf_ab78.asm (recombine MATCH).
 * ORIGIN 0xAB78
 * EXPECT: F074 06A4 61F8 0577 0001 FC20 F071 009F 8092 FC00
 *
 * Intent: Conditional zero-fill. Runs 0x6A4; bit 0 of cell 0x577 set fills (bitf any-bit TC per ti-c54x op_bitf; rc ntc skips the fill when clear): A = 0 with 160 stores (rptz a,#159) through live-in AR2, return.
 */
extern void sub_06A4(void);

void leaf_AB78(int **ppar2)
{
    sub_06A4();                                  /* call 0x6a4 */
    if ((*(volatile int *)0x577 & 1) != 0) {     /* bitf, rc ntc */
        int i;
        for (i = 0; i < 160; i++) {              /* rptz a,#159 */
            **ppar2 = 0;                         /* stl a,*ar2+ */
            (*ppar2)++;
        }
    }
    /* ret */
}
