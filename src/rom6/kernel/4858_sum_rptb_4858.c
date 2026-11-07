/* ROM6 0x4858 SUM_RPTB_4858 -- 43w.
 * Verified encoding: src/rom6/kernel/4858_sum_rptb_4858.asm (recombine MATCH).
 * ORIGIN 0x4858
 * EXPECT: F074 059E 4915 F300 0024 8912 E800 E900 771A 002B F072 4865 0092 0192 7712 01F6 7713 01F4 4A0B 4A0C 4A0D E901 FD43 F784 0182 8192 8A0A 8A09 8A08 F300 0008 6F93 0D9C E901 FD43 F784 0182 8182 F300 0008 6F83 0D9C FC00
 *
 * Intent: Dual-sum fold with conditional high stores.
 * Runs 0x59E (dark, extern); B = zero-extended AR5
 * (ldm, oracle zero-extends; AR5 caller-live) + 36 (add
 * lk); AR2 = B-low (stlm; entry AR2 never read, so no
 * AR2 param); A = 0, B = 0 (ld pair); BRC = 43; 44
 * passes (rptb 0x4865) of A += *(AR2++) then B +=
 * *(AR2++) (add Smem, 1-word forms, SXM = 1 flagged).
 * AR2 = 502, AR3 = 500 (stm pair); B pushed (pshm
 * bl/bh/bg; the stack has no C form); B = 1, A < 0 keeps
 * B = 1 else B = -1 (xc 1,alt covers the 1-word neg;
 * A is the loop sum, sign-tested exactly); B += *(AR2)
 * (add Smem, SXM flagged); cell AR2 = B-low with AR2
 * post-incremented (stl); A popped from the B save
 * (popm ag/ah/al: A = accumulated B-sum; the push/pop
 * pair is modeled as the value move, stack notional per
 * 2D5E); B += 8 (add lk); cell AR3 = HIGH of (B
 * arith>>4) with AR3 post-incremented (stl b,-4,*ar3+:
 * STH-shift per the leaf -- bits 31-16 of the shifted
 * accumulator -- and the 8433 precedent; exact here
 * because |B| < 2^16 always (B = +/-1 plus one 16-bit
 * cell plus 8), so the store is 0xFFFF iff B < 0 else
 * 0). Second stanza: B = 1, A < 0 keeps else -1 (same
 * xc/neg on the popped A); B += *(AR2) (the post-stl
 * cell); cell AR2 = B-low, no step (stl); B += 8;
 * cell AR3 = HIGH of (B arith>>4), no step (stl
 * b,-4,*ar3; same exactness argument); return. A/B
 * locals, written before read on every path; ARs dead
 * at return (flagged). Bound 4858-4882.
 */
extern void sub_059E(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void sum_rptb_4858(int ar5_live)
{
    int *ar2;
    int *ar3;
    long a;
    long b;
    int i;
    sub_059E();                                      /* call 0x59e */
    b = (long)(unsigned)ar5_live;                    /* ldm ar5,b (zero-ext) */
    b += 36;                                         /* add #36,b */
    ar2 = (int *)(b & 0xFFFF);                       /* stlm b,ar2 */
    a = 0;                                           /* ld #0,a */
    b = 0;                                           /* ld #0,b */
    /* stm #43,brc */
    for (i = 0; i < 44; i++) {                       /* rptb 0x4865 */
        a += (long)*ar2++;                           /* add *ar2+,a */
        b += (long)*ar2++;                           /* add *ar2+,b */
    }
    ar2 = (int *)502;                                /* stm #502,ar2 */
    ar3 = (int *)500;                                /* stm #500,ar3 */
    {                                                /* pshm bl/bh/bg */
        long b_saved = b;
        b = 1;                                       /* ld #1,b */
        if (a >= 0)                                  /* xc 1,alt */
            b = -b;                                  /* neg b */
        b += (long)*ar2;                             /* add *ar2,b */
        *ar2++ = (int)(b & 0xFFFF);                  /* stl b,*ar2+ */
        a = b_saved;                                 /* popm ag/ah/al */
        b += 8;                                      /* add #8,b */
        *ar3++ = (b < 0) ? -1 : 0;                  /* stl b,-4,*ar3+ */
        b = 1;                                       /* ld #1,b */
        if (a >= 0)                                  /* xc 1,alt */
            b = -b;                                  /* neg b */
        b += (long)*ar2;                             /* add *ar2,b */
        *ar2 = (int)(b & 0xFFFF);                    /* stl b,*ar2 */
        b += 8;                                      /* add #8,b */
        *ar3 = (b < 0) ? -1 : 0;                    /* stl b,-4,*ar3 */
    }
    /* ret */
}
