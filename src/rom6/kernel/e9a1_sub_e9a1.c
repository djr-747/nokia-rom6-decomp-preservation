/* ROM6 0xE9A1 SUB_E9A1 -- 39w scaled-store loop.
 * Verified encoding: src/rom6/kernel/e9a1_sub_e9a1.asm (recombine MATCH).
 * ORIGIN 0xE9A1
 * EXPECT: F074 071C EEFF E800 82F8 2D33 82F8 2D32 82F8 2D31 7217 29A9 7710 2D34 7711 B78A F162 7FFF 6D8F 1091 8812 1080 F0F8 F000 0002 00F8 2D31 80F8 2D31 1090 F030 00FF 8000 4700 8392 6C8F E9B4 EE01 FC00
 *
 * Intent: Calls sub_071C (low-zone unsourced, flagged);
 * balanced FRAME -1/+1 (SP adjust, comment only); A = 0;
 * cells 0x2D33/0x2D32/0x2D31 = A-high (sth absolute, ASM
 * dark, flagged); AR7 = *(0x29A9) (mvdm); AR0 = 11572, AR1 =
 * -18550; B = 32767<<16; AR7-- (mar); loop of AR7_entry
 * passes (banz 0xe9b4,*ar7-; count dark/volatile, flagged):
 * A = *(AR1++) (ld, SXM dark, flagged); AR2 = A-low
 * (stlm); A = *(AR0) (no step); A = low32(A)>>8 (sftl a,-8,
 * oracle op_shift; C dead); A += 2; A += *(0x2D31)<<16;
 * *(0x2D31) = A-low; A = *(AR0++) (AR0 advances); A &= 255;
 * *(DP:0x00) = A-low (stl direct, DP = 0 assumed, flagged);
 * *(AR2++) = B-high = 0x7FFF (sth, rpt #0 runs it once).
 * AR1/AR0 advance per pass; AR2 reset per pass; out
 * cells/ARs. Abuts E9C8 zerofill.
 * EXPECT from the image.
 */
void sub_E9A1(void)
{
    long a;
    long b;
    int *ar0;
    int *ar1;
    int *ar2;
    int ar7;

    sub_071C();                                              /* call 0x71c (low-zone, flagged) */
    /* frame -1 (SP adjust, balanced by frame 1; comment only) */
    a = 0;                                                   /* ld #0,a */
    *(volatile int *)0x2D33 = (int)((a >> 16) & 0xFFFFL);    /* sth a,*(0x2d33) (ASM dark) */
    *(volatile int *)0x2D32 = (int)((a >> 16) & 0xFFFFL);    /* sth a,*(0x2d32) */
    *(volatile int *)0x2D31 = (int)((a >> 16) & 0xFFFFL);    /* sth a,*(0x2d31) */
    ar7 = *(volatile int *)0x29A9;                           /* mvdm 0x29a9,ar7 */
    ar0 = (int *)11572;                                      /* stm #11572,ar0 */
    ar1 = (int *)-18550;                                     /* stm #-18550,ar1 */
    b = 32767L << 16;                                        /* ld #32767,16,b */
    ar7--;                                                   /* mar *ar7- */
    do {                                                     /* banz 0xe9b4,*ar7- (shoots first) */
        a = (long)*ar1++;                                    /* ld *ar1+,a (SXM dark, flagged) */
        ar2 = (int *)(a & 0xFFFFL);                          /* stlm a,ar2 */
        a = (long)*ar0;                                      /* ld *ar0,a */
        a = (long)((unsigned long)a >> 8);                   /* sftl a,-8 (oracle; C dead) */
        a += 2;                                              /* add #2,a */
        a += (long)*(volatile int *)0x2D31 << 16;            /* add *(0x2d31),a */
        *(volatile int *)0x2D31 = (int)(a & 0xFFFFL);        /* stl a,*(0x2d31) */
        a = (long)*ar0++;                                    /* ld *ar0+,a */
        a &= 255L;                                           /* and #255,a */
        *(volatile int *)0x0 = (int)(a & 0xFFFFL);            /* stl a,*(dp:0x00) (DP dark, flagged) */
        /* rpt #0: next runs once */
        *ar2++ = (int)((b >> 16) & 0xFFFFL);                 /* sth b,*ar2+ */
        ar7--;
    } while (ar7 != 0);
    /* frame 1 (balanced; comment only) */
    /* ret */
}
