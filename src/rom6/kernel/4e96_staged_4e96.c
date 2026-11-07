/* ROM6 ORIGIN 0x4E96 (38w): STAGED_4E96 -- quad 4EBC staging then 4F5F.
 * Verified encoding: src/rom6/kernel/4e96_staged_4e96.asm (recombine MATCH).
 * EXPECT: F074 0670 7714 2F00 32F8 0016 7710 2F80 F274 4EBC 7712 DCC2 6D94 F274 4EBC 7712 DCFB 6D94 7710 2F81 F274 4EBC 7712 DCC2 6D94 F274 4EBC 7712 DCFB 7712 2F80 7713 0457 F274 4F5F 7711 000E FC00
 *
 * Intent: dark call 0x670. AR4 = 12032; ASM = cell 0x16 (ST1 ASM field,
 * read once); AR0 = 12160. Four calld to RPTB_MATH_4EBC (each delay stm
 * runs first): AR2 = 0xDCC2 (-9022) / 0xDCFB (-8965) alternating,
 * AR4 stepping 12032..12035 (mar *ar4+ after the first three calls),
 * AR0 = 12160 for the first two then 12161, AR3 threading entry-live
 * through all four (the callee advances AR2/AR3 via its ppar writeback;
 * AR2 is reset by each delay so only AR3 carries across). AR2 = 12160,
 * AR3 = 1111, calld pooled FRAG_4F5F (delay AR1 = 28: its banz loop
 * count; pooled span takes no C params, setup noted). Ret. AR3-entry
 * caller param (walk base); AR0/AR2/AR4/ASM/AR1 set in-span; A/B dead
 * (never read); TC untouched. Bound 4E96-4EBB.
 */
extern void sub_0670(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void rptb_math_4EBC(int **ppar2, int **ppar3, int *par4,
                           int ar0_live, int asm_live);
extern void frag_4F5F(void); /* joins 4f5f_rolror_banz_4f5f; see docs/evidence/extern-triage.md */

void staged_4E96(int *ar3_in)
{
    int *ar2;
    int *ar3 = ar3_in;
    int *ar4;
    int ar0;
    int asm_live;

    sub_0670();                                        /* call 0x670 (dark) */
    ar4 = (int *)12032;                                /* stm #12032,ar4 */
    asm_live = *(volatile int *)0x16;                  /* ld *(0x16),asm */
    ar0 = 12160;                                       /* stm #12160,ar0 */
    /* calld 0x4ebc (delay stm #-9022,ar2 runs first) */
    ar2 = (int *)0xDCC2;
    rptb_math_4EBC(&ar2, &ar3, ar4, ar0, asm_live);
    ar4++;                                             /* mar *ar4+ */
    /* calld 0x4ebc (delay stm #-8965,ar2 runs first) */
    ar2 = (int *)0xDCFB;
    rptb_math_4EBC(&ar2, &ar3, ar4, ar0, asm_live);
    ar4++;                                             /* mar *ar4+ */
    ar0 = 12161;                                       /* stm #12161,ar0 */
    /* calld 0x4ebc (delay stm #-9022,ar2 runs first) */
    ar2 = (int *)0xDCC2;
    rptb_math_4EBC(&ar2, &ar3, ar4, ar0, asm_live);
    ar4++;                                             /* mar *ar4+ */
    /* calld 0x4ebc (delay stm #-8965,ar2 runs first) */
    ar2 = (int *)0xDCFB;
    rptb_math_4EBC(&ar2, &ar3, ar4, ar0, asm_live);
    ar2 = (int *)12160;                                /* stm #12160,ar2 */
    ar3 = (int *)1111;                                 /* stm #1111,ar3 */
    /* calld 0x4f5f (delay stm #14,ar1 runs first; pooled, setup noted) */
    frag_4F5F();
    /* ret */
}
