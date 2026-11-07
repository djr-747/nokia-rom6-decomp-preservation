/* ROM6 0x9D16 FRAG_9D16 -- 23w.
 * Verified encoding: src/rom6/kernel/9d16_frag_9d16.asm (recombine MATCH).
 * ORIGIN 0x9D16
 * EXPECT: 7716 B413 FD47 6D96 F485 F48E 4A08 490E FD44 E817 F587 F520 890E 8A08 F784 F48F F47D FF4D F47F E901 FE00 F2C4 1C86
 *
 * Intent: Abs/norm/min saturate lane. AR6 = -19437; if A > 0 AR6++
 * (xc 1,aleq skips the mar); A = |A| (abs); A = exp(A) (exponent op,
 * oracle-unbound per 87e9 precedent, value flagged); save AL (pshm);
 * B = T (ldm); if A == 0 A = 23 (xc 1,aneq skips the load); A = min(A,B);
 * B = B - A; T = B-low; restore AL (popm); B = -B; A = norm(A)
 * (single-step, oracle-unbound per 87e9 precedent, value flagged);
 * A >>= 3; if B != 0 { A >>= 1; B = 1 } (xc 2,beq skips both);
 * retd with delay A = (B<<4)^A, A ^= *AR6 (both run).
 * Entry post-RET head (thin, per asm evidence). A/B/AR6/T live-in
 * (dark, flagged).
 */
void frag_9D16(void)
{
    long a;  /* live-in (dark, flagged) */
    long b;  /* live-in (dark, flagged) */
    int *ar6;  /* live-in (dark, flagged) */
    int t;  /* live-in (dark, flagged) */

    ar6 = (int *)-19437;                                       /* stm #-19437,ar6 */
    if (a <= 0)                                                /* xc 1,aleq (executes when A<=0) */
        ar6++;                                                 /* mar *ar6+ */
    if (a < 0)                                                 /* abs a */
        a = -a;
    /* exp a (exponent op; oracle-unbound per 87e9 precedent, value flagged) */
    /* pshm al (caller-live, comment only) */
    b = (long)t;                                               /* ldm t,b */
    if (a != 0)                                                /* xc 1,aneq (executes when A!=0) */
        a = 23;                                                /* ld #23,a */
    if (a > b)                                                 /* min b */
        a = b;
    b -= a;                                                    /* sub a,b */
    t = (int)(b & 0xFFFFL);                                    /* stlm b,t */
    /* popm al (restore entry state) */
    b = -b;                                                    /* neg b */
    /* norm a (single-step; oracle-unbound per 87e9 precedent, value flagged) */
    a >>= 3;                                                   /* sfta a,-3 */
    if (b == 0) {                                              /* xc 2,beq (executes when B==0) */
        a >>= 1;                                               /* sfta a,-1 */
        b = 1;                                                 /* ld #1,b */
    }
    /* retd (delay words run): */
    a = ((b << 4) ^ a);                                        /* xor b,4,a */
    a ^= (long)(*ar6 & 0xFFFF);                                  /* xor *ar6,a (Smem zero-extended per op_xor_smem) */
    /* retd */
    (void)a; (void)b;
}
