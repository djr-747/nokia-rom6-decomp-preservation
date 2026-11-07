/* ROM6 0x3EBD FIR_COEFF_TABLE -- 3w port write, one EXPECT.
 * Verified encoding: src/rom6/kernel/3ebd_fir_coeff_table.asm (recombine MATCH).
 * ORIGIN 0x3EBD
 * EXPECT: 75F8 000C 0031
 *
 * Intent: The 3-word span decodes as one port write (the coefficient
 * table described in the .asm header lives around/after this; bytes
 * verified). Port 49 = *(0xC) (portw *(0x12... *(0xc),49). Runs into
 * the following words exterior. Bound 3EBD-3EBF.
 */
extern void port_write_49(int v);

void fir_coeff_table_3EBD(void)
{
    port_write_49(*(volatile int *)0xC);          /* portw *(0xc),49 */
    /* runs into following words exterior */
}
