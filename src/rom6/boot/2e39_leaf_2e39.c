/* ROM6 0x2E39 LEAF_2E39 -- 25w.
 * Verified encoding: src/rom6/boot/2e39_leaf_2e39.asm (recombine MATCH).
 * ORIGIN 0x2E39
 * EXPECT: 61F8 0549 0020 F820 2E4A 4A12 7713 0549 6883 FFDF 7714 009F 7715 0002 F074 2C88 8A12 61F8 054D 0004 F820 2E52 F074 2E64 FC00
 *
 * Intent: Flag-cell setup plus tail chain. Bit 5 of cell 0x549 clear jumps to the 2E4A fragment (bc 0x2e4a,ntc: 2E4A = bit-test plus tail to 2E52, forward extern, bytes cited); else saves AR2 (pshm, hardware state), AR3 = 1353 with bit 5 cleared, AR4 = 159, AR5 = 2 feed 0x2C88; restores AR2 (popm); bit 2 of cell 0x54D clear jumps to the 2E52 entry (bc 0x2e52,ntc, C: frag_2E52); else call 0x2E64; return.
 */
extern void frag_2E4A(void); /* joins 2e39_leaf_2e39 interior @+0x11; see docs/evidence/extern-triage.md */
extern void sub_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */
extern void frag_2E52(void);
extern void sub_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

static int *G_AR3;
static int *G_AR4;
static int *G_AR5;

void leaf_2E39(void)
{
    if ((*(volatile int *)0x549 & 32) == 0) {    /* bitf, bc ntc */
        frag_2E4A();                             /* tail (bytes cited) */
        return;
    }
    /* pshm ar2 (hardware state, no C form) */
    G_AR3 = (int *)1353;                         /* stm #1353,ar3 */
    *G_AR3 &= -33;                               /* andm #-33 */
    G_AR4 = (int *)159;                          /* stm #159,ar4 */
    G_AR5 = (int *)2;                            /* stm #2,ar5 */
    sub_2C88();                                  /* call 0x2c88 */
    /* popm ar2 (hardware state, no C form) */
    if ((*(volatile int *)0x54D & 4) == 0) {     /* bitf, bc ntc */
        frag_2E52();                             /* tail call */
        return;
    }
    sub_2E64();                                  /* call 0x2e64 */
    /* ret */
}
