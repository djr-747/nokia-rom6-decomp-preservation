/* ROM6 0x4B81 SUB_4B81 -- 25w.
 * Verified encoding: src/rom6/kernel/4b81_sub_4b81.asm (recombine MATCH).
 * ORIGIN 0x4B81
 * EXPECT: F6B8 10F8 250D 7712 0491 F845 4B9A F010 0004 F845 4B9A 6892 0FFF 771A 0009 F072 4B97 944C 1A82 8092 6F82 0C5C 8092 F073 4BA6
 *
 * Intent: Double-gated fold loop. SXM off (rsbx, hardware state;
 * adds below use plain int->long conversion, consistent); A =
 * cell0x250D; AR2 = 1169; zero (twice-tested: before and after
 * A -= 4) tail-enters FRAG_4B9A with AR2 writeback (bc aeq x2;
 * C: frag_4B9A). Else cell1169 &= 4095 with AR2++ (andm,
 * 16-bit cell exact); 10 passes of A = (*AR2-- << 12) (LD Xmem,12
 * with SXM = 1 assumed flagged; fits long), A |= *AR2,
 * *(AR2++) = A-low, A = *AR2 >> 4 arithmetic (LD shift -8 family
 * per the 457f precedent, flagged), *(AR2++) = A-low (block
 * [RSA = PC + 2 = 0x4B92, REA = 0x4B97], BRC = 9); tail-branch
 * dark 0x4BA6 (2 words ahead of the 4BA8 routine; entry unbound,
 * flagged). Bound 4B81-4B99.
 */
extern void frag_4B9A(int **ppar2);
extern void frag_4BA6(void);

void sub_4B81(void)
{
    int *ar2;
    long a;
    int i;
    /* rsbx st1,sxm (hardware state) */
    a = (long)*(volatile int *)0x250D;               /* ld *(0x250d),a */
    ar2 = (int *)1169;                               /* stm #1169,ar2 */
    if (a == 0) {                                    /* bc 0x4b9a,aeq */
        frag_4B9A(&ar2);
        return;
    }
    a -= 4;                                          /* sub #4,a */
    if (a == 0) {                                    /* bc 0x4b9a,aeq */
        frag_4B9A(&ar2);
        return;
    }
    *ar2 &= 4095;                                    /* andm #4095,*ar2+ */
    ar2++;
    /* stm #9,brc */
    for (i = 0; i < 10; i++) {                       /* rptb 0x4b97 */
        a = (long)*ar2-- << 12;                      /* ld *ar2-,12,a */
        a |= (long)*ar2;                             /* or *ar2,a */
        *ar2++ = (int)(a & 0xFFFF);                  /* stl a,*ar2+ */
        a = (long)*ar2 >> 4;                         /* ld *ar2,-4,a (arith, flagged) */
        *ar2++ = (int)(a & 0xFFFF);                  /* stl a,*ar2+ */
    }
    frag_4BA6();                                     /* b 0x4ba6 (dark tail) */
}
