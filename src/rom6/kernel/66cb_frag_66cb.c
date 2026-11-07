/* ROM6 0x66CB FRAG_66CB -- 23w.
 * Verified encoding: src/rom6/kernel/66cb_frag_66cb.asm (recombine MATCH).
 * ORIGIN 0x66CB
 * EXPECT: 6F85 0E20 F842 676A 8185 6FF8 2FD7 0E00 F110 0033 7712 2617 FD4A F640 8082 7712 2615 F274 697F 7682 0000 F073 676A
 *
 * Intent: Save-conditional with delayed call. A = B-live-in - *AR5-live-in, non-negative tail-enters 0x676A (bc ageq: has .asm, no C yet, forward extern). Else stores B to *AR5; A = B + cell 0x2FD7 (add) then B = A - 51 (sub); B >= 0 copies B to A (xc 1,bgeq plus ld b,a) else A keeps B + cell; stores A to cell 9751; AR2 = 9749; runs DARAM save/restore 0x697F (calld, C: daram_save_restore; delay slot stores 0 to cell 9749, always runs first); tail-enters 0x676A (b, forward extern). SUB per op_sub. Bound 66CB-66E1.
 */
extern void frag_676A(void);
extern void daram_save_restore(void);

void frag_66CB(int b_live, int *par5)
{
    int a;
    int b = b_live;
    a = b - *par5;                               /* sub *ar5,b,a */
    if (a >= 0) {                                /* bc 0x676a,ageq */
        frag_676A();                             /* tail, unbound C */
        return;
    }
    *par5 = b;                                   /* stl b,*ar5 */
    a = b + *(volatile int *)0x2FD7;         /* add *(0x2fd7),b,a */
    b = a - 51;                                  /* sub #51,a,b */
    /* stm #9751,ar2 */
    if (b >= 0)                                  /* xc 1,bgeq */
        a = b;                                   /* ld b,a */
    *(volatile int *)9751 = a;               /* stl a,*ar2 */
    /* stm #9749,ar2 */
    *(volatile int *)9749 = 0;               /* calld delay: st #0 */
    daram_save_restore();                        /* calld 0x697f */
    frag_676A();                                 /* b 0x676a tail */
}
