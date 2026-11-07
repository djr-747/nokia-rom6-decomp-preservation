/* ROM6 0xA99A FRAG_A99A -- 17w.
 * Verified encoding: src/rom6/kernel/a99a_frag_a99a.asm (recombine MATCH).
 * ORIGIN 0xA99A
 * EXPECT: 7712 2799 EC3A 7092 3044 61F8 051C 0001 FC20 10F8 3082 FC45 E800 EC3A 7308 2799 FC00
 *
 * Intent: Table copy plus conditional clear. AR2 = 10137; 59 copies (rpt #58) of cell 0x3044 through AR2 (mvkd); bit 0 of cell 0x51C set loads cell 0x3082 (bitf, rc ntc skips only when set... loads when set, else A stays live-in); A == 0 writes cell 0x2799 = AL = 0 (rc aeq gates ld #0,a; 59 mvmd al stores to the fixed cell); return. BITF any-bit TC per ti-c54x op_bitf.
 */
void frag_A99A(int a_live)
{
    int i;
    int *ar2 = (int *)10137;                     /* stm #10137,ar2 */
    int a = a_live;
    for (i = 0; i < 59; i++)                     /* rpt #58 */
        *ar2++ = *(volatile int *)0x3044;     /* mvkd */
    if ((*(volatile int *)0x51C & 1) != 0)       /* bitf, rc ntc */
        a = *(volatile int *)0x3082;         /* ld */
    if (a == 0) {                                /* rc aeq */
        for (i = 0; i < 59; i++)                 /* ld #0,a; rpt #58 */
            *(volatile int *)0x2799 = 0;      /* mvmd al,0x2799 */
    }
    /* ret */
}
