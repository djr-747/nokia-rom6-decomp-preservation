/* ROM6 0xDAC9 FRAG_DAC9 -- 6w.
 * Verified encoding: src/rom6/kernel/dac9_frag_dac9.asm (recombine MATCH).
 * ORIGIN 0xDAC9
 * EXPECT: 105E F844 DACF FE00 765F 0000
 *
 * Intent: FRAG_DAC9 zero-gated delayed return (6w, ROM slice verified: no listing row). A = cell 0x5E (page-0 direct), nonzero runs C FRAG_DACF (bc aneq, C-bound). Else cell 0x5F = 0 in the retd delay slot (always runs); returns. A dies on the fall path, void.
 */
extern void frag_DACF(void);

void frag_DAC9(void)
{
    int a = *(volatile int *)0x5E;             /* ld 0x5e,a */
    if (a != 0) {                                  /* bc 0xdacf,aneq */
        frag_DACF();                               /* away, C-bound */
        return;
    }
    *(volatile int *)0x5F = 0;                 /* retd delay slot */
    /* retd: return */
}
