/* ROM6 0x6693 FRAG_6693 -- 20w.
 * Verified encoding: src/rom6/kernel/6693_frag_6693.asm (recombine MATCH).
 * ORIGIN 0x6693
 * EXPECT: 60F8 000B 0004 F820 66E2 7711 2FDB 61F8 051E 0008 F830 66AC 1081 F010 000E F843 66A7 E900 F073 66CB
 *
 * Intent: Entry gate with three tails. Cell 0xB (BL alias, compared as a cell) != 4 jumps away to FRAG_66E2 (cmpm plus bc ntc: CMPM TC-on-equal per op_cmpm; C: frag_66E2 with entry AR5). AR1 = 12251; bit 3 of cell 0x51E set tail-enters FRAG_66AC (bc tc, C: frag_66AC with AR1/AR6/AR5 passthrough). A = cell 12251 - 14, negative tail-enters FRAG_66A7 (bc alt, C: frag_66A7 with A plus AR6 passthrough). Else B = 0 tail-enters FRAG_66CB (C: frag_66CB; ld #0,b then b). AR5/AR6 untouched, passed through as params. Bound 6693-66A6.
 */
extern void frag_66E2(int *par5);
extern void frag_66AC(int *par1, int *par6, int *par5);
extern void frag_66A7(int a_live, int *par6);
extern void frag_66CB(int b_live, int *par5);

void frag_6693(int *par5, int *par6)
{
    int a;
    int *ar1;
    if (*(volatile int *)0xB != 4) {             /* cmpm, bc ntc */
        frag_66E2(par5);                         /* away, C: 66e2_frag_66e2.c */
        return;
    }
    ar1 = (int *)12251;                         /* stm #12251,ar1 */
    if ((*(volatile int *)0x51E & 8) != 0) {     /* bitf, bc tc */
        frag_66AC(ar1, par6, par5);              /* tail call */
        return;
    }
    a = *ar1 - 14;                               /* ld *ar1,a; sub #14,a */
    if (a < 0) {                                 /* bc 0x66a7,alt */
        frag_66A7(a, par6);                      /* tail call */
        return;
    }
    frag_66CB(0, par5);                          /* ld #0,b; b 0x66cb */
}
