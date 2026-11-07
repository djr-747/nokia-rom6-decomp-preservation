/* ROM6 0x9F0A SUB_9F0A -- 15w.
 * Verified encoding: src/rom6/kernel/9f0a_sub_9f0a.asm (recombine MATCH).
 * ORIGIN 0x9F0A
 * EXPECT: F120 8000 1BF8 0914 81F8 29C8 E828 E902 7710 00F3 F274 93CE 7712 29C8 FC00
 *
 * Intent: Sign-bit OR plus call. B = -32768 | cell 0x914, stored to cell 0x29C8; A = 40, B = 2, AR0 = 243; calls 0x93CE with AR2 = 10696 in the calld delay slot (executes first), returns.
 */
extern void sub_93CE(void); /* joins 93ce_msg_classify_by_caller; see docs/evidence/extern-triage.md */

static int *G_AR0;
static int *G_AR2;

void sub_9F0A(void)
{
    int b = -32768 | *(volatile int *)0x914; /* ld, or */
    *(volatile int *)0x29C8 = b;             /* stl */
    /* ld #40,a; ld #2,b; stm #243,ar0 */
    G_AR0 = (int *)243;
    G_AR2 = (int *)10696;                        /* calld delay slot */
    sub_93CE();                                  /* calld 0x93ce */
    /* ret */
}
