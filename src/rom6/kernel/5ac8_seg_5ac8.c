/* ROM6 0x5AC8 SEG_5AC8 -- 51w deinterleave engine, four entries, one EXPECT.
 * Verified encoding: src/rom6/kernel/5ac8_seg_5ac8.asm (recombine MATCH).
 * ORIGIN 0x5AC8
 * EXPECT: F002 2B1C F47E E910 890E 8813 7715 0000 7711 0001 7716 0003 771A 0038 F072 5AEA 1483 F063 000F 6DB4 8284 F300 0008 F640 F330 000F 6DF0 0040 FD4D E910 F620 890E E724 FD45 6D93 6D95 62F8 0015 0039 8810 890E 4813 60F8 250F 0022 F820 5AFB 08F8 352C F073 5AFD
 *
 * Intent: Nibble deinterleave scatter with re-bias. Entries: FRAG_5AC8
 * (adds 11036 << 2: ADD #lk,SHFT = (lk << shift) + src per op_add_lk;
 * falls into 5ACA), FRAG_5ACA (full head), FRAG_5AD2 (middle re-entry:
 * re-arms AR6 = 3, falls into 5AD4), FRAG_5AD4 (inner re-entry: BRC = 56
 * re-armed = 57-count loop). FRAG_5ACA: A >>= 2 arithmetic (sfta, always
 * arithmetic); B = T = 16; AR3 = A-low (stlm); AR5 = 0; AR1 = 1; AR6 = 3;
 * AR0 = 0 and BK = 456 live in from ROUTINE_5AAC (stm pair; assumed,
 * flagged). RPTB 57x (BRC = 56): A = *(AR3-address) << T (LD Xmem,TS,
 * SXM-widened per op_ld_xmem_shift; SXM = 1 assumed, OVM saturation noted
 * but unreached: values stay small); A &= 15 << 16 (AND_IMMEDIATE_SHIFT16
 * applies the shifted mask per op_logical_immediate: zero-extended lk16
 * << 16); AR4 += AR0 (mar *ar4+0, by-AR0 step per 4EBC); nibble store
 * *(AR2 + AR0) = A-high (sth); B += 8; A = B; B &= 15; AR0 += 64 circular
 * mod BK = 456 (mar *+ar0(0x40)%; 64k mod 456 hits 57 distinct slots:
 * deinterleave stride); B == 0 skips B = 16 (xc 1,beq); A -= B; T = B-low;
 * AR4 = AR2 (mvmm); A != 0 advances AR3 (xc 1,aeq; skips one AR3 on the
 * all-zero nibble); AR5++ (advanced, never read in span: stride counter,
 * possible live-out, trace-confirmable). Mid-tail: A = *(0x15) * 57
 * (mpy); AR0 = A-low; T = B-low (loop-exit B); A = AR3-address (ldm;
 * 16-bit); id != 34 tail-enters FRAG_5AFB (bc ntc) else A -= *(0x352C)
 * (sub Smem, SXM = 1 sign-extend per op_sub_smem) and tail-enters
 * FRAG_5AFD (b). Steady state from the ACA head is T = 16 with AR3++
 * every iteration (B cycles 16 -> 8 -> 16); the 5AD4 back-edge instead
 * seeds B = T = 12 from the FRAG_5AFD tail (ld #12,b), so each middle
 * pass opens with one T = 12 nibble then settles (HYPOTHESIS from code
 * shape, trace-confirmable). Bound 5AC8-5AFA; exits to FRAG_5AFB/5AFD.
 */
extern void frag_5AFB(long a_live, int *par2, int ar3, int ar5, int ar0,
                      long b_live, int t_live, int ar6, int ar1);
extern void frag_5AFD(long a_live, int *par2, int ar3, int ar5, int ar0,
                      long b_live, int t_live, int ar6, int ar1);

void frag_5AD4(int *par2, int ar3, int ar5, int ar0, long b_live,
               int t_live, int ar6, int ar1)
{
    long a;
    long b = b_live;
    int t = t_live;
    int *par4 = par2;                            /* AR4 = AR2 on entry */
    int k;

    for (k = 0; k < 57; k++) {                   /* stm #56,brc; rptb */
        a = (long)*(volatile int *)ar3 << t;     /* ld *ar3,ts,a */
        a &= (15L << 16);                        /* and #15,16,a */
        par4 += ar0;                             /* mar *ar4+0 */
        *par4 = (int)((a >> 16) & 0xFFFF);       /* sth a,*ar4 */
        b += 8;                                  /* add #8,b */
        a = b;                                   /* ld b,a */
        b &= 15;                                 /* and #15,b */
        ar0 += 64;                               /* mar *+ar0(0x40)% */
        if (ar0 >= 456)                          /* BK = 456 (head) */
            ar0 -= 456;
        if (b != 0)                              /* xc 1,beq */
            b = 16;                              /* ld #16,b */
        a -= b;                                  /* sub b,a */
        t = (int)(b & 0xFFFF);                   /* stlm b,t */
        par4 = par2;                             /* mvmm ar2,ar4 */
        if (a != 0)                              /* xc 1,aeq */
            ar3++;                               /* mar *ar3+ */
        ar5++;                                   /* mar *ar5+ (unread) */
    }
    a = (long)*(volatile int *)0x15 * 57L;       /* mpy *(0x15),#57,a */
    ar0 = (int)(a & 0xFFFF);                     /* stlm a,ar0 */
    t = (int)(b & 0xFFFF);                       /* stlm b,t */
    a = (long)(ar3 & 0xFFFF);                    /* ldm ar3,a */
    if (*(volatile int *)0x250F != 34) {         /* cmpm; bc ntc */
        frag_5AFB(a, par2, ar3, ar5, ar0, b, t, ar6, ar1);
        return;
    }
    /* sub *(0x352c),a (SXM = 1 sign-extend, flagged) */
    frag_5AFD(a - (long)*(volatile int *)0x352C, par2, ar3, ar5, ar0,
              b, t, ar6, ar1);                   /* b 0x5afd */
}

void frag_5AD2(int *par2, int ar3, int ar5, int ar0, long b_live,
               int t_live, int ar1)
{
    /* stm #3,ar6; falls into 5AD4 */
    frag_5AD4(par2, ar3, ar5, ar0, b_live, t_live, 3, ar1);
}

void frag_5ACA(long a_live, int *par2)
{
    long a = a_live >> 2;                        /* sfta a,-2 */
    /* ld #16,b; stlm b,t; stlm a,ar3; stm #0,ar5; stm #1,ar1 */
    /* AR0 = 0 live-in from ROUTINE_5AAC head (assumed, flagged) */
    frag_5AD2(par2, (int)(a & 0xFFFF), 0, 0, 16L, 16, 1);
}

void frag_5AC8(long a_live, int *par2)
{
    /* add #11036,2,a; falls into 5ACA */
    frag_5ACA(a_live + (11036L << 2), par2);
}
