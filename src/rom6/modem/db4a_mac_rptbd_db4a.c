/* ROM6 0xDB4A MAC_RPTBD_DB4A -- 19w.
 * Verified encoding: src/rom6/modem/db4a_mac_rptbd_db4a.asm (recombine MATCH).
 * ORIGIN 0xDB4A
 * EXPECT: 770E 1249 771A 0009 2092 F272 DB5B 7710 000A 28B3 28B3 28B3 28B3 28B3 2AB3 CC8A 6DEB FFC5 FC00
 *
 * Intent: RPTBD block-MAC tail (modem engine). T = 4681
 * (stm #4681,t, in-span constant). A = seed product (*AR2++ x T, mpy
 * *ar2+,a, 16x16->32 per op_mpy_smem). BRC = 9 (folded); rptbd block
 * DB53-DB5B, 10 passes (delays stm #10,ar0 + seed run once; RPTBD
 * PC+4 convention per the d5ca groundwork, Z=1 no oracle leaf,
 * flagged). Per pass: A += 5 x MEM[AR3] x T (mac *ar3+0,a x5; AR3
 * fixed, +0 step, single cell read); A = round16(A + MEM[AR3] x T)
 * (macr *ar3+0,a: (sum + 0x8000) & ~0xFFFF per the
 * ti_c54x_multiply_accumulate ground truth); MEM[*AR4++] = A-low +
 * start next product (parallel st a,*ar4+ || mpy *ar2+,a); AR3 -= 59
 * (mar *+ar3(0xffc5), linear). AR2-out = +11, AR3-out = -590,
 * AR4-out = +10 (writebacks via ppar, 2e64 precedent). AR0 = 10
 * (delay filler, no in-span use, caller-observable, not carried).
 * A-out = 10th parallel-mpy product (dead-slot drain residue; caller
 * liveness through the D670 calld site unbound, flagged).
 * Exactness: T is the in-span constant 4681 (teff 9362 with FRCT),
 * so |term| <= 306708496 and the 7-term pass sum <= 2146959472 <
 * 2^31 - 1 for every input including full-scale FRCT=1; OVM
 * provably never fires (value irrelevant, comment only) and 40-bit
 * wrap coincides with 32-bit long -- exact. FRCT is the entry-dark
 * mode bit (explicit param); the FRCT P = 0x40000000 edge is
 * unreachable at this T (flagged). Entered via 0xD670 calld
 * (header evidence).
 */
long frag_DB4A(int **ppar2, int **ppar3, int **ppar4, int frct_in)
{
    long teff = frct_in ? 9362L : 4681L;             /* stm #4681,t (+FRCT x2) */
    long a;
    long p;
    int x;
    int ar0;
    int *ar2 = *ppar2;
    int *ar3 = *ppar3;
    int *ar4 = *ppar4;
    int pass;
    int k;
    a = (long)(*ar2++) * teff;                       /* mpy *ar2+,a (seed) */
    /* stm #9,brc (folded); rptbd 0xdb5b */
    ar0 = 10;                                        /* stm #10,ar0 (delay filler) */
    for (pass = 0; pass < 10; pass++) {              /* rptbd block DB53-DB5B */
        x = *ar3;                                    /* mac cell (AR3 fixed, +0) */
        for (k = 0; k < 5; k++)                      /* mac *ar3+0,a x5 */
            a += (long)x * teff;
        p = (long)x * teff;                          /* macr *ar3+0,a product */
        a = (a + p + 0x8000L) & ~0xFFFFL;            /* macr round16 */
        *ar4++ = (int)(a & 0xFFFF);                  /* st a,*ar4+ (store lane) */
        a = (long)(*ar2++) * teff;                   /* ... || mpy *ar2+,a (next lane) */
        ar3 -= 59;                                   /* mar *+ar3(0xffc5) */
    }
    (void)ar0;                                       /* AR0 = 10, caller-observable, not carried */
    *ppar2 = ar2;                                    /* AR2-out = +11 */
    *ppar3 = ar3;                                    /* AR3-out = -590 */
    *ppar4 = ar4;                                    /* AR4-out = +10 */
    return a;
}
