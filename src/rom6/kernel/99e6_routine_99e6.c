/* ROM6 0x99E6 ROUTINE_99E6 -- 25w.
 * Verified encoding: src/rom6/kernel/99e6_routine_99e6.asm (recombine MATCH).
 * ORIGIN 0x99E6
 * EXPECT: F074 05CE E721 6DD2 6DD2 11D2 F300 0007 F77F E712 E800 47F8 000B 1CD2 FA45 99FF 7312 21FB 76F8 21FE 0001 E800 FE00 80F8 20FE
 *
 * Intent: Offset-xor fold with taken-path tail. Runs 0x5CE
 * (dark, extern); saves AR2 to AR1; AR2 steps +AR0 three
 * times (two mars plus the ld step; circular +0%, wrap needs
 * caller-live BK, linear modeled flagged); B = *AR2 + 7 then
 * B arith>>= 1 (sfta, SXM = 1 flagged); restores AR2 from AR1
 * (net AR2 unchanged); A = 0; RC+1 passes (rpt Smem *(0xB))
 * of A ^= *AR2 with AR2 += AR0 (xor Smem exact per the
 * logical leaf; A stays 16-bit, long-safe); bcd to 0x99FF
 * (BCD grounded) with cell 0x21FB = post-loop AR2 running as
 * the delay slot in both paths; taken path enters frag_99FF
 * with the saved AR2 value and live AR0; fall-through path
 * sets cell 0x21FE = 1, A = 0, retd with the cell 0x20FE = 0
 * store running as the delay slot, then returns. AR0 is
 * caller-live throughout; ARs dead at return (flagged).
 * Bound 99E6-99FE.
 */
extern void sub_05CE(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_99FF(int ar1_live, int ar0_live);

void routine_99E6(int *ar2_in, int ar0_live)
{
    int *ar2 = ar2_in;
    int *ar1;
    long a;
    long b;
    int rc;
    int i;
    sub_05CE();                                  /* call 0x5ce */
    ar1 = ar2;                                   /* mvmm ar2,ar1 */
    ar2 += ar0_live;                             /* mar *ar2+% */
    ar2 += ar0_live;                             /* mar *ar2+% */
    b = (long)*ar2;                              /* ld *ar2+%,b */
    ar2 += ar0_live;                             /* +0% step */
    b += 7;                                      /* add #7,b */
    b >>= 1;                                     /* sfta b,-1 (arith, flagged) */
    ar2 = ar1;                                   /* mvmm ar1,ar2 (restore) */
    a = 0;                                       /* ld #0,a */
    rc = *(volatile int *)0xB;                   /* rpt *(0xb) */
    for (i = 0; i < rc + 1; i++) {               /* xor loop */
        a ^= (long)*ar2;                         /* xor *ar2+%,a */
        ar2 += ar0_live;                         /* +0% (wrap flagged) */
    }
    *(volatile int *)0x21FB = (int)ar2;          /* bcd delay (both paths) */
    if (a == 0) {                                /* bcd 0x99ff,aeq */
        frag_99FF((int)ar1, ar0_live);
        return;
    }
    *(volatile int *)0x21FE = 1;                 /* st #1,*(0x21fe) */
    a = 0;                                       /* ld #0,a */
    *(volatile int *)0x20FE = 0;                 /* retd delay (always runs) */
    /* retd */
    (void)b;                                     /* B dead at return (flagged) */
}
