/* ROM6 0xE0B5 ROUTINE_E0B5 -- 56w dual-accumulator MAC filter lane.
 * Verified encoding: src/rom6/kernel/e0b5_routine_e0b5.asm (recombine MATCH).
 * ORIGIN 0xE0B5
 * EXPECT: F484 E906 E726 6DAA 770E 0005 FF43 F600 6D8A F520 807B E801 287B 0013 8814 817B F210 0006 E901 297B FF45 E901 6D8C 0113 8915 771A 0027 7710 FFF7 F272 E0EB E723 6D8A A49A B09B B04A B09B B04A B09B B04A B09B B04A B09B B04A B09B B04A B09B B04A B09B B04A B09B B00E B4DF 6DCA 8296 FC00
 *
 * Intent: Entry via 2x calld (D173/D825, head-exact, call-only) with
 * A/AR2/AR0 caller-live dark (params, 8b9d precedent). A = -A (neg);
 * B = 6; AR6 = AR2; AR2 -= AR0-in (mar *ar2-0, entry AR0); T = 5.
 * xc 2,alt: A < 0 runs add (A += B) + mar (AR2--), else sub (B -= A).
 * Cell 0x7B = A-low; A = 1; A += cell 0x7B x T (mac); A += cell 0x13;
 * AR4 = A-low (stlm address from value); cell 0x7B = B-low; A = B - 6
 * (sub #6,b,a); B = 1; B += cell 0x7B x T (mac); xc 2,aeq: A == 0 runs
 * ld (B = 1) + mar (AR4--), then B += cell 0x13 either way;
 * AR5 = B-low. AR0 = -9. rptbd 0xe0eb runs its delays once (AR3 = AR2;
 * AR2--) then the 22-word block 40x (BRC 39 + 1, <= (unsigned)brc
 * retrofit): mpy seeds A (795d plain form, no shift), 18x mac
 * accumulate (same form), macr rounds the low 16 away (8b9d macar
 * shape: (A + p + 0x8000) & ~0xFFFF, FRCT doubling dark, flagged),
 * mar *ar2-0% steps AR2 by -AR0, sth stores A-high to *AR6+ each pass.
 * +0%/-0% steps ride AR0 (-9) with BK = 0 so no circular wrap (351d
 * linear convention, wrap flagged); DP = 0 assumed for the 0x7B/0x13
 * absolute cells (flagged). No callees. Out cells/A/ARs. EXPECT from
 * the image.
 */

