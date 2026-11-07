/* ROM6 0x853B FANOUT26_853B -- 26w.
 * Verified encoding: src/rom6/kernel/853b_fanout26_853b.asm (recombine MATCH).
 * ORIGIN 0x853B
 * EXPECT: 7710 0004 E741 6DB1 7710 000A F074 855F E742 E713 F074 8577 F074 85E4 E712 E743 F074 8577 6D96 6C88 8541 F074 855F F074 85FD FC00
 *
 * Intent: Dual-fanout driver with counted repeat. AR1 = AR4 (mvmm;
 * mar *ar1+0 is a null step, no C form); AR0 = 10 (the earlier 4 is
 * dead). Loop body (do-while, banz bottom-test per 3199 precedent: test
 * pre-decrement value, always decrements, so 10+1 passes, flagged):
 * run 0x855F fanout (AR4/AR5/AR6 positional, 855F convention), AR2 = AR4,
 * AR3 = AR1, run 0x8577 OR-combine (AR2/AR3 positional, 8577 convention),
 * run 0x85E4 block copy (AR3/AR4 positional, 85E4 convention), AR2 = AR1,
 * AR3 = AR4, run 0x8577 again, AR6++ (mar). Tail: run 0x855F once more,
 * run dark 0x85FD (forward extern, asm-only), return. AR5 caller-live,
 * never set in-span (unbound local, flagged); pp1 rides the 8501 call
 * convention but is unused in-span (flagged). Mappings by convention
 * (unverified), flagged.
 */
extern void fanout_855F(int *ar4_in, int *ar5_in, int *ar6_in);
extern void or_combine_8577(int *p2, int *p3);
extern void block_copy_85E4(int *src3, int *src4);
extern void sub_85FD(void); /* joins 85fd_block_copy_85fd; see docs/evidence/extern-triage.md */

void fanout26_853B(int **pp1, int *ar4, int *ar6)
{
    int *ar1;
    int *ar2;
    int *ar3;
    int *ar5;      /* caller-live, never set in-span (flagged) */
    int ar0cnt;
    int taken;

    (void)pp1;                                         /* unused in-span (flagged) */
    ar1 = ar4;                                         /* mvmm ar4,ar1 */
    /* mar *ar1+0 (null step, no C form) */
    ar0cnt = 10;                                       /* stm #10,ar0 */
    for (;;) {
        fanout_855F(ar4, ar5, ar6);                    /* call 0x855f */
        ar2 = ar4;                                     /* mvmm ar4,ar2 */
        ar3 = ar1;                                     /* mvmm ar1,ar3 */
        or_combine_8577(ar2, ar3);                     /* call 0x8577 */
        block_copy_85E4(ar3, ar4);                     /* call 0x85e4 */
        ar2 = ar1;                                     /* mvmm ar1,ar2 */
        ar3 = ar4;                                     /* mvmm ar4,ar3 */
        or_combine_8577(ar2, ar3);                     /* call 0x8577 */
        ar6++;                                         /* mar *ar6+ */
        taken = (ar0cnt != 0);                         /* banz (always decs) */
        ar0cnt--;
        if (!taken)
            break;
    }
    fanout_855F(ar4, ar5, ar6);                        /* call 0x855f */
    sub_85FD();                                        /* call 0x85fd */
    /* ret */
}
