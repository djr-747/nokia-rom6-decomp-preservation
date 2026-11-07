/* ROM6 0x38FB FRAG_38FB -- 11w (overlap-corrected wave-12: the or #0,a operand word 0x3905 homed here).
 * Verified encoding: src/rom6/kernel/38fb_frag_38fb.asm (recombine MATCH).
 * ORIGIN 0x38FB
 * EXPECT: F562 F330 00FC F340 0003 F463 F030 FE00 F2A0 F040 0000
 *
 * Intent: Shift-merge with live-out A. B = A-live-in << 2 arithmetic masked to bits 2-7 (and #252) plus 3 (or); A <<= 3 masked to clear low 9 (and #-512) OR B OR 0 (or #0,a is a no-op pad, kept per 2e64 precedent; its operand word 3905 owned here, overlap-corrected); A returned (no exit in span, falls into frag_3905's ret which reads A-live). 40-bit accumulators as long. Bound 38FB-3905.
 */
int frag_38FB(int a_live)
{
    long a = a_live;
    long b;
    b = a << 2;                                  /* sfta a,2,b */
    b &= 252;                                    /* and #252,b */
    b |= 3;                                      /* or #3,b */
    a <<= 3;                                     /* sfta a,3 */
    a &= -512;                                   /* and #-512,a */
    a |= b;                                      /* or b,a */
    a |= 0;                                      /* or #0,a (no-op pad) */
    return (int)a;                               /* falls through, A live-out */
}
