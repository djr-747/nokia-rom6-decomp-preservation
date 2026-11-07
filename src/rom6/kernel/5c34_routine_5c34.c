/* ROM6 0x5C34 ROUTINE_5C34 -- 27w shift-accumulate scatter, one EXPECT.
 * Verified encoding: src/rom6/kernel/5c34_routine_5c34.asm (recombine MATCH).
 * ORIGIN 0x5C34
 * EXPECT: F074 0674 771A 0038 F072 5C4D F55E 8913 1816 F442 F484 880E 6DB3 1583 1961 81E1 2F80 1011 0060 F110 01C8 8811 1095 0017 FD4E 8911 FC00
 *
 * Intent: Negated-shift scatter over a caller window. Runs dark SUB_0674
 * (call). BRC = 56 re-arms a 57-iteration RPTB. Per iteration: B = A >>
 * 2 (ld a,-2,b: LD src,SHFT per op_ld_src_shift, SXM-arithmetic assumed,
 * flagged); AR3 = B-low (stlm); A &= *(DP+0x16) (and 0x16,a: DP = 0 from
 * the HUB_5BF1 prologue -- all 8 callers in-hub, solid); A <<= 2
 * (ld a,2,a); A = -A (neg a; TC preserved per op_neg_acc, no TC reader in
 * span); T = A-low, so T = -((A_entry & 3) << 2) mod 65536, i.e. T in
 * {0, 65532, 65528, 65524}; AR3 += AR0 (mar *ar3+0, by-AR0 per 4EBC; AR0
 * caller-live); B = *(AR3-address) << T (ld *ar3,ts,b: LD Xmem,TS per
 * op_ld_xmem_shift; effective barrel count for the wrapped-negative T
 * values is trace-confirmable, HYPOTHESIS -- transcribed literally);
 * B &= *(DP+0x61) (and 0x61,b: *(0x61) = 15); *(AR1 + 0x2F80) = B-low
 * (stl b,*ar1(0x2f80)); A = *(DP+0x11) + *(DP+0x60) (ld/add DP cells);
 * B = A - 456 (sub #456,a,b: A kept); AR1 = A-low (stlm); A =
 * *(AR5++) + *(DP+0x17) (ld/add: loop-carried A for the next iteration);
 * B > 0 skips AR1 = B-low (xc 1,bgt: XC skips WORDS per op_xc), so
 * AR1 = (B > 0) ? A-low : B-low. A-live-out (stream tail) unused by the
 * hub callers; B/T dead at RET @5C4E. AR5/AR0/AR1/A caller-live;
 * ASM untouched. Bound 5C34-5C4E.
 */
extern void sub_0674(void);

void sub_5C34(long a_live, int ar1_live, int *par5, int ar0_live)
{
    long a = a_live;
    long b;
    int t;
    int ar1 = ar1_live;
    int ar3;
    int ar0 = ar0_live;
    int k;

    sub_0674();                                        /* call 0x674 */
    /* stm #56,brc re-armed below as the 57-count */
    for (k = 0; k < 57; k++) {                   /* rptb 0x5c4d */
        b = a >> 2;                          /* ld a,-2,b (SXM?) */
        ar3 = (int)(b & 0xFFFF);                   /* stlm b,ar3 */
        a &= (long)*(volatile int *)0x16;          /* and 0x16,a */
        a <<= 2;                                   /* ld a,2,a */
        a = -a;                                    /* neg a */
        t = (int)(a & 0xFFFF);                     /* stlm a,t */
        ar3 = (ar3 + ar0) & 0xFFFF;                /* mar *ar3+0 */
        b = (long)*(volatile int *)ar3 << t;       /* ld *ar3,ts,b */
        b &= (long)*(volatile int *)0x61;          /* and 0x61,b */
        *(volatile int *)(ar1 + 0x2F80) = (int)(b & 0xFFFF); /* stl */
        a = (long)*(volatile int *)0x11 +
            (long)*(volatile int *)0x60;           /* ld/add */
        b = a - 456L;                              /* sub #456,a,b */
        ar1 = (int)(a & 0xFFFF);                   /* stlm a,ar1 */
        a = (long)*par5++ + (long)*(volatile int *)0x17; /* ld/add */
        if (b <= 0)                                /* xc 1,bgt */
            ar1 = (int)(b & 0xFFFF);                /* stlm b,ar1 */
    }
    /* ret @5C4E (A-live-out noted above) */
}
