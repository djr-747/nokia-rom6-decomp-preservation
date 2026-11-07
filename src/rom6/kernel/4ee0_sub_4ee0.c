/* ROM6 0x4EE0 SUB_4EE0 -- 19w.
 * Verified encoding: src/rom6/kernel/4ee0_sub_4ee0.asm (recombine MATCH).
 * ORIGIN 0x4EE0
 * EXPECT: F074 059C 6FF8 2F1F 0C48 7213 2F1E 7712 2F5B 6C83 4EF3 7713 0912 7714 250A F273 4EF9 11F8 250E
 *
 * Intent: Counter-gated delayed branch. Runs 0x59C (dark, forward extern); A = cell 0x2F1F << 8 (ld shifted form); AR3 = cell 0x2F1E; nonzero AR3 (post-decremented, BANZ per ti-c54x branch_sind: while (ar-- != 0)) tail-enters FRAG_4EF3 with A = cell << 8, AR2 = 12123 (the preset feeds the tail, not dead), and caller-live BRC threaded through as brc_live_in. Else dead AR3/AR4 presets (noted); B = cell 0x250E in the bd delay slot (always runs); branch to dark 0x4EF9 (bd, forward extern). Bound 4EE0-4EF2.
 */
extern void sub_059C(void);
extern void frag_4EF3(long a_live_in, int *ar2_in, int brc_live_in);
extern void frag_4EF9(void);

void sub_4EE0(int brc_live_in)
{
    long a;
    int ar3;
    sub_059C();                                  /* call 0x59c */
    a = (long)*(volatile int *)0x2F1F << 8;      /* ld *(0x2f1f),8,a */
    ar3 = *(volatile int *)0x2F1E;           /* mvdm 0x2f1e,ar3 */
    /* stm #12123,ar2 (preset feeds the 4EF3 tail) */
    if (ar3-- != 0) {                            /* banz 0x4ef3,*ar3 */
        frag_4EF3(a, (int *)12123, brc_live_in);  /* tail */
        return;
    }
    /* stm #2322,ar3; stm #9482,ar4 (dead presets) */
    {
        int b = *(volatile int *)0x250E;     /* bd delay (always runs) */
        (void)b;                                 /* B dead (branch away) */
    }
    frag_4EF9();                                 /* bd 0x4ef9 */
}
