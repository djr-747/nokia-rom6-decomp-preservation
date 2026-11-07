/* ROM6 0x6666 FRAG_6666 -- 19w.
 * Verified encoding: src/rom6/kernel/6666_frag_6666.asm (recombine MATCH).
 * ORIGIN 0x6666
 * EXPECT: F200 0006 0885 F846 676A 8185 F074 697F 7711 2617 10F8 053D 8081 F010 0033 F842 6672 F073 676A
 *
 * Intent: Threshold gate with save plus retest. A = B-live-in + 6 - *AR5-live-in; positive tail-enters 0x676A (bc 0x676a,agt: has .asm, no C yet, forward extern). Else stores B to *AR5, runs DARAM save/restore 0x697F (C: daram_save_restore), copies cell 0x53D to cell 9751, A -= 51, non-negative jumps away to dark 0x6672 (bc 0x6672,ageq, forward extern); else tail-enters 0x676A. AGT = A > 0 per 6871 precedent. Bound 6666-6678.
 */
extern void frag_676A(void); /* joins 676a_branch_tail_676a; see docs/evidence/extern-triage.md */
extern void daram_save_restore(void);
extern void frag_6672(void); /* joins 6666_frag_6666 interior @+0xC; see docs/evidence/extern-triage.md */

void frag_6666(int b_live, int *par5)
{
    int a = b_live + 6 - *par5;              /* add #6,b,a; sub *ar5,a */
    if (a > 0) {                                 /* bc 0x676a,agt */
        frag_676A();                             /* tail, unbound C */
        return;
    }
    *par5 = b_live;                              /* stl b,*ar5 */
    daram_save_restore();                        /* call 0x697f */
    /* stm #9751,ar1 */
    *(volatile int *)9751 =
        *(volatile int *)0x53D;              /* ld; stl a,*ar1 */
    a = *(volatile int *)0x53D - 51;         /* sub #51,a */
    if (a >= 0) {                                /* bc 0x6672,ageq */
        frag_6672();                             /* away, dark */
        return;
    }
    frag_676A();                                 /* b 0x676a tail */
}
