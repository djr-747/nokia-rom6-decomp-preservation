/* ROM6 0x3179 SUB_3179 -- 28w.
 * Verified encoding: src/rom6/kernel/3179_sub_3179.asm (recombine MATCH).
 * ORIGIN 0x3179
 * EXPECT: 7714 2512 12D2 1184 F330 FBFF FF44 F340 0400 8184 7714 2647 12D2 F1F8 818C F130 00FF 7684 00E0 7714 263E 10D2 8194 8084 F074 2E2F F073 2E64
 *
 * Intent: Masked store lane with tail chain. AR4 = 9490;
 * A = unsigned *AR2 (ldu, 3691 precedent) with AR2 += AR0
 * (circular +0%, wrap needs caller-live BK, linear modeled
 * flagged); B = *AR4; B &= 0xFBFF (and #-1025, imm16
 * zero-extended so upper cleared, per the logical-immediate
 * leaf); xc 2,aneq tests A (XC reads the accumulator named
 * by the condition): A nonzero skips the 2-word B |= 1024,
 * zero runs it; cell AR4 = B-low; AR4 = 9799; A = unsigned
 * *AR2 (AR2 += AR0); B = A logical>>8 (sftl, exact: A < 2^16
 * so logical and arithmetic coincide); cell AR4 = B-low
 * with AR4 post-decremented to 9798; B = A & 255 (upper
 * cleared); cell AR4 = 224 (st immediate); AR4 = 9790;
 * A = *AR2 (AR2 += AR0, SXM = 1 flagged); cell AR4 = B-low
 * with AR4 post-incremented to 9791; cell AR4 = A-low;
 * runs 0x2E2F (extern) then tail-branches to frag_2E64
 * (extern). ARs/A/B dead into the tail (flagged). Bound
 * 3179-3194 (28w; the header's old 22w count is stale).
 */
extern void sub_2E2F(void);
extern void frag_2E64(void);

void sub_3179(int ar0_live, int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar4;
    long a;
    long b;
    ar4 = (int *)9490;                               /* stm #9490,ar4 */
    a = (unsigned long)(unsigned)*ar2;               /* ldu *ar2+%,a */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    b = (long)*ar4;                                  /* ld *ar4,b */
    b &= 64511;                                      /* and #-1025,b */
    if (a == 0)                                      /* xc 2,aneq (tests A) */
        b |= 1024;                                   /* or #1024,b */
    *ar4 = (int)(b & 0xFFFF);                        /* stl b,*ar4 */
    ar4 = (int *)9799;                               /* stm #9799,ar4 */
    a = (unsigned long)(unsigned)*ar2;               /* ldu *ar2+%,a */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    b = (unsigned long)a >> 8;                       /* sftl a,-8,b */
    *ar4-- = (int)(b & 0xFFFF);                      /* stl b,*ar4- */
    b = a & 255;                                     /* and #255,a,b */
    *ar4 = 224;                                      /* st #224,*ar4 */
    ar4 = (int *)9790;                               /* stm #9790,ar4 */
    a = (long)*ar2;                                  /* ld *ar2+%,a (SXM flagged) */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    *ar4++ = (int)(b & 0xFFFF);                      /* stl b,*ar4+ */
    *ar4 = (int)(a & 0xFFFF);                        /* stl a,*ar4 */
    sub_2E2F();                                      /* call 0x2e2f */
    frag_2E64();                                      /* b 0x2e64 (tail) */
}
