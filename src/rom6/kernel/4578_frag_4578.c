/* ROM6 0x4578 FRAG_4578 -- 7w.
 * Verified encoding: src/rom6/kernel/4578_frag_4578.asm (recombine MATCH).
 * ORIGIN 0x4578
 * EXPECT: 4913 F074 4055 8084 7716 0000 FC00
 *
 * Intent: Helper-call plus store. B = AR3 (live-in), call 0x4055, store result through live-in AR4, clear AR6, return.
 */
extern int sub_4055(int b_in); /* joins 4055_port0_txn_phase2; see docs/evidence/extern-triage.md */

static int *G_AR6;

int frag_4578(int *par3, int *par4)
{
    int a = sub_4055((int)par3);                 /* ldm ar3,b; call 0x4055 */
    *par4 = a;                                   /* stl a,*ar4 */
    G_AR6 = (int *)0;                            /* stm #0,ar6 */
    return a;                                    /* ret */
}
