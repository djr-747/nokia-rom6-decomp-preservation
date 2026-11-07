/* ROM6 0x44E7 FRAG_44E7 -- 22w.
 * Verified encoding: src/rom6/kernel/44e7_frag_44e7.asm (recombine MATCH).
 * ORIGIN 0x44E7
 * EXPECT: F074 2E2F 7712 2F00 E723 7692 1000 7092 054E 6FF8 022D 0C48 1AF8 2623 8082 7714 0074 F274 2C88 7715 0006 FC00
 *
 * Intent: Dispatcher plus shifted-OR store. Runs the 0x2E2F dispatcher entry; AR2 = 12032, AR3 = AR2 (mvmm); stores 4096 with post-increment; cell 0x54E through AR2++; A = (cell 0x22D << 8) OR cell 0x2623 stored through AR2; AR4 = 116 feeds 0x2C88 with AR5 = 6 in the calld delay slot (executes first); return.
 */
extern void dispatcher_entry_2E2F(void);
extern void sub_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */

static int *G_AR2;
static int *G_AR3;
static int *G_AR4;
static int *G_AR5;

void frag_44E7(void)
{
    int a;
    dispatcher_entry_2E2F();                    /* call 0x2e2f */
    G_AR2 = (int *)12032;                        /* stm #12032,ar2 */
    G_AR3 = G_AR2;                               /* mvmm ar2,ar3 */
    *G_AR2++ = 4096;                             /* st #4096,*ar2+ */
    *G_AR2++ = *(volatile int *)0x54E;       /* mvkd 0x54e,*ar2+ */
    a = ((int)*(volatile int *)0x22D << 8) |
        *(volatile int *)0x2623;             /* ld, or */
    *G_AR2 = a;                                  /* stl a,*ar2 */
    G_AR4 = (int *)116;                          /* stm #116,ar4 */
    G_AR5 = (int *)6;                            /* calld delay slot */
    sub_2C88();                                  /* calld 0x2c88 */
    /* ret */
}
