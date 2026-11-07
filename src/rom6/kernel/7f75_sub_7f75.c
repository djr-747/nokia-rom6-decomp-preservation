/* ROM6 0x7F75 SUB_7F75 -- 32w rotate-merge loop, AR2 sink.
 * Verified encoding: src/rom6/kernel/7f75_sub_7f75.asm (recombine MATCH).
 * ORIGIN 0x7F75
 * EXPECT: F074 7FB5 7715 0006 E900 7196 0013 6DB3 1483 F490 F591 1B82 818A E900 771A 0007 F072 7F8D 7196 0013 6DB3 1483 F490 F591 F761 F3FF 6E8D 7F82 1B82 818A F073 7F54
 *
 * Intent: Rotate-merge loop, AR2-sink variant of the 7F95
 * lane (which sinks AR1 and lacks the SFTL step). Head call
 * 0x7FB5 (mask lane, C entry sub32_7F95 -- the 7FB5 entry
 * path runs on call); AR5 = 6; B = 0; cell 0x13 = *AR6+;
 * A = *AR3 << TS (T caller-preset, dark -- TS = T & 31,
 * flagged); ROR A / ROL B through a shared carry (initial
 * carry dark, flagged); fold *AR2 in; store BL to *AR2-.
 * Main loop (BANZD on AR5, 6 passes, set-once -- terminates
 * cleanly): each pass re-arms B = 0, BRC = 7 at the 7F82
 * target, runs RPTB block x8 {reload cell, shift in, inner
 * ROR/ROL ring with SFTA B,1 then SFTL B,-1 (net: B =
 * (B << 1) >>> 1, sign bit cleared)}, then the BANZD delay
 * words fold/store to *AR2- (or *ar2,b; stl b,*ar2-).
 * Tail is an unconditional branch to the 7F54 span (B, not
 * delayed -- no delay slots), modeled as a tail call to the
 * existing frag_7F54 entry. Out: merged stream at *AR2-.
 * (Wave-13: or/stl are the BANZD delay slots inside the
 * AR5 loop; EXPECT embedded from the image in this pass.)
 */
extern void sub32_7F95(void);
extern void frag_7F54(void);

void sub_7F75(void)
{
    long a;
    long b;
    int *ar1;  /* dark (unused here, kept for lane symmetry, flagged) */
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar5;
    int *ar6;  /* table cursor, live-in (dark, flagged) */
    int t;  /* T live-in for TS shifts (dark, flagged) */
    int ts;
    int carry = 0;  /* C54x carry in (dark, flagged) */
    int i;

    sub32_7F95();                                              /* call 0x7fb5 (mask lane head) */
    ar5 = (int *)6;                                            /* stm #6,ar5 */
    b = 0;                                                     /* ld #0,b */
    *(volatile int *)0x13 = *ar6++;                            /* mvdk *ar6+,0x13 */
    /* mar *ar3+0 */
    ts = t & 31;
    a = (long)*ar3 << ts;                                      /* ld *ar3,ts,a */
    { int nc = (int)(a & 1L); a = ((a >> 1) & 0x7FFFFFFFL) | ((long)carry << 31); carry = nc; } /* ror a */
    { int nc = (int)((b >> 31) & 1L); b = (b << 1) | carry; carry = nc; } /* rol b */
    b |= (long)(*ar2 & 0xFFFF);                                           /* or *ar2,b */
    *ar2-- = (int)(b & 0xFFFFL);                               /* stl b,*ar2- */
    b = 0;                                                     /* ld #0,b */
    /* stm #7,brc */
    do {                                                       /* main loop (BANZD on AR5) */
        b = 0;                                                 /* 7f82 re-arm: ld #0,b */
        /* stm #7,brc (re-arm) */
        for (i = 0; i < 8; i++) {                              /* rptbd */
            *(volatile int *)0x13 = *ar6++;                    /* mvdk *ar6+,0x13 */
            /* mar *ar3+0 */
            a = (long)*ar3 << ts;                              /* ld *ar3,ts,a */
            { int nc = (int)(a & 1L); a = ((a >> 1) & 0x7FFFFFFFL) | ((long)carry << 31); carry = nc; } /* ror a */
            { int nc = (int)((b >> 31) & 1L); b = (b << 1) | carry; carry = nc; } /* rol b */
            b <<= 1;                                           /* sfta b,1 */
            b = (long)(((unsigned long)b >> 1) & 0x7FFFFFFFL); /* sftl b,-1 (logical) */
        }
        b |= (long)(*ar2 & 0xFFFF);                                       /* banzd delay 1: or *ar2,b */
        *ar2-- = (int)(b & 0xFFFFL);                           /* banzd delay 2: stl b,*ar2- */
        ar5--;                                                 /* banzd 0x7f82,*ar5- */
    } while (ar5 != (int *)0);
    frag_7F54();                                               /* b 0x7f54 (tail; B not delayed) */
    (void)a; (void)b; (void)ar1;
}
