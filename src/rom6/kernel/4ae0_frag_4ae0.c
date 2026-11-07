/* ROM6 0x4AE0 FRAG_4AE0 -- 19w.
 * Verified encoding: src/rom6/kernel/4ae0_frag_4ae0.asm (recombine MATCH).
 * ORIGIN 0x4AE0
 * EXPECT: 1185 F074 4590 76F8 2656 0000 60F8 250F 0022 F820 4ADF 76F8 366F 0000 76F8 37B0 0000 F073 4ADF
 *
 * Intent: B-lane join. B = *AR5-live-in into routine_4590 (C: routine_4590(int), B threaded); clears cell 0x2656; cell 0x250F != 34 tail-enters FRAG_4ADF (bc ntc, C: frag_4ADF). Else clears cells 0x366F/0x37B0, tail-enters FRAG_4ADF anyway (b). Bound 4AE0-4AF2.
 */
extern void routine_4590(int b_in);
extern void frag_4ADF(void);

void frag_4AE0(int *par5)
{
    int b = *par5;                               /* ld *ar5,b */
    routine_4590(b);                             /* call 0x4590 */
    *(volatile int *)0x2656 = 0;             /* st #0 */
    if (*(volatile int *)0x250F != 34) {         /* cmpm, bc ntc */
        frag_4ADF();                             /* tail call */
        return;
    }
    *(volatile int *)0x366F = 0;             /* st #0 */
    *(volatile int *)0x37B0 = 0;             /* st #0 */
    frag_4ADF();                                 /* b 0x4adf tail */
}
