/* ROM6 0x54A4 MSG_FETCH_ROUTINE -- 23w.
 * Verified encoding: src/rom6/kernel/54a4_msg_fetch_routine.asm (recombine MATCH).
 * ORIGIN 0x54A4
 * EXPECT: F074 06E6 76F8 01F3 2C00 76F8 0243 2C00 F000 2C00 80F8 054A 80F8 054B 771A 0277 E800 F272 54B9 7711 2C00 8091 FC00
 *
 * Intent: Producer-cell preset plus window clear. Runs dark SUB_06E6
 * (entry A flows through the dark call, clobber risk flagged);
 * A += 11264; cells 0x1F3/0x243 = 11264; cells 0x54A/0x54B = A-low;
 * A = 0; the rptbd delay slot AR1 = 11264 runs once; the delayed
 * block [RSA = PC + 4 = 0x54B9 = REA] is the single STL, run
 * BRC + 1 = 632 times (RPTBD shape per the vendored TI note in
 * ti-c54x opcode_catalog.def; execution stays deferred, flagged);
 * return (AR1 live-out dropped, flagged). Bound 54A4-54BA.
 */
extern void sub_06E6(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void msg_fetch_routine_54A4(long a_live)
{
    int *ar1;
    int i;
    long a;
    sub_06E6();                                      /* call 0x6e6 (dark) */
    a = a_live + 11264;                              /* add #11264,a */
    *(volatile int *)0x1F3 = 11264;                  /* st #11264,*(0x1f3) */
    *(volatile int *)0x243 = 11264;                  /* st #11264,*(0x243) */
    *(volatile int *)0x54A = (int)(a & 0xFFFF);      /* stl a,*(0x54a) */
    *(volatile int *)0x54B = (int)(a & 0xFFFF);      /* stl a,*(0x54b) */
    /* stm #631,brc; ld #0,a */
    ar1 = (int *)11264;                              /* rptbd delay: stm (once) */
    for (i = 0; i < 632; i++)                        /* rptbd 0x54b9 */
        *ar1++ = 0;                                  /* stl a,*ar1+ (A=0) */
    /* ret */
}
