/* ROM6 0x37D8 FRAG_37D8 -- 42w.
 * Verified encoding: src/rom6/kernel/37d8_frag_37d8.asm (recombine MATCH).
 * ORIGIN 0x37D8
 * EXPECT: F074 05A0 61F8 0860 0090 F920 9E85 F074 942E 7710 0001 E736 8814 FC45 4813 F030 00FF F110 0000 F84C 3862 4814 F030 00FF F110 00F0 F84D 3802 F110 00F2 F84D 3806 F110 00F4 F84D 381B F110 00F7 F84D 3879 F073 3862
 *
 * Intent: Residue dispatch over live A. Runs 0x5A0 (dark,
 * extern; entry A assumed preserved through it, flagged);
 * TC = bit 4 or 7 of cell 0x860 (bitf #144, ANY-bit per
 * the oracle); set runs 0x9E85 (cc, conditional call
 * grounded) and rejoins; A = sub_942E() (dark callee, A
 * live-out as int return per the 2E64 convention);
 * AR0 = 1 (feeds the 3862 tails below); AR6 = AR3-value
 * (mvmm, dead after, noted); AR4 = A-low (stlm); A == 0
 * returns (rc aeq, grounded); A = AR3-value (ldm, AR3 is
 * caller-live) & 255 (upper cleared); B = A - 0 (sub lk);
 * nonzero tail-calls frag_3862 with live AR2/AR5 and
 * AR0 = 1 (bc 0x3862,bneq; the callee now has C intent);
 * else A = AR4-value (ldm, i.e. the 942E A-out low) &
 * 255; B = A - 240 runs frag_3802 on zero (bc beq; C,
 * parameterless); B = A - 242 runs frag_3806 with live
 * AR2 on zero (bc beq; C); B = A - 244 runs frag_381B
 * with live AR2 on zero (bc beq; C); B = A - 247 runs
 * frag_3879 with live AR5 and AR2 on zero (bc beq; C);
 * else tail-calls frag_3862 with live AR2/AR5 and AR0 = 1
 * (b 0x3862). AR2/AR5 are caller-live throughout (no
 * in-span step); ARs/A/B dead at exit (flagged). Bound
 * 37D8-3801.
 */
extern void sub_05A0(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_9E85(void); /* joins 9e85_wrap_9e85; see docs/evidence/extern-triage.md */
extern int sub_942E(void); /* joins 942e_cobba_verify_loop; see docs/evidence/extern-triage.md */
extern void frag_3862(int *ar2_in, int ar5_live, int ar0_live);
extern void frag_3802(void);
extern void frag_3806(int *ar2_in);
extern void frag_381B(int *par2);
extern void frag_3879(int ar5_live, int *ar2_in);

void frag_37D8(long a_live, int *ar2_in, int *ar3_in, int ar5_live)
{
    long a = a_live;
    long b;
    int ar4v;
    sub_05A0();                                      /* call 0x5a0 */
    if ((*(volatile int *)0x860 & 144) != 0)         /* bitf #144 */
        sub_9E85();                                  /* cc 0x9e85,ntc */
    a = sub_942E();                                  /* call 0x942e (A-out) */
    ar4v = (int)(a & 0xFFFF);                        /* stlm a,ar4 */
    if (a == 0)                                      /* rc aeq */
        return;
    a = (long)*ar3_in;                               /* ldm ar3,a (AR3 live) */
    a &= 255;                                        /* and #255,a */
    b = a;                                           /* sub #0,a,b */
    if (b != 0) {                                    /* bc 0x3862,bneq */
        frag_3862(ar2_in, ar5_live, 1);
        return;
    }
    a = (long)ar4v;                                  /* ldm ar4,a */
    a &= 255;                                        /* and #255,a */
    b = a - 240;                                     /* sub #240,a,b */
    if (b == 0) {                                    /* bc 0x3802,beq */
        frag_3802();
        return;
    }
    b = a - 242;                                     /* sub #242,a,b */
    if (b == 0) {                                    /* bc 0x3806,beq */
        frag_3806(ar2_in);
        return;
    }
    b = a - 244;                                     /* sub #244,a,b */
    if (b == 0) {                                    /* bc 0x381b,beq */
        frag_381B(ar2_in);
        return;
    }
    b = a - 247;                                     /* sub #247,a,b */
    if (b == 0) {                                    /* bc 0x3879,beq */
        frag_3879(ar5_live, ar2_in);
        return;
    }
    frag_3862(ar2_in, ar5_live, 1);                   /* b 0x3862 (tail) */
}
