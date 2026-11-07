/* ROM6 0x692C SUB_692C -- 33w.
 * Verified encoding: src/rom6/kernel/692c_sub_692c.asm (recombine MATCH).
 * ORIGIN 0x692C
 * EXPECT: 10F8 0060 7711 038C 6F81 0D20 FC4E F110 0010 F84E 6940 F010 0001 880E F495 34E9 0001 FC30 F073 6954
 *
 * Intent: Bit-test gate with two early outs. A = cell 0x60, AR1 = 908; B = A minus *AR1 (SUB Xmem,SHFT,src,dst SHFT 0, 16-bit narrowing noted), positive returns (rc bgt, signed per 6871). B = A - 16 (SUB #lk SHFT-0 per op_sub_lk), positive runs C FRAG_6940 with A and AR1 (bc bgt, C-bound with (a_live, par1)). Else A -= 1, T = A low (stlm); TC = bit (15 - T&15) of *(AR1+1) (BITT Smem per ti-c54x op_bitt_smem: TC = Smem(15 - T(3:0)); plain-offset read, indirect-mode caveat cited); TC set returns (rc tc). Else tail-enters C FRAG_6954 (b, C-bound). Bound 692C-694C.
 */
extern void frag_6940(int a_live, int *par1);
extern void frag_6954(void);

void sub_692C(void)
{
    int a, b, t;
    int *ar1;
    int tc;
    a = *(volatile int *)0x60;                 /* ld */
    ar1 = (int *)(long)908;                        /* stm #908,ar1 */
    b = a - *ar1;                                  /* sub *ar1,a,b */
    if (b > 0) {
        return;                                    /* rc bgt */
    }
    b = a - 16;                                    /* sub #16,a,b */
    if (b > 0) {                                   /* bc 0x6940,bgt */
        frag_6940(a, ar1);                         /* away, C-bound */
        return;
    }
    a -= 1;                                        /* sub #1,a */
    t = a & 0xFFFF;                                /* stlm a,t */
    /* nop */
    tc = ((*(ar1 + 1) >> (15 - (t & 15))) & 1) != 0; /* bitt *+ar1(0x1) */
    if (tc) {
        return;                                    /* rc tc */
    }
    frag_6954();                                   /* b 0x6954 tail */
}
