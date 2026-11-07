/* ROM6 0x8A45 ROUTINE_8A45 -- 15w.
 * Verified encoding: src/rom6/kernel/8a45_routine_8a45.asm (recombine MATCH).
 * ORIGIN 0x8A45
 * EXPECT: F074 0590 7712 1100 F071 0008 8092 771A 0080 F272 8A52 7692 0028 8092 FC00
 *
 * Intent: Zero-fill with sentinel. Runs dark SUB_0590; AR2 = 4352;
 * RPTZ zeroes A and repeats the store 9 times (RC = 8, catalog RPTZ
 * note: 0 -> dst, lk -> RC); the rptbd delay slot stores 40 once
 * (st #40,*ar2+); the delayed block [RSA = PC + 4 = 0x8A52, REA] is
 * the single STL, run BRC + 1 = 129 times (RPTBD shape per the
 * vendored TI SPRU172C note in ti-c54x opcode_catalog.def; RPTBD
 * execution stays deferred in the core, flagged). Return; AR2
 * live-out dropped (flagged). Bound 8A45-8A53.
 */
extern void sub_0590(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void routine_8A45(void)
{
    int *ar2;
    int i;
    sub_0590();                                      /* call 0x590 (dark) */
    ar2 = (int *)4352;                               /* stm #4352,ar2 */
    for (i = 0; i < 9; i++)                          /* rptz a,#8 (A=0) */
        *ar2++ = 0;                                  /* stl a,*ar2+ */
    *ar2++ = 40;                                     /* rptbd delay: st #40 (once) */
    for (i = 0; i < 129; i++)                        /* stm #128,brc; rptbd 0x8a52 */
        *ar2++ = 0;                                  /* stl a,*ar2+ (A=0) */
    /* ret */
}
