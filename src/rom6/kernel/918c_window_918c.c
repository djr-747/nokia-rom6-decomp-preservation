/* ROM6 0x918C WINDOW_918C -- 50w (span 918C-91BD, single entry).
 * Verified encoding: src/rom6/kernel/918c_window_918c.asm (recombine MATCH).
 * ORIGIN 0x918C
 * EXPECT: F074 0610 7713 30BE 7714 30D0 7715 30DF 771A 0007 F072 919D 6FEB 0002 0C5A 8094 F484 808D 6DEB 0002 EC0F 7193 30C0 7710 0009 7713 3218 7715 3200 7714 3210 7719 0020 F020 FE00 EC1F 8095 7715 3200 E800 7711 3220 7716 3222 8091 8089 8085 7712 30C0 FC00
 *
 * Intent: Windowed normalize-and-fill (mesh entry E1; called by
 * the 91BE/91F3 drivers in this mesh). Entry AR3 live (the
 * window cursor, stepped in-span); entry A/B unread (both
 * recomputed; no B ops); void. Runs dark SUB_0610 (call,
 * forward extern void). AR3 = 12478, AR4 = 12496, AR5 = 12511
 * (stm locals). BRC = 7; rptb block [9198,919D], 8 passes
 * (RPTB non-delayed RSA = word after the 2-word op, inclusive
 * REA per repeat_block; the 3-word ld occupies the block head
 * with its shift word 0C5A): AR3 += 2 then A = *AR3
 * arithmetically shifted right 6 (ld *+ar3(0x2),-6,a; the *+
 * form updates AR3, SXM dark in-span so arith assumed per the
 * modem convention, flagged); *AR4++ = A-low (stl); A = -A
 * (neg, LONG_MIN edge flagged); *AR5-- = A-low (stl). mar
 * AR3 += 2 runs once after the loop. 16 stores of *AR3++ to
 * cell 0x30C0 (rpt #15 plus mvdk, 2a5f shapes). AR0 = 9,
 * AR3 = 12824, AR5 = 12800, AR4 = 12816, BK = 32 (stm; BK/AR0
 * set but never read in-span: locals, voided, 2d8f/50B2
 * precedent). A = -512 (ld); 32 stores of A-low (0xFE00) at
 * *AR5++ (rpt #31); AR5 = 12800; A = 0 (ld); AR1 = 12832,
 * AR6 = 12834 (stm; AR6 never read: voided); *AR1++ = 0,
 * *AR1-- = 0, *AR5 = 0 (stl trio); AR2 = 12480 (stm, dead at
 * return: voided); return. A/B/ARs dead after (void, 9217
 * precedent); outs via DARAM writes and the 0x30C0 cell.
 */
extern void sub_0610(void);                              /* dark, no symbol */

void window_918C(int *ar3_in)
{
    long a;
    int *ar3 = ar3_in;
    int *ar4;
    int *ar5;
    int *ar1;
    int *ar0;
    int *ar2;
    int *ar6;
    int bk;
    int i;
    sub_0610();                                          /* call 0x610 (dark) */
    ar3 = (int *)12478;                                  /* stm #12478,ar3 */
    ar4 = (int *)12496;                                  /* stm #12496,ar4 */
    ar5 = (int *)12511;                                  /* stm #12511,ar5 */
    for (i = 0; i <= 7; i++) {                           /* rptb 0x919d, BRC = 7 */
        ar3 += 2;                                        /* ld *+ar3(0x2) (update-then-read) */
        a = (long)*ar3 >> 6;                             /* -6 shift (arith assumed, flagged) */
        *ar4++ = (int)(a & 0xFFFFL);                      /* stl a,*ar4+ */
        a = -a;                                          /* neg a (edge flagged) */
        *ar5-- = (int)(a & 0xFFFFL);                     /* stl a,*ar5- */
    }
    ar3 += 2;                                            /* mar *+ar3(0x2) (post-loop) */
    for (i = 0; i < 16; i++)                             /* rpt #15; mvdk */
        *(volatile int *)0x30C0 = *ar3++;                /* mvdk *ar3+,0x30c0 */
    ar0 = (int *)9;                                      /* stm #9,ar0 (dead, noted) */
    (void)ar0;
    ar3 = (int *)12824;                                  /* stm #12824,ar3 */
    ar5 = (int *)12800;                                  /* stm #12800,ar5 */
    ar4 = (int *)12816;                                  /* stm #12816,ar4 */
    bk = 32;                                             /* stm #32,bk (unused, noted) */
    (void)bk;
    a = -512;                                            /* ld #-512,a */
    for (i = 0; i < 32; i++)                             /* rpt #31 */
        *ar5++ = (int)(a & 0xFFFFL);                     /* stl a,*ar5+ (= 0xFE00) */
    ar5 = (int *)12800;                                  /* stm #12800,ar5 */
    a = 0;                                               /* ld #0,a */
    ar1 = (int *)12832;                                  /* stm #12832,ar1 */
    ar6 = (int *)12834;                                  /* stm #12834,ar6 (dead, noted) */
    (void)ar6;
    *ar1++ = (int)(a & 0xFFFFL);                         /* stl a,*ar1+ */
    *ar1-- = (int)(a & 0xFFFFL);                         /* stl a,*ar1- */
    *ar5 = (int)(a & 0xFFFFL);                           /* stl a,*ar5 */
    ar2 = (int *)12480;                                  /* stm #12480,ar2 (dead, noted) */
    (void)ar2;
    /* ret */
}
