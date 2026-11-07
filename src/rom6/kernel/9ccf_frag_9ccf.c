/* ROM6 0x9CCF FRAG_9CCF -- 24w.
 * Verified encoding: src/rom6/kernel/9ccf_frag_9ccf.asm (recombine MATCH).
 * ORIGIN 0x9CCF
 * EXPECT: 61F8 0860 0002 F820 9CE7 7712 29C9 E724 771A 004F F072 9CE5 1092 F074 06B8 9828 1092 F074 06B8 F030 00FF 1A84 8094 E94F
 *
 * Intent: Filter tap with dark tail. TC = (cell0x860 & 2) != 0
 * (bitf, 32b4 precedent); clear tail-enters dark FRAG_9CE7
 * (bc ntc; entry state of 9CE7 unbound -- its head calls dark
 * 0x6C8 first, flagged). Else AR2 = 10697, AR4 = AR2 (mvmm);
 * BRC = 79; 80 passes of A = *(AR2++) (ld), dark SUB_06B8,
 * *(AR4) = (A<<8) & 0xFFFF (STL-shift single-word form, grounded
 * per ti-c54x op_stl_shft_xmem: logical left, store low, exact;
 * no AR step), A = *(AR2++), dark SUB_06B8, A &= 255, A |= *AR4,
 * *(AR4++) = A-low (block [RSA = PC + 2 = 0x9CDB, REA = 0x9CE5];
 * RPTB non-delayed form, grounded precedent); B = 79, falls into
 * dark 0x9CE7 (B handoff value unbound -- the bc path carries
 * entry B, flagged). ARs dead at tail (flagged). Bound 9CCF-9CE6.
 */
extern void sub_06B8(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_9CE7(void); /* joins 9ce7_frag_9ce7; see docs/evidence/extern-triage.md */

void frag_9CCF(int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar4;
    long a;
    long b;
    int tc;
    int i;
    tc = (*(volatile int *)0x860 & 2) != 0;          /* bitf *(0x860),#2 */
    if (!tc) {                                       /* bc 0x9ce7,ntc */
        frag_9CE7();
        return;
    }
    ar2 = (int *)10697;                              /* stm #10697,ar2 */
    ar4 = ar2;                                       /* mvmm ar2,ar4 */
    /* stm #79,brc */
    for (i = 0; i < 80; i++) {                       /* rptb 0x9ce5 */
        a = (long)*ar2++;                            /* ld *ar2+,a */
        sub_06B8();                                  /* call 0x6b8 (dark) */
        *ar4 = (int)(((unsigned long)a << 8) & 0xFFFF); /* stl a,8,*ar4 */
        a = (long)*ar2++;                            /* ld *ar2+,a */
        sub_06B8();                                  /* call 0x6b8 (dark) */
        a &= 255;                                    /* and #255,a */
        a |= (long)*ar4;                             /* or *ar4,a */
        *ar4++ = (int)(a & 0xFFFF);                  /* stl a,*ar4+ */
    }
    b = 79;                                          /* ld #79,b */
    (void)b;                                         /* B handoff unbound (flagged) */
    frag_9CE7();                                     /* fall-through (dark tail) */
}
