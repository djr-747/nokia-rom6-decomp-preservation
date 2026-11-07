/* ROM6 0xA639 SUB_A639 -- 29w.
 * Verified encoding: src/rom6/kernel/a639_sub_a639.asm (recombine MATCH).
 * ORIGIN 0xA639
 * EXPECT: F074 065C 61F8 2628 2000 FC20 E809 11F8 260E 7711 0CAC 60F8 250F 0022 F820 A64B 7711 0D80 F074 3D79 68F8 2639 F3FF 69F8 2639 0400 FC00
 *
 * Intent: Cell test plus preset swap. Runs 0x65C; bit 13 of cell 0x2628 clear skips the presets (bitf, rc ntc); A = 9, B = cell 0x260E, AR1 = 3244; cell 0x250F != 34 skips the AR1 = 3456 preset (bc 0xa64b,ntc lands on the call, in-span); call 0x3D79; clears low 11 bits of cell 0x2639 except bit 10 (andm -3073) and sets bit 10 (orm #1024); return.
 */
extern void sub_065C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_3D79(void); /* joins 3d79_pshm_kernel_caller; see docs/evidence/extern-triage.md */

static int *G_AR1;

void sub_A639(void)
{
    int a, b;
    sub_065C();                                  /* call 0x65c */
    if ((*(volatile int *)0x2628 & 8192) == 0)   /* bitf, rc ntc */
        return;
    a = 9;                                      /* ld #9,a */
    b = *(volatile int *)0x260E;             /* ld *(0x260e),b */
    G_AR1 = (int *)3244;                         /* stm #3244,ar1 */
    (void)a; (void)b;
    if (*(volatile int *)0x250F == 34)            /* cmpm, bc ntc */
        G_AR1 = (int *)3456;                     /* stm (skipped when !=) */
    sub_3D79();                                  /* call 0x3d79 */
    *(volatile int *)0x2639 &= -3073;        /* andm #-3073 */
    *(volatile int *)0x2639 |= 1024;         /* orm #1024 */
    /* ret */
}
