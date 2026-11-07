/* ROM6 0xD5CA D5CA_MAC_TAIL -- 12w.
 * Verified encoding: src/rom6/modem/d5ca_d5ca_mac_tail.asm (recombine MATCH).
 * ORIGIN 0xD5CA
 * EXPECT: 8207 771A 0027 E743 3007 F272 D5D4 ED00 2094 F463 CCA9 FC00
 *
 * Intent: RPTBD MAC/staging tail. MEM[0x7] = A-high entry (sth a,0x07,
 * 5b26 A-high precedent). AR3 = AR4-entry (mvmm ar4,ar3, 425f
 * precedent). T = MEM[0x7] (ld 0x07,t -- the staged high half, T live
 * for the mpy lane). BRC = 39 (stm #39,brc, folded into the pass
 * count). rptbd block: RSA = PC+4 past the 2-word op (delays ld #0,asm
 * + first mpy run once, then 40 passes over sfta + parallel st||mpy;
 * RPTBD summary convention. The RSA-after-op reading (50B2's flagged
 * Z=1 deviation) would discard every other parallel-mpy product -- 40
 * wasted cycles -- so code shape selects PC+4 here; Z=1 has no oracle
 * leaf, flagged). Per pass: A <<= 3 (sfta a,3, 40-bit wrap flagged),
 * MEM[*AR3++] = A-low + start next product (parallel st a,*ar3+ ||
 * mpy *ar4+,a; 16x16->32 per op_mpy_smem). 40 consecutive stores.
 * AR4-out = AR4-entry + 41 (writeback via ppar4, 2e64 precedent);
 * AR3-out = AR4-entry + 40 (not carried, caller-derivable, flagged).
 * A-out = 41st product, exact in 32-bit long (16x16, MPY never
 * saturates; caller liveness through the banz sites unbound,
 * flagged); B untouched (preserved). Entered only via 0xD595 banz /
 * 0xD5AC banzd (header evidence).
 */
long frag_D5CA(long a_in, int **ppar4)
{
    long a = a_in;
    int t;
    int *ar4 = *ppar4;
    int *ar3;
    int pass;
    *(volatile int *)0x7 = (int)((a >> 16) & 0xFFFF); /* sth a,0x07 */
    ar3 = ar4;                                       /* mvmm ar4,ar3 */
    t = *(volatile int *)0x7;                        /* ld 0x07,t */
    a = (long)(*ar4++) * t;                          /* delay: mpy *ar4+,a (first product) */
    for (pass = 0; pass < 40; pass++) {              /* rptbd 0xd5d4, BRC=39 */
        a <<= 3;                                     /* sfta a,3 */
        *ar3++ = (int)(a & 0xFFFF);                  /* st a,*ar3+ (store lane) */
        a = (long)(*ar4++) * t;                      /* ... || mpy *ar4+,a (next lane) */
    }
    (void)ar3;                                       /* AR3-out = AR4-entry + 40, not carried */
    *ppar4 = ar4;                                    /* AR4-out = AR4-entry + 41 */
    return a;
}
