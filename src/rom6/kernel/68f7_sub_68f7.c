/* ROM6 0x68F7 SUB_68F7 -- 23w.
 * Verified encoding: src/rom6/kernel/68f7_sub_68f7.asm (recombine MATCH).
 * ORIGIN 0x68F7
 * EXPECT: 7711 038B 1081 7712 2627 76F8 0545 0000 F110 0010 F84E 690E F010 0001 880E F495 34E9 0002 F830 6928 FE00 6982 0100
 *
 * Intent: Bit-test gate with delayed return. AR1 = 907, A = *AR1, AR2 = 0x2627, cell 0x545 = 0. B = A - 16, positive runs C FRAG_690E with A and AR1/AR2 (bc bgt, C-bound with (a_live, par1, par2); A untouched by the SUB). Else A -= 1, T = A low; TC = bit (15 - T&15) of *(AR1+2) (BITT per op_bitt_smem, plain offset); TC set runs C FRAG_6928 (bc tc, C-bound). Else delayed return with cell 0x2627 |= 256 in the slot (retd: slot always runs, then return). Bound 68F7-690D.
 */
extern void frag_690E(int a_live, int *par1, int *par2);
extern void frag_6928(void);

void sub_68F7(void)
{
    int a, b, t;
    int *ar1, *ar2;
    int tc;
    ar1 = (int *)(long)907;                        /* stm #907,ar1 */
    a = *ar1;                                      /* ld *ar1,a */
    ar2 = (int *)(long)0x2627;                     /* stm #9767,ar2 */
    *(volatile int *)0x545 = 0;                /* st */
    b = a - 16;                                    /* sub #16,a,b */
    if (b > 0) {                                   /* bc 0x690e,bgt */
        frag_690E(a, ar1, ar2);                    /* away, C-bound */
        return;
    }
    a -= 1;                                        /* sub #1,a */
    t = a & 0xFFFF;                                /* stlm a,t */
    /* nop */
    tc = ((*(ar1 + 2) >> (15 - (t & 15))) & 1) != 0; /* bitt *+ar1(0x2) */
    if (tc) {                                      /* bc 0x6928,tc */
        frag_6928();                               /* away, C-bound */
        return;
    }
    *(volatile int *)0x2627 |= 256;            /* retd delay slot */
    /* retd: return */
}
