/* ROM6 0x90F8 POSTSCALE_90F8 -- 32w Viterbi postscale tail.
 * Verified encoding: src/rom6/kernel/90f8_postscale_90f8.asm (recombine MATCH).
 * ORIGIN 0x90F8
 * EXPECT: 4A17 7717 3120 7712 0003 771A 0007 F072 9110 3097 5A85 5FD5 8ED4 8FD3 4008 430B F465 F483 F063 FF00 F765 F583 F3F8 F2A0 8291 8D96 6C8A 90FD 8A17 FE00 6DDC 6DDB
 *
 * Intent: Viterbi ACS postscale tail (sibling of the
 * 9118/9146 butterflies). Save AR7; AR7 = 12576; AR2 = 3;
 * BRC = 7; RPTBD block 9101-9110 x8: T = *AR7+; A +=
 * (*AR5:T) (DADST short form: high += Xmem, low += T, C16 =
 * 0 assumed, flagged); B -= (*AR5+:T) circular (DSADT short
 * form, same flag); A -= *AR4+ << 16 and B -= *AR3+ <<
 * 16 circular (CMPS pair; TC borrow flagged); A -=
 * mem(0x08) << 16; B -= mem(0x0B) << 16; A <<= 5, SAT A
 * (OVM dark, flagged), A &= (-256) << 16; store A MSW to
 * *AR1+. Tail (once per outer pass): B <<= 5, SAT B, B >>>
 * = 8, A |= B (combined metric), store A MSW to *AR1+,
 * store TRN to *AR6+ (traceback write); BANZ to 90FD
 * (AR2--, branch while nonzero); popm AR7; RETD with mar
 * delays; return.
 * Termination note: the outer BANZ retargets 90FD, which
 * reloads AR2 = 3 and BRC = 7 and re-arms RPTB -- as listed
 * the AR2 gate (3 -> 2 each pass with reload) never falls
 * through on in-span state alone, and no in-span writer to
 * AR2 exists besides the reload. Yet the 90E7 wrapper calls
 * 0x90F8 and continues (AGT/countdown epilogue), so return
 * is caller-evidenced. The terminating exterior condition
 * (caller/ISR context interaction) is NOT in-span: OPEN,
 * flagged. The C below models one outer pass with the
 * counters as listed and does not invent a trip count.
 */
void postscale_90F8(void)
{
    long a;  /* live-in (dark, flagged) */
    long b;  /* live-in (dark, flagged) */
    int *ar1;  /* live-in (dark, flagged) */
    int *ar2;
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;  /* live-in (dark, flagged) */
    int *ar5;  /* live-in (dark, flagged) */
    int *ar6;  /* live-in (dark, flagged) */
    int *ar7;
    int t;
    int i;

    /* pshm ar7 (caller AR7 saved, restored before return) */
    ar7 = (int *)12576;                                        /* stm #12576,ar7 */
    ar2 = (int *)3;                                            /* stm #3,ar2 */
    /* stm #7,brc */
    for (i = 0; i < 8; i++) {                                  /* rptbd 0x9110 */
        t = *ar7++;                                            /* ld *ar7+,t */
        a += ((long)*ar5 << 16) + (t & 0xFFFFL);               /* dadst *ar5,a (short: hi += X, lo += T; C16=0 flagged) */
        b -= ((long)*ar5 << 16) + (t & 0xFFFFL);               /* dsadt *ar5+%,b (circular BK dark, flagged) */
        ar5++;
        a -= (long)*ar4++ << 16;                               /* cmps a,*ar4+% (TC borrow flagged) */
        b -= (long)*ar3++ << 16;                               /* cmps b,*ar3+% */
        a -= (long)*(volatile int *)0x08 << 16;                /* sub 0x08,16,a */
        b -= (long)*(volatile int *)0x0B << 16;                /* sub 0x0b,16,b */
        a <<= 5;                                               /* sfta a,5 */
        /* sat a (OVM dark, flagged) */
        a &= (long)-256 << 16;                                 /* and #-256,16,a */
        *ar1++ = (int)((a >> 16) & 0xFFFFL);                   /* sth a,*ar1+ */
    }
    b <<= 5;                                                   /* sfta b,5 */
    /* sat b (OVM dark, flagged) */
    b = (long)((unsigned long)b >> 8);                         /* sftl b,-8 (logical) */
    a |= b;                                                    /* or b,a */
    *ar1++ = (int)((a >> 16) & 0xFFFFL);                       /* sth a,*ar1+ */
    *ar6++ = 0; /* st trn,*ar6+ (TRN register, no C form, flagged) */
    ar2--;                                                     /* banz 0x90fd,*ar2- */
    /* (taken: re-arms at 90FD; in-span fall-through OPEN per header -- one outer pass modeled) */
    /* popm ar7 */
    /* retd (delay words run, then return): */
    /* mar *ar4+0% (circular, flagged) */
    /* mar *ar3+0% (circular, flagged) */
    /* retd */
    (void)a; (void)b; (void)t;
}
