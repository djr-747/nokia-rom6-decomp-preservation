/* ROM6 0x311F WORKER_311F -- 64w.
 * Verified encoding: src/rom6/kernel/311f_worker_311f.asm (recombine MATCH).
 * ORIGIN 0x311F
 * EXPECT: 6F82 0C56 F030 000F F000 0002 80F8 0587 10D2 F130 00FF F030 0300 F478 FA45 313E F340 0800 F010 0002 F495 F495 FF43 F340 0400 FF45 F340 0100 FF46 F340 0200 81F8 2202 10D2 F130 FF00 F778 63F8 000B 015B F77C 81F8 2204 F030 00FF F110 00FF 62F8 0008 0D8B F47C FF4D F020 FFFF 80F8 2203 F074 2E2F 4A12 F074 98AD 8A12 F073 2E64
 *
 * Intent: Scale-select plus fold with tail chain. A = *AR2
 * arith>>10 (ld Smem,SHIFT; second word 0C56: SHIFT5 = 22 ->
 * -10 with bit 8 free per the 9BF8 analysis, SXM = 1
 * flagged); A &= 15 (upper cleared), A += 2 (add lk), cell
 * 0x587 = A-low; A = *AR2 with AR2 += AR0 (circular +0%,
 * wrap needs caller-live BK, linear modeled flagged);
 * B = A & 255 (upper cleared); A &= 768; A arith>>= 8
 * (sfta, 351d precedent); bcd on A == 0 tests the PRE-delay
 * accumulator (leaf evaluates over input state): delays
 * B |= 2048 and A -= 2 always run; taken path skips the
 * three conditional ORs to the 313E store. Fall path
 * (A in {-1,0,1}): xc 2,alt/aeq/agt each skip one 2-word
 * or-into-B (XC-taken-skips per the oracle; 2 words cover
 * the immediate ORs), leaving exactly the two non-matching
 * bits set beside 2048; cell 0x2202 = B-low. Second lane:
 * A = *AR2 (AR2 += AR0); B = (A & 0xFF00) arith>>8 (upper
 * cleared first, exact); B = cell 0xB x 347 (mpy Smem,K16,
 * T = cell side effect flagged) arith>>= 4 (sfta); cell
 * 0x2204 = B-low; A &= 255; B = A - 255; A = cell 0x8
 * x 3467 arith>>= 4; xc 2,beq skips A = -1 iff A == 0
 * (A ends 0 or -1); cell 0x2203 = A-low. Epilogue: runs
 * 0x2E2F (extern), saves AR2 across 0x98AD (dark, extern;
 * pshm/popm pair is hardware state per the 2D5E precedent,
 * the C local carries AR2), tail-branches to frag_2E64
 * (extern). ARs/A/B dead into the tail (flagged). Bound
 * 311F-315E.
 */
extern void sub_2E2F(void);
extern void sub_98AD(void);
extern void frag_2E64(void);

void worker_311F(int ar0_live, int *ar2_in)
{
    int *ar2 = ar2_in;
    long a;
    long b;
    int taken;
    a = (long)*ar2 >> 10;                            /* ld *ar2,-10,a (arith) */
    a &= 15;                                         /* and #15,a */
    a += 2;                                          /* add #2,a */
    *(volatile int *)0x587 = (int)(a & 0xFFFF);      /* stl a,*(0x587) */
    a = (long)*ar2;                                  /* ld *ar2+%,a */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    b = a & 255;                                     /* and #255,a,b */
    a &= 768;                                        /* and #768,a */
    a = a >> 8;                                      /* sfta a,-8 (arith) */
    taken = (a == 0);                                /* bcd tests pre-delay A */
    b |= 2048;                                       /* delay-1 (always runs) */
    a -= 2;                                          /* delay-2 (always runs) */
    if (!taken) {                                    /* bcd 0x313e,aeq */
        if (a >= 0)                                  /* xc 2,alt */
            b |= 1024;                               /* or #1024,b */
        if (a != 0)                                  /* xc 2,aeq */
            b |= 256;                                /* or #256,b */
        if (a <= 0)                                  /* xc 2,agt */
            b |= 512;                                /* or #512,b */
    }
    *(volatile int *)0x2202 = (int)(b & 0xFFFF);     /* stl b,*(0x2202) */
    a = (long)*ar2;                                  /* ld *ar2+%,a */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    b = a & 65280;                                   /* and #-256,a,b */
    b = b >> 8;                                      /* sfta b,-8 (arith, exact) */
    b = (long)*(volatile int *)0xB * 347;            /* mpy (T flagged) */
    b = b >> 4;                                      /* sfta b,-4 (arith) */
    *(volatile int *)0x2204 = (int)(b & 0xFFFF);     /* stl b,*(0x2204) */
    a &= 255;                                        /* and #255,a */
    b = a - 255;                                     /* sub #255,a,b */
    a = (long)*(volatile int *)0x8 * 3467;           /* mpy (T flagged) */
    a = a >> 4;                                      /* sfta a,-4 (arith) */
    if (a != 0)                                      /* xc 2,beq */
        a = -1;                                      /* ld #-1,a */
    *(volatile int *)0x2203 = (int)(a & 0xFFFF);     /* stl a,*(0x2203) */
    sub_2E2F();                                      /* call 0x2e2f */
    /* pshm ar2 (hardware state, C local carries it) */
    sub_98AD();                                      /* call 0x98ad */
    /* popm ar2 (hardware state) */
    frag_2E64();                                      /* b 0x2e64 (tail) */
}
