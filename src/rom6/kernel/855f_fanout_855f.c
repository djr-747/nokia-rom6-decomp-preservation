/* ROM6 0x855F FANOUT_855F -- 19w.
 * Verified encoding: src/rom6/kernel/855f_fanout_855f.asm (recombine MATCH).
 * ORIGIN 0x855F
 * EXPECT: E742 E753 F074 8572 1086 F074 8573 F074 8572 F074 8572 1086 F074 8573 F074 8572 F074 8588 FC00
 *
 * Intent: XOR-fold fanout. AR2 = AR4, AR3 = AR5 (mvmm, live-ins); interleaved 0x8572 folds (C: xor_fold) on *AR6 (live-in) with 0x8573 calls, ending in the 0x8588 block copy (C: block_copy_8588); return.
 */
extern int xor_fold(int *acc, int *src);
extern void sub_8573(void); /* joins 8572_xor_fold interior @+0x1; see docs/evidence/extern-triage.md */
extern void block_copy_8588(int *src);

static int *G_AR2;
static int *G_AR3;

void fanout_855F(int *ar4_in, int *ar5_in, int *ar6_in)
{
    int a;
    G_AR2 = ar4_in;                              /* mvmm ar4,ar2 */
    G_AR3 = ar5_in;                              /* mvmm ar5,ar3 */
    a = xor_fold(G_AR2, ar6_in);                 /* call 0x8572; ld */
    (void)a;
    sub_8573();                                  /* call 0x8573 */
    a = xor_fold(G_AR2, ar6_in);                 /* call; ld */
    (void)a;
    a = xor_fold(G_AR2, ar6_in);                 /* call; ld */
    (void)a;
    sub_8573();                                  /* call 0x8573 */
    a = xor_fold(G_AR2, ar6_in);                 /* call 0x8572 */
    (void)a;
    block_copy_8588(G_AR3);                      /* call 0x8588 */
    /* ret */
}
