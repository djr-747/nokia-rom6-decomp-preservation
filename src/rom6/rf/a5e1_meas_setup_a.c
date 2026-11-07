/* ROM6 0xA5E1 MEAS_SETUP_A -- 17w.
 * Verified encoding: src/rom6/rf/a5e1_meas_setup_a.asm (recombine MATCH).
 * ORIGIN 0xA5E1
 * EXPECT: F074 065A 61F8 2628 0200 FC20 E80C 11F8 2613 F274 3D79 7711 0733 76F8 022A 0001 FC00
 *
 * Intent: Measure setup A. Runs helper 0x65A; when bit 9 of cell 0x2628 is set (bitf any-bit TC per ti-c54x op_bitf; rc ntc skips the loads when the bit is clear): A = 12, B = cell 0x2613; calls 0x3D79 with AR1 = 1843 in the calld delay slot (executes first); sets cell 0x22A = 1, returns.
 */
extern void helper_065A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_3D79(void); /* joins 3d79_pshm_kernel_caller; see docs/evidence/extern-triage.md */

static int *G_AR1;

void meas_setup_A_A5E1(void)
{
    int a = 0, b = 0;
    helper_065A();                               /* call 0x65a */
    if ((*(volatile int *)0x2628 & 512) != 0) {  /* bitf, rc ntc */
        a = 12;                                  /* ld #12,a */
        b = *(volatile int *)0x2613;         /* ld *(0x2613),b */
    }
    (void)b;
    G_AR1 = (int *)1843;                         /* calld delay slot */
    sub_3D79();                                  /* calld 0x3d79 */
    *(volatile int *)0x22A = 1;              /* st #1 */
    /* ret */
}
