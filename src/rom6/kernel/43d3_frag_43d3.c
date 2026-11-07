/* ROM6 0x43D3 FRAG_43D3 -- 23w.
 * Verified encoding: src/rom6/kernel/43d3_frag_43d3.asm (recombine MATCH).
 * ORIGIN 0x43D3
 * EXPECT: 7714 2F01 771A 0001 F072 43DA 10D2 8094 F074 2E2F F030 00FF F010 0001 F845 4533 7713 0527 7714 2F00 EC02 E5A9 FC00
 *
 * Intent: Strided copy with post-call gate. AR4 = 12033; 2 passes
 * of A = *AR2 (sign-extended per SXM = 1, flagged) with AR2 +=
 * AR0-live (circular +0%, wrap needs caller-live BK, linear modeled
 * flagged), *(AR4++) = A-low (rptb 0x43da: RSA = PC + 2, BRC = 1);
 * runs dark SUB_2E2F; A &= 255 (imm positive, exact); A -= 1;
 * zero tail-enters FRAG_4533 (bc aeq; 4533 sets its own AR4, void);
 * else AR3 = 1319, AR4 = 12032, 3 dual moves *(AR3++) = *(AR4++)
 * (rpt #2 + MVDD, 457f precedent); return. AR2 caller-live,
 * dead after. Bound 43D3-43E9.
 */
extern void sub_2E2F(void);
extern void frag_4533(void);

void frag_43D3(int *ar2_in, int ar0_live)
{
    int *ar2 = ar2_in;
    int *ar4;
    int *ar3;
    long a;
    int i;
    ar4 = (int *)12033;                              /* stm #12033,ar4 */
    for (i = 0; i < 2; i++) {                        /* stm #1,brc; rptb 0x43da */
        a = (long)*ar2;                              /* ld *ar2+%,a */
        ar2 += ar0_live;                             /* +0% (wrap flagged) */
        *ar4++ = (int)(a & 0xFFFF);                  /* stl a,*ar4+ */
    }
    sub_2E2F();                                      /* call 0x2e2f (dark) */
    a &= 255;                                        /* and #255,a */
    a -= 1;                                          /* sub #1,a */
    if (a == 0) {                                    /* bc 0x4533,aeq */
        frag_4533();
        return;
    }
    ar3 = (int *)1319;                               /* stm #1319,ar3 */
    ar4 = (int *)12032;                              /* stm #12032,ar4 */
    for (i = 0; i < 3; i++)                          /* rpt #2 */
        *ar3++ = *ar4++;                             /* mvdd *ar4+,*ar3+ */
    /* ret */
}
