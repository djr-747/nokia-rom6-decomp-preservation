/* ROM6 0x9D0B FRAG_9D0B -- 11w.
 * Verified encoding: src/rom6/kernel/9d0b_frag_9d0b.asm (recombine MATCH).
 * ORIGIN 0x9D0B
 * EXPECT: F300 0002 F3E1 E828 7710 00F3 F274 93CE 7712 29C8 FC00
 *
 * Intent: Scaled-index call. B = (B + 2) << 1 (sftl 40-bit shift, live-in B); A = 40; AR0 = 243; calls 0x93CE with AR2 = 10696 in the calld delay slot (executes first), returns.
 */
extern void sub_93CE(void); /* joins 93ce_msg_classify_by_caller; see docs/evidence/extern-triage.md */

static int *G_AR0;
static int *G_AR2;

void frag_9D0B(int b_in)
{
    int b = (b_in + 2) << 1;                     /* add #2,b; sftl b,1 */
    int a = 40;                                  /* ld #40,a */
    (void)a;
    G_AR0 = (int *)243;                         /* stm #243,ar0 */
    G_AR2 = (int *)10696;                        /* calld delay slot */
    sub_93CE();                                  /* calld 0x93ce */
    (void)b;
    /* ret */
}
