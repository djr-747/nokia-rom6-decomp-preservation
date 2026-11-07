/* ROM6 0x670D FRAG_670D -- 70w quad MIN-select into 0x6753/0x676A tails.
 * Verified encoding: src/rom6/kernel/670d_frag_670d.asm (recombine MATCH).
 * ORIGIN 0x670D
 * EXPECT: 60F8 000B 0040 F830 6717 60F8 000B 0080 F820 676A 7711 2642 E933 F274 6961 7712 2FD7 7710 2FDD 8180 E933 F274 6961 7711 2643 1080 F587 8180 7711 2640 E966 F274 6961 7712 2FDA 1080 F587 8180 7711 2641 E966 F274 6961 7712 2FDA 1080 F587 8180 10F8 053C 60F8 0008 0004 F820 6753 F210 000E F843 676A F074 697F 76F8 2615 0000 F274 6987 7712 2FD7 F073 676A
 *
 * Intent: Cell(DP 0x0B) == 64 tail-enters dark FRAG_6717 (bc tc, forward
 * extern void + return; numerically inside the 670D-6752 bound but a
 * separate span, same pattern as 3652; rejoin-vs-tail unproven, noted).
 * != 128 tail-enters FRAG_676A (bc ntc, C-less .asm, void per 6666
 * precedent). Else four SUB_6961 passes (calld, C: sub_6961(b_in, par0,
 * par1, par2, b_out); calld delay-slot AR2 presets are callee-visible
 * pre-branch state per 836D): AR1 = 9794/9795/9792/9793, B = 51/51/102/102,
 * AR2 = 12247/12247(delay)/12250/12250, AR0 = AR0-entry then 12253. After
 * each of the first three passes B-out is stored to *AR0, A reloaded, B =
 * min(A,B) (min b, signed 40-bit per 6657/op_compare precedent), stored
 * back. Then A = cell 0x53C; cell(DP 8) != 4 runs FRAG_6753 with B-live
 * (bc ntc; C: frag_6753(b_live)). Else A = B - 14 (sub #14,b,a); A < 0
 * tail-enters FRAG_676A (bc alt, ALT = A < 0 per 5E7D/6657/6693). Else runs
 * DARAM save/restore 0x697F (call, C: daram_save_restore), cell 0x2615 = 0
 * (st), runs 0x6987 with AR2 = 12247 (calld, C: daram_cell_store(src);
 * delay-slot preset callee-visible) and tail-enters FRAG_676A (b). AR0
 * entry-live (first pass *AR0 read); A/B internal. Bound 670D-6752 (exit
 * F073@6751->676A + operand 6752).
 */
extern void frag_6717(void); /* joins 670d_frag_670d interior @+0xA; see docs/evidence/extern-triage.md */
extern void frag_676A(void); /* joins 676a_branch_tail_676a; see docs/evidence/extern-triage.md */
extern void frag_6753(int b_live);
extern int sub_6961(int b_in, int *par0, int *par1, int *par2, int *b_out);
extern void daram_save_restore(void);
extern void daram_cell_store(int *src);

void frag_670D(int *par0)
{
    volatile int *ar0 = (volatile int *)12253;
    long a;
    long b;
    int bout;

    if (*(volatile int *)0xB == 64) {               /* cmpm; bc 6717,tc */
        frag_6717();
        return;
    }
    if (*(volatile int *)0xB != 128) {              /* cmpm; bc 676a,ntc */
        frag_676A();
        return;
    }
    /* stm #9794,ar1; ld #51,b; calld (delay AR2 = 12247) */
    sub_6961(51, par0, (int *)9794, (int *)12247, &bout);
    /* stm #12253,ar0 (AR0 pinned for the remaining passes) */
    *ar0 = bout;                                     /* stl b,*ar0 */
    /* ld #51,b; calld (delay AR1 = 9795) */
    sub_6961(51, (int *)12253, (int *)9795, (int *)12247, &bout);
    a = (long)*ar0;                                  /* ld *ar0,a */
    b = (a < (long)bout) ? a : (long)bout;           /* min b */
    *ar0 = (int)b;                                   /* stl b,*ar0 */
    /* stm #9792,ar1; ld #102,b; calld (delay AR2 = 12250) */
    sub_6961(102, (int *)12253, (int *)9792, (int *)12250, &bout);
    a = (long)*ar0;
    b = (a < (long)bout) ? a : (long)bout;           /* min b */
    *ar0 = (int)b;
    /* stm #9793,ar1; ld #102,b; calld (delay AR2 = 12250) */
    sub_6961(102, (int *)12253, (int *)9793, (int *)12250, &bout);
    a = (long)*ar0;
    b = (a < (long)bout) ? a : (long)bout;           /* min b */
    *ar0 = (int)b;
    a = (long)*(volatile int *)0x53C;                /* ld *(0x53c),a */
    if (*(volatile int *)0x8 != 4) {                 /* cmpm; bc 6753,ntc */
        frag_6753((int)b);
        return;
    }
    a = b - 14L;                                     /* sub #14,b,a */
    if (a < 0) {                                     /* bc 0x676a,alt */
        frag_676A();
        return;
    }
    daram_save_restore();                            /* call 0x697f */
    *(volatile int *)0x2615 = 0;                     /* st #0,*(0x2615) */
    /* calld 0x6987 (delay AR2 = 12247, callee-visible) */
    daram_cell_store((int *)12247);
    /* stm #12247,ar2 (dead post-tail preset, not modeled) */
    frag_676A();                                     /* b 0x676a tail */
}
