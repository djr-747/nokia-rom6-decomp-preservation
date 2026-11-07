/* ROM6 0xAF40 ROUTINE_AF40 -- 23w.
 * Verified encoding: src/rom6/kernel/af40_routine_af40.asm (recombine MATCH).
 * ORIGIN 0xAF40
 * EXPECT: 4A11 E800 60F8 250F 0022 F820 AF4B 10F8 3490 F030 0007 80F8 0011 F495 F495 71E1 B55F 352C 71E1 B562 352D 8A11 FC00
 *
 * Intent: Flag-cell copy with in-span gate. Saves AR1 (pshm, hardware state); A = 0; cell 0x250F == 34 loads A = cell 0x3490 AND 7 (bc 0xaf4b,ntc skips the two loads, landing on the store with A = 0, exact); stores A-low to cell 0x11; two nops; cells 0x352C/0x352D = *(saved AR1 + 0xB55F/0xB562) (mvdk indirect with offset); restores AR1 (popm, hardware state); return.
 */
void routine_AF40(int *par1_saved)
{
    int a = 0;                                       /* pshm ar1; ld #0,a */
    if (*(volatile int *)0x250F == 34) {            /* cmpm, bc ntc */
        a = *(volatile int *)0x3490 & 7;         /* ld, and #7,a */
    }
    *(volatile int *)0x11 = a;                 /* stl a,*(0x11) */
    /* nop; nop */
    *(volatile int *)0x352C = *(par1_saved + 0xB55F); /* mvdk */
    *(volatile int *)0x352D = *(par1_saved + 0xB562); /* mvdk */
    /* popm ar1 (hardware state, no C form) */
    /* ret */
}
