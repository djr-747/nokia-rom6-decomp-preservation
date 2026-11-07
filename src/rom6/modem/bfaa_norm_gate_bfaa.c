/* ROM6 0xBFAA NORM_GATE_BFAA -- 13w.
 * Verified encoding: src/rom6/modem/bfaa_norm_gate_bfaa.asm (recombine MATCH).
 * ORIGIN 0xBFAA
 * EXPECT: F074 06DE F6B9 F7B8 F7B6 1092 FA44 BFB7 1C43 8068 FE00 768A 0000
 *
 * Intent: normalize gate. Helper call, set fract/sign-extend modes
 * (clear OVM, set SXM/FRCT), load sample *AR2++. If nonzero, the
 * delayed branch chains to stage 0xBFB7; the delay slots (xor 0x43,
 * store to 0x68) run either way. Zero falls to delayed return with
 * a zero spill that clears the next cell.
 */
extern void helper_06DE(void);
extern void stage_BFB7(void);   /* chained continuation, extern to link */

void norm_gate_BFAA(int **pp)
{
    int a;
    helper_06DE();                              /* call 0x6de */
    /* rsbx st1,ovm / ssbx st1,sxm / ssbx st1,frct: fract mode on */
    a = *(*pp)++;                               /* ld *ar2+,a */
    if (a) {                                    /* bcd 0xbfb7,aneq */
        a ^= 0x43;                              /* delay slot 1 */
        *(volatile int *)0x68 = a;              /* delay slot 2 */
        stage_BFB7();
    } else {
        a ^= 0x43;
        *(volatile int *)0x68 = a;
        **pp = 0;                               /* retd / st #0,*ar2- */
    }
}
