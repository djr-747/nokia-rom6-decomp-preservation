/* ROM6 0xE0A2 ROUTINE_E0A2 -- 19w.
 * Verified encoding: src/rom6/kernel/e0a2_routine_e0a2.asm (recombine MATCH).
 * ORIGIN 0xE0A2
 * EXPECT: F100 FC13 8913 F521 8915 E724 FD43 A14D FD42 A1AF A44D B0AF B04D B0AF B04D B0AF FE00 B04D B4AF
 *
 * Intent: Dual-MAC correlation lane with complementary XC skips. B = A - 1005;
 * AR3 = B-low; B = A - 1; AR5 = B-low; AR4 = AR2. Exactly one of the two
 * single-word adds runs: A >= 0 takes B = *AR2- + *AR3 (xc 1,alt skips when
 * A < 0); A < 0 takes B = *AR4+ + *AR5 (xc 1,ageq skips when A >= 0).
 * Then the dual-MAC chain (mpy/mac x6, FRCT/OVM flagged per db4a);
 * retd with the last mac/macr pair as its 2 delay WORDS (both run).
 * Entries 2x calld (per asm evidence). A/B/AR2/AR4 live-in (dark, flagged).
 */
void routine_E0A2(void)
{
    long a;  /* live-in (dark, flagged) */
    long b;  /* live-in (dark, flagged) */
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;
    int *ar4;  /* live-in (dark, flagged) */
    int *ar5;

    b = a - 1005;                                              /* add #-1005,a,b */
    ar3 = (int *)(b & 0xFFFFL);                                /* stlm b,ar3 */
    b = b - (a << 1);                                          /* sub a,1,b (shift form: dst_old - src<<1 per op_arithmetic leaf) */
    ar5 = (int *)(b & 0xFFFFL);                                /* stlm b,ar5 */
    ar4 = ar2;                                                 /* mvmm ar2,ar4 */
    if (a < 0) {                                               /* xc 1,alt (executes when A<0) */
        b = ((long)*ar2 + (long)*ar3) << 16;                  /* add *ar2-,*ar3+0%,b (dual: SXM-widened <<16 per op_dual_arithmetic) */
        ar2--;
    }
    if (a >= 0) {                                              /* xc 1,ageq (executes when A>=0) */
        b = ((long)*ar4 + (long)*ar5) << 16;                  /* add *ar4+,*ar5+0%,b (dual: SXM-widened <<16 per op_dual_arithmetic) */
        ar4++;
    }
    a = (long)*ar2 * (long)*ar3;                               /* mpy *ar2-,*ar3+0%,a */
    ar2--;
    a += (long)*ar4 * (long)*ar5;                              /* mac *ar4+,*ar5+0%,a */
    ar4++;
    ar5++;
    a += (long)*ar2 * (long)*ar3;                              /* mac *ar2-,*ar3+0%,a */
    ar2--;
    a += (long)*ar4 * (long)*ar5;                              /* mac *ar4+,*ar5+0%,a */
    ar4++;
    ar5++;
    a += (long)*ar2 * (long)*ar3;                              /* mac *ar2-,*ar3+0%,a */
    ar2--;
    a += (long)*ar4 * (long)*ar5;                              /* mac *ar4+,*ar5+0%,a */
    ar4++;
    ar5++;
    /* retd (delay words run, then return): */
    a += (long)*ar2 * (long)*ar3;                              /* retd delay: mac */
    ar2--;
    a += ((long)*ar4 * (long)*ar5 + 0x4000L) >> 16;           /* retd delay: macr (rounded; FRCT flagged) */
    ar4++;
    ar5++;
    (void)a; (void)b;
    /* retd */
}
