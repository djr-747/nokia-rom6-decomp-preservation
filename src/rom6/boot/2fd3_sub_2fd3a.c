/* ROM6 0x2FD3 SUB_2FD3A -- 21w.
 * Verified encoding: src/rom6/boot/2fd3_sub_2fd3a.asm (recombine MATCH).
 * ORIGIN 0x2FD3
 * EXPECT: 12D2 F130 00FF F0F8 8913 F130 0002 F84D 2FE8 69F8 2549 0200 F130 0001 F84C 2FF2 69F8 2512 0200 F073 2FF2
 *
 * Intent: Bit-test dispatch tail (continuation of SUB_2F51 past its
 * 2FD1 dispatch tail; TRACE entry per the header). A = *AR2++ unsigned
 * (ldu *ar2+%,a; circular BK wrap flagged, linear ++ in C). B = A &
 * 255 (and #255,a,b); A >>= 8 logical (sftl a,-8; A >= 0 from the
 * ldu, so logical == arith, exact). AR3 = B-low (stlm b,ar3; unused
 * in-span, caller-observable, flagged not-carried). B = A & 2, zero
 * enters SUB_2FD3B (bc 0x2fe8,beq; C-bound this wave, A/AR2 live).
 * Else cell 0x2549 |= 512 (orm); B = A & 1, nonzero enters the 2FF2
 * join (bc 0x2ff2,bneq; mid-span entry into the 2FD3B span, C-bound
 * frag_2FF2 per the 5371 precedent). Else cell 0x2512 |= 512 (orm)
 * then the same 2FF2 tail (b 0x2ff2).
 */
extern void sub_2FD3B(long a, int *ar2);           /* C-bound */
extern void frag_2FF2(long a, int *ar2);             /* mid-span entry into the 2FD3B span */

void sub_2FD3A(int *ar2_io)
{
    long a = (long)(unsigned)*ar2_io++;              /* ldu *ar2+%,a (BK wrap flagged) */
    long b;
    int *ar3;
    b = a & 255L;                                    /* and #255,a,b */
    a >>= 8;                                         /* sftl a,-8 (a >= 0, exact) */
    ar3 = (int *)(long)(b & 0xFFFFL);                /* stlm b,ar3 (caller-out, not carried) */
    b = a & 2L;                                      /* and #2,a,b */
    if (b == 0) {                                    /* bc 0x2fe8,beq */
        sub_2FD3B(a, ar2_io);
        return;
    }
    *(volatile int *)0x2549 |= 512;                  /* orm #512,*(0x2549) */
    b = a & 1L;                                      /* and #1,a,b */
    if (b != 0) {                                    /* bc 0x2ff2,bneq */
        frag_2FF2(a, ar2_io);
        return;
    }
    *(volatile int *)0x2512 |= 512;                  /* orm #512,*(0x2512) */
    frag_2FF2(a, ar2_io);                            /* b 0x2ff2 */
    (void)ar3;
}