void routine_E0B5(long a_in, int *ar2_in, int ar0_in)
{
    long a = a_in;
    long b;
    long p;
    int *ar2 = ar2_in;
    int *ar3;
    int *ar4;
    int *ar5;
    int *ar6;
    int ar0;
    int t;
    int i;

    a = -a;                                                  /* neg a */
    b = 6L;                                                  /* ld #6,b */
    ar6 = ar2;                                               /* mvmm ar2,ar6 */
    ar2 -= ar0_in;                                           /* mar *ar2-0 (AR0 entry-dark) */
    t = 5;                                                   /* stm #5,t */
    if (a < 0) {                                             /* xc 2,alt */
        a += b;                                              /* add b,a */
        ar2--;                                               /* mar *ar2- */
    } else {
        b -= a;                                              /* sub a,b */
    }
    *(volatile int *)0x7B = (int)(a & 0xFFFFL);              /* stl a,0x7b */
    a = 1L;                                                  /* ld #1,a */
    a += (long)*(volatile int *)0x7B * (long)t;              /* mac 0x7b,a */
    a += (long)*(volatile int *)0x13;                        /* add 0x13,a */
    ar4 = (int *)(long)(a & 0xFFFFL);                        /* stlm a,ar4 */
    *(volatile int *)0x7B = (int)(b & 0xFFFFL);              /* stl b,0x7b */
    a = b - 6L;                                              /* sub #6,b,a */
    b = 1L;                                                  /* ld #1,b */
    b += (long)*(volatile int *)0x7B * (long)t;              /* mac 0x7b,b */
    if (a == 0) {                                            /* xc 2,aeq */
        b = 1L;                                              /* ld #1,b */
        ar4--;                                               /* mar *ar4- */
    }
    b += (long)*(volatile int *)0x13;                        /* add 0x13,b */
    ar5 = (int *)(long)(b & 0xFFFFL);                        /* stlm b,ar5 */
    ar0 = -9;                                                /* stm #-9,ar0 */
    /* rptbd 0xe0eb (delays run once, block 40x) */
    ar3 = ar2;                                               /* delay: mvmm ar2,ar3 */
    ar2--;                                                   /* delay: mar *ar2- */
    for (i = 0; i < 40; i++) {
        a = (long)*ar3 * (long)*ar4;                         /* mpy *ar3+,*ar4+,a */
        ar3++;
        ar4++;
        a += (long)*ar3 * (long)*ar5;                        /* mac *ar3+,*ar5+,a */
        ar3++;
        ar5++;
        a += (long)*ar2 * (long)*ar4;                        /* mac *ar2-,*ar4+,a */
        ar2--;
        ar4++;
        a += (long)*ar3 * (long)*ar5;                        /* mac *ar3+,*ar5+,a */
        ar3++;
        ar5++;
        a += (long)*ar2 * (long)*ar4;                        /* mac *ar2-,*ar4+,a */
        ar2--;
        ar4++;
        a += (long)*ar3 * (long)*ar5;                        /* mac *ar3+,*ar5+,a */
        ar3++;
        ar5++;
        a += (long)*ar2 * (long)*ar4;                        /* mac *ar2-,*ar4+,a */
        ar2--;
        ar4++;
        a += (long)*ar3 * (long)*ar5;                        /* mac *ar3+,*ar5+,a */
        ar3++;
        ar5++;
        a += (long)*ar2 * (long)*ar4;                        /* mac *ar2-,*ar4+,a */
        ar2--;
        ar4++;
        a += (long)*ar3 * (long)*ar5;                        /* mac *ar3+,*ar5+,a */
        ar3++;
        ar5++;
        a += (long)*ar2 * (long)*ar4;                        /* mac *ar2-,*ar4+,a */
        ar2--;
        ar4++;
        a += (long)*ar3 * (long)*ar5;                        /* mac *ar3+,*ar5+,a */
        ar3++;
        ar5++;
        a += (long)*ar2 * (long)*ar4;                        /* mac *ar2-,*ar4+,a */
        ar2--;
        ar4++;
        a += (long)*ar3 * (long)*ar5;                        /* mac *ar3+,*ar5+,a */
        ar3++;
        ar5++;
        a += (long)*ar2 * (long)*ar4;                        /* mac *ar2-,*ar4+,a */
        ar2--;
        ar4++;
        a += (long)*ar3 * (long)*ar5;                        /* mac *ar3+,*ar5+,a */
        ar3++;
        ar5++;
        a += (long)*ar2 * (long)*ar4;                        /* mac *ar2-,*ar4+,a */
        ar2--;
        ar4++;
        a += (long)*ar3 * (long)*ar5;                        /* mac *ar3+,*ar5+,a */
        ar3++;
        ar5++;
        a += (long)*ar2 * (long)*ar4;                        /* mac *ar2,*ar4+0%,a */
        ar4 += ar0;                                          /* +0% (BK wrap flagged) */
        p = (long)*ar3 * (long)*ar5;                        /* macr *ar3+0%,*ar5+0%,a */
        a = (a + p + 0x8000L) & ~0xFFFFL;
        ar3 += ar0;                                          /* +0% (BK wrap flagged) */
        ar5 += ar0;                                          /* +0% (BK wrap flagged) */
        ar2 -= ar0;                                          /* mar *ar2-0% (BK wrap flagged) */
        *ar6++ = (int)((a >> 16) & 0xFFFFL);                 /* sth a,*ar6+ */
    }
}
