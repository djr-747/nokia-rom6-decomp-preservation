/* ROM6 0x315F RPTB_LANE_315F -- 26w.
 * Verified encoding: src/rom6/kernel/315f_rptb_lane_315f.asm (recombine MATCH).
 * ORIGIN 0x315F
 * EXPECT: 771A 0001 7714 254F F072 316A 12D2 6F94 0C98 F030 00FF 8094 EC1E E5CA 61F8 3EC8 0040 F495 F495 FF30 EC03 E5CA F074 2E2F F073 2E64
 *
 * Intent: Split-sample sweep with conditional second fill. BRC = 1; AR4 = 9551; 2x rptb block: A = zero-
 * extended *AR2++ (ldu, circular % flagged linear ++); *AR4++ = A >> 8 (stl a,-8; A non-negative by lane,
 * exact); A &= 255 (and); *AR4++ = A (stl); 31x mvdd *AR2+0%,*AR4+ (rpt #30; AR2 += AR0-live, +0% wrap needs
 * caller-live BK, linear flagged); TC = cell 0x3EC8 & 64 (bitf); TC taken runs second 4x fill (rpt #3 mvdd;
 * xc 2,tc skips rpt+mvdd exactly); dispatcher_entry_2E2F(); b-tail frag_2E64() (operand @3178 in-span,
 * 649d split precedent). Post-branch head (prev b 2e64); no exterior callers, entry unconfirmed, flagged.
 */
extern void dispatcher_entry_2E2F(void);
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

void frag_315F(int *par2, int ar0_live)
{
    long a;
    int *ar2;
    int *ar4;
    int taken;
    int i;


    ar2 = par2;
    ar4 = (int *)9551;                                     /* stm #9551,ar4 */
    /* stm #1,brc; rptb 0x316a (2 iters) */
    for (i = 0; i < 2; i++) {
        a = (long)(unsigned)*ar2++;                         /* ldu *ar2+%,a (wrap flagged) */
        *ar4++ = (int)((a >> 8) & 0xFFFF);                  /* stl a,-8,*ar4+ (A>=0 exact) */
        a &= 255L;                                         /* and #255,a */
        *ar4++ = (int)a;                                   /* stl a,*ar4+ */
    }
    for (i = 0; i < 31; i++) {                             /* rpt #30 */
        *ar4++ = *ar2;                                     /* mvdd *ar2+0%,*ar4+ */
        ar2 += ar0_live;                                   /* +0% (wrap flagged) */
    }
    taken = (*(volatile int *)0x3EC8 & 64) != 0;          /* bitf *(0x3ec8),#64 */
    if (taken) {                                           /* xc 2,tc */
        for (i = 0; i < 4; i++) {                           /* rpt #3 */
            *ar4++ = *ar2;
            ar2 += ar0_live;
        }
    }
    dispatcher_entry_2E2F();                               /* call 0x2e2f */
    frag_2E64();                                           /* b 0x2e64 (tail) */
}
