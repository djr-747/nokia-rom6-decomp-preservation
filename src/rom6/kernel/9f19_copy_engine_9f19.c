/* ROM6 0x9F19 COPY_ENGINE_9F19 -- 15w.
 * Verified encoding: src/rom6/kernel/9f19_copy_engine_9f19.asm (recombine MATCH).
 * ORIGIN 0x9F19
 * EXPECT: 4A08 4A09 4A0A 4A07 4482 ED00 F072 9F22 E518 C809 8A07 8A0A 8A09 8A08 FC00
 *
 * Intent: Push-preserved block copy. Saves AL/AH/AG/ST1 (pshm, hardware state); A = *AR2 << 16 (AR2 live-in); ASM = 0 (dead, no ASM use in block, noted); repeats BRC + 1 times (rptb 0x9f22, BRC live-in, block = mvdd plus parallel st||ld):repeats BRC + 1 times (rptb 0x9f22, BRC live-in, block = mvdd plus parallel st||ld): *AR2++ = *AR3 (AR3 fixed, live-in), then the parallel pair stores old A to *AR3++ while loading new A from *AR2 (sequentialized with a temp, same effect); restores ST1/AG/AH/AL (popm, hardware state); return.
 */
void copy_engine_9F19(int **ppar2, int *par3, int brc_in)
{
    int i;
    int *ar2 = *ppar2;
    int *ar3 = par3;
    int a;
    /* pshm al/ah/ag/st1 (hardware state, no C form) */
    a = *ar2 << 16;                              /* ld *ar2,16,a */
    /* ld #0,asm (dead: block uses no ASM) */
    for (i = 0; i <= brc_in; i++) {               /* rptb 0x9f22 */
        int old_a = a;
        *ar2++ = *ar3;                           /* mvdd *ar3,*ar2+ */
        *ar3++ = old_a;                          /* st a,*ar3+ (pair) */
        a = *ar2;                                /* ld *ar2,a (pair) */
    }
    /* popm st1/ag/ah/al (hardware state, no C form) */
    *ppar2 = ar2;
    /* ret */
}
