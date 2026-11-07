/* ROM6 0x333C FRAG_333C -- 36w.
 * Verified encoding: src/rom6/kernel/333c_frag_333c.asm (recombine MATCH).
 * ORIGIN 0x333C
 * EXPECT: 6182 4000 68F8 263A E3FF F820 3346 69F8 263A 1800 6F82 0C58 F030 003F 11D2 F330 003F 7714 03B5 80F8 2655 8194 EC1E E5CA 61F8 3EC8 0040 F495 F495 FF30 EC03 E5CA F074 2E2F F073 2E64
 *
 * Intent: Bit-gated block copy with tail chain. TC = bit 14
 * of *AR2 (bitf single-bit mask, both TC senses coincide);
 * cell 0x263A &= 0xE3FF (andm #-7169); TC set runs cell |=
 * 6144 (bc 0x3346,ntc skips the orm); A = *AR2 arith>>8
 * (ld Smem,SHIFT; second word 0C58: SHIFT5 = 24 -> -8,
 * SXM = 1 flagged); A &= 63 (upper cleared); B = *AR2 with
 * AR2 += AR0 (circular +0%, wrap needs caller-live BK,
 * linear modeled flagged); B &= 63; AR4 = 949; cell 0x2655
 * = A-low; cell AR4 = B-low with AR4 post-incremented;
 * 31 passes (rpt #30) of cell AR4 = *(AR2) with AR4++ and
 * AR2 += AR0 (mvdd linear form per the 351d precedent,
 * wrap flagged); TC = bit 6 of cell 0x3EC8; xc 2,tc skips
 * the 4-pass (rpt #3) repeat copy iff TC set (351d
 * precedent: xc covers rpt + mvdd, skips it whole);
 * runs 0x2E2F (extern) then tail-branches to frag_2E64
 * (extern). ARs/A/B dead into the tail (flagged). Bound
 * 333C-335F.
 */
extern void sub_2E2F(void);
extern void frag_2E64(void);

void frag_333C(int ar0_live, int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar4;
    long a;
    long b;
    int i;
    {                                                    /* bitf *ar2,#16384 */
        int tc = (*ar2 & 16384) != 0;
        *(volatile int *)0x263A &= 58367;            /* andm #-7169 (always) */
        if (tc)                                      /* bc 0x3346,ntc */
            *(volatile int *)0x263A |= 6144;         /* orm #6144 */
    }
    a = (long)*ar2 >> 8;                             /* ld *ar2,-8,a (arith) */
    a &= 63;                                         /* and #63,a */
    b = (long)*ar2;                                  /* ld *ar2+%,b (SXM flagged) */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    b &= 63;                                         /* and #63,b */
    ar4 = (int *)949;                                /* stm #949,ar4 */
    *(volatile int *)0x2655 = (int)(a & 0xFFFF);     /* stl a,*(0x2655) */
    *ar4++ = (int)(b & 0xFFFF);                      /* stl b,*ar4+ */
    for (i = 0; i < 31; i++) {                       /* rpt #30 + mvdd */
        *ar4++ = *ar2;
        ar2 += ar0_live;                             /* +0% (wrap flagged) */
    }
    if ((*(volatile int *)0x3EC8 & 64) == 0) {       /* bitf; xc 2,tc */
        for (i = 0; i < 4; i++) {                    /* rpt #3 + mvdd */
            *ar4++ = *ar2;
            ar2 += ar0_live;                         /* +0% (wrap flagged) */
        }
    }
    sub_2E2F();                                      /* call 0x2e2f */
    frag_2E64();                                      /* b 0x2e64 (tail) */
}
