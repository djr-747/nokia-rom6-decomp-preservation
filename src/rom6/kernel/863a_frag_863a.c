/* ROM6 0x863A FRAG_863A -- 7w.
 * Verified encoding: src/rom6/kernel/863a_frag_863a.asm (recombine MATCH).
 * ORIGIN 0x863A
 * EXPECT: 0040 0020 0018 000C 0008 0004 0004
 *
 * Intent: Accumulator preload head. A += cells 0x40 + 0x20 + 0x18 +
 * 0x0C + 0x08 + 0x04 + 0x04 (ADD Smem,A: int->long conversion models
 * the SXM = 1 sign-extension exactly, flagged); cells absolute per the
 * da40 precedent (DP = 0 page assumed, flagged). Falls through into
 * 0x8641 (sub_8641, 2w stub); the dark SUB_0592 behind it may clobber
 * A, so the sum is carried only to the call (flagged). Bound 863A-8640.
 */
extern void sub_8641(void);

void frag_863A(long a_live)
{
    long a = a_live;
    a += (long)*(volatile int *)0x40;                /* add DP+0x40,a */
    a += (long)*(volatile int *)0x20;                /* add DP+0x20,a */
    a += (long)*(volatile int *)0x18;                /* add DP+0x18,a */
    a += (long)*(volatile int *)0x0C;                /* add DP+0x0c,a */
    a += (long)*(volatile int *)0x08;                /* add DP+0x08,a */
    a += (long)*(volatile int *)0x04;                /* add DP+0x04,a */
    a += (long)*(volatile int *)0x04;                /* add DP+0x04,a */
    (void)a;                                         /* A live into 0x8641 (clobber risk, flagged) */
    sub_8641();                                      /* fall-through to 0x8641 */
}
