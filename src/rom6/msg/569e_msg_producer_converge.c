/* ROM6 0x569E MSG_PRODUCER_CONVERGE_569E -- 4w.
 * Verified encoding: src/rom6/msg/569e_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x569E
 * EXPECT: 80F8 264E F074 77EE
 *
 * Intent: Store plus zerofill call. Stores A-live-in to cell 0x264E, runs ZEROFILL_RETD 0x77EE (has .asm, no C yet, forward extern); falls into the next convergence head on return. 4w per .asm header (no yaml bound entry; recombine MATCH).
 */
extern void zerofill_retd(void); /* 77ee_zerofill_retd; see docs/evidence/extern-triage.md */
void frag_569E(int a_live)
{
    *(volatile int *)0x264E = a_live;        /* stl a,*(0x264e) */
    zerofill_retd();                             /* call 0x77ee */
    /* falls through (no exit in span) */
}
