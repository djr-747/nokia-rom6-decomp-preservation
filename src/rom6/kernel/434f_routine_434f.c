/* ROM6 0x434F ROUTINE_434F -- 29w.
 * Verified encoding: src/rom6/kernel/434f_routine_434f.asm (recombine MATCH).
 * ORIGIN 0x434F
 * EXPECT: F074 0608 4A17 7717 0007 E900 61F8 3EC8 0040 F495 F495 890E 8910 FF30 7717 000B FF30 7710 03C0 F074 436C 7717 0017 F274 436C 7710 01FF 8A17 FC00
 *
 * Intent: Guard preset with chained call. Runs 0x608
 * (dark, extern); saves entry AR7 (pshm, hardware state
 * -- an ar7_saved local stands in per the 2D5E
 * precedent); AR7 = 7; B = 0 (ld); TC = bit 6 of cell
 * 0x3EC8 (bitf); T = B-low = 0 (stlm b,t; T feeds the
 * dark 436C calls below opaquely, flagged); AR0 = 0
 * (stlm b,ar0; AR0 write-only in-span, its 511 live-out
 * dropped, flagged); TC clear runs AR7 = 11 (xc 2,tc
 * covers the 2-word stm) and AR0 = 960 (xc 2,tc);
 * runs 0x436C (dark pool span -- ROR/ADDC/BANZD have no
 * oracle form -- forward extern); AR7 = 23; the calld
 * delay slot AR0 = 511 runs BEFORE the second call to
 * 0x436C (calld, grounded delayed-call); restores entry
 * AR7 (popm; the stepped local dies) and returns. ARs
 * dead at return (flagged). Bound 434F-436B.
 */
extern void sub_0608(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_436C(void); /* joins 436c_routine_436c; see docs/evidence/extern-triage.md */

void routine_434F(int ar7_live)
{
    int ar7_saved = ar7_live;                        /* pshm ar7 */
    int ar7 = 7;                                     /* stm #7,ar7 */
    long b = 0;                                      /* ld #0,b */
    int ar0 = 0;                                     /* stlm b,ar0 */
    int t;
    int tc;
    sub_0608();                                      /* call 0x608 */
    tc = (*(volatile int *)0x3EC8 & 64) != 0;        /* bitf *(0x3ec8),#64 */
    /* nop; nop */
    t = (int)(b & 0xFFFF);                           /* stlm b,t (= 0) */
    if (!tc)                                         /* xc 2,tc */
        ar7 = 11;                                    /* stm #11,ar7 */
    if (!tc)                                         /* xc 2,tc */
        ar0 = 960;                                   /* stm #960,ar0 */
    sub_436C();                                      /* call 0x436c */
    ar7 = 23;                                        /* stm #23,ar7 */
    ar0 = 511;                                       /* calld delay (runs first) */
    sub_436C();                                      /* calld 0x436c */
    ar7 = ar7_saved;                                 /* popm ar7 */
    /* ret (AR0 = 511 live-out, dropped, flagged) */
    (void)t;
    (void)ar0;
}
