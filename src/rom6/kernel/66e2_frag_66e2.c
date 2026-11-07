/* ROM6 0x66E2 FRAG_66E2 -- 43w.
 * Verified encoding: src/rom6/kernel/66e2_frag_66e2.asm (recombine MATCH).
 * ORIGIN 0x66E2
 * EXPECT: 11F8 054F F230 0100 F845 66F2 F074 68A2 6F85 0E20 F842 66F2 8185 76F8 056C 0001 11F8 054F F230 8000 F845 676A F074 688D 6F85 0E20 F842 676A 1085 8185 F300 0004 F520 F84D 6708 76F8 056C 0000 69F8 051E 0400 F073 676A
 *
 * Intent: Masked compare-and-rebias pair. B = cell 0x54F, A = B AND 256, zero runs dark 0x66F2 (bc aeq, forward extern). Else runs dark SUB_68A2; A = B minus *AR5-entry (SUB Xmem,SHFT,src,dst with SHFT 0, AR5 threaded as param, unstepped), non-negative runs 0x66F2 (bc ageq, signed per 6871). Else *AR5-entry = B low, cell 0x56C = 1. Second verse: B = cell 0x54F, A = B AND -32768, zero tail-enters dark 0x676A (bc aeq). Else runs dark SUB_688D; A = B minus *AR5, non-negative tail-enters 0x676A (bc ageq). Else A = *AR5, *AR5 = B low; B += 4, B -= A; nonzero clears cell 0x56C (bc beq skips the store when B == 0, same shape as 4474); sets bit 10 of cell 0x51E; tail-enters dark 0x676A (b). 16-bit narrowing noted throughout. Bound 66E2-670C.
 */
extern void frag_66F2(void);
extern void sub_68A2(void);
extern void sub_688D(void);
extern void frag_676A(void);

void frag_66E2(int *par5)
{
    int a, b;
    b = *(volatile int *)0x54F;                /* ld */
    a = b & 256;                                   /* and #256,b,a */
    if (a == 0) {                                  /* bc 0x66f2,aeq */
        frag_66F2();                               /* away, dark */
        return;
    }
    sub_68A2();                                    /* call 0x68a2 */
    a = b - *par5;                                 /* sub *ar5,b,a */
    if (a >= 0) {                                  /* bc 0x66f2,ageq */
        frag_66F2();                               /* away, dark */
        return;
    }
    *par5 = b & 0xFFFF;                            /* stl b,*ar5 */
    *(volatile int *)0x56C = 1;                /* st */
    b = *(volatile int *)0x54F;                /* ld */
    a = b & -32768;                                /* and #-32768,b,a */
    if (a == 0) {                                  /* bc 0x676a,aeq */
        frag_676A();                               /* tail, dark */
        return;
    }
    sub_688D();                                    /* call 0x688d */
    a = b - *par5;                                 /* sub *ar5,b,a */
    if (a >= 0) {                                  /* bc 0x676a,ageq */
        frag_676A();                               /* tail, dark */
        return;
    }
    a = *par5;                                     /* ld *ar5,a */
    *par5 = b & 0xFFFF;                            /* stl b,*ar5 */
    b += 4;                                        /* add #4,b */
    b -= a;                                        /* sub a,b */
    if (b != 0) {                                  /* bc 0x6708,beq skips */
        *(volatile int *)0x56C = 0;            /* st */
    }
/* l6708: */
    *(volatile int *)0x51E |= 1024;            /* orm */
    frag_676A();                                   /* b 0x676a tail */
}
