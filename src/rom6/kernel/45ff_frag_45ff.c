/* ROM6 0x45FF FRAG_45FF -- 60w.
 * Verified encoding: src/rom6/kernel/45ff_frag_45ff.asm (recombine MATCH).
 * ORIGIN 0x45FF
 * EXPECT: F074 06F6 7713 2F00 EC02 E5C9 F074 2E2F 7712 04EF 7713 2F14 771A 0005 F072 4612 1092 F050 A5A5 8093 76F8 2F14 0000 F274 8534 7714 2F14 771A 0002 7714 2F14 68F8 2F16 FF00 7715 2F00 E900 F072 462E 1094 F030 7777 1C95 F495 F495 FF44 F120 0100 7713 2F00 7693 3602 818B 7714 0074 F274 2C88 7715 0004 FC00
 *
 * Intent: Mask-xor stage with counted store. Runs 0x6F6
 * (dark, extern); AR3 = 12032; 3 passes (rpt #2) of cell
 * AR3 = *(AR2) with AR3 post-incremented and AR2 += AR0
 * (mvdd *ar2+0%,*ar3+ per the 351d convention: read
 * pre-step address, step by AR0; AR0 caller-live,
 * circular wrap needs caller-live BK, linear modeled
 * flagged). Runs 0x2E2F (extern); AR2 = 1263, AR3 =
 * 12052; BRC = 5; 6 passes (rptb 0x4612) of A = *AR2
 * with AR2 post-incremented (ld; SXM = 1 flagged),
 * A ^= 42405 (xor K16 immediate zero-extended per the
 * logical-immediate leaf: upper preserved), cell AR3 =
 * A-low with AR3 post-incremented; cell 0x2F14 = 0 (st);
 * the calld delay slot AR4 = 12052 runs BEFORE sub_8534
 * (calld, C intent, parameterless); BRC = 2; AR4 = 12052
 * (reloaded); cell 0x2F16 &= 0xFF00 (andm #-256); AR5 =
 * 12032; B = 0; 3 passes (rptb 0x462e) of A = (*AR4++)
 * & 30583 (and #0x7777, upper cleared) XOR *(AR5++)
 * (xor Smem,A per op_xor_smem) with two nops, then A ==
 * 0 runs B = 256 (xc 2,aneq covers the 2-word ld;
 * i.e. B ends 256 iff any pass folded to zero, else 0).
 * AR3 = 12032; cell AR3 = 13826 with AR3 post-incremented
 * (st); cell AR3 = B-low with AR3 post-decremented
 * (stl b,*ar3-); AR4 = 116; the calld delay slot AR5 = 4
 * runs BEFORE routine_2C88 (dark, extern); return. AR2
 * steps on a local; AR3/AR4/AR5 locals; AR0 caller-live
 * read-only; A/B locals; all dead at return (flagged).
 * Bound 45FF-463A.
 */
extern void sub_06F6(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void dispatcher_entry_2E2F(void);
extern void sub_8534(void);
extern void routine_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */

void frag_45FF(int ar0_live, int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar3;
    int *ar4;
    int *ar5;
    long a;
    long b;
    int i;
    sub_06F6();                                      /* call 0x6f6 */
    ar3 = (int *)12032;                              /* stm #12032,ar3 */
    for (i = 0; i < 3; i++) {                        /* rpt #2 + mvdd */
        *ar3++ = *ar2;                               /* mvdd *ar2+0%,*ar3+ */
        ar2 += ar0_live;                             /* +0% (wrap flagged) */
    }
    dispatcher_entry_2E2F();                                      /* call 0x2e2f */
    ar2 = (int *)1263;                               /* stm #1263,ar2 */
    ar3 = (int *)12052;                              /* stm #12052,ar3 */
    /* stm #5,brc */
    for (i = 0; i < 6; i++) {                        /* rptb 0x4612 */
        a = (long)*ar2++;                            /* ld *ar2+,a (SXM flagged) */
        a ^= 42405;                                  /* xor #42405,a */
        *ar3++ = (int)(a & 0xFFFF);                  /* stl a,*ar3+ */
    }
    *(volatile int *)0x2F14 = 0;                     /* st #0,*(0x2f14) */
    ar4 = (int *)12052;                              /* calld delay (runs first) */
    sub_8534();                                      /* calld 0x8534 */
    /* stm #2,brc */
    ar4 = (int *)12052;                              /* stm #12052,ar4 */
    *(volatile int *)0x2F16 &= 65280;                 /* andm #-256 */
    ar5 = (int *)12032;                              /* stm #12032,ar5 */
    b = 0;                                           /* ld #0,b */
    for (i = 0; i < 3; i++) {                        /* rptb 0x462e */
        a = (long)*ar4++;                            /* ld *ar4+,a */
        a &= 30583;                                  /* and #30583,a */
        a ^= (long)*ar5++;                           /* xor *ar5+,a */
        /* nop; nop */
        if (a == 0)                                  /* xc 2,aneq */
            b = 256;                                 /* ld #256,b */
    }
    ar3 = (int *)12032;                              /* stm #12032,ar3 */
    *ar3++ = 13826;                                  /* st #13826,*ar3+ */
    *ar3-- = (int)(b & 0xFFFF);                      /* stl b,*ar3- */
    ar4 = (int *)116;                                /* stm #116,ar4 */
    ar5 = (int *)4;                                  /* calld delay (runs first) */
    routine_2C88();                                  /* calld 0x2c88 */
    /* ret */
}
