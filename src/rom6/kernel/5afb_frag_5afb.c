/* ROM6 0x5AFB FRAG_5AFB -- 29w re-bias tail, two entries, one EXPECT.
 * Verified encoding: src/rom6/kernel/5afb_frag_5afb.asm (recombine MATCH).
 * ORIGIN 0x5AFB
 * EXPECT: F010 2B1C F030 FFFF F010 0273 F842 5B05 F000 0273 60F8 250F 0022 F820 5B0E 00F8 352C F073 5B10 F000 2B1C 8813 6C8E 5AD4 E90C 890E 6C89 5AD2 FC00
 *
 * Intent: Middle/outer loop-close with modulo-627 fold and re-bias.
 * Entries: FRAG_5AFB (from SEG_5AC8 bc ntc: A -= 11036, falls into 5AFD),
 * FRAG_5AFD (from SEG_5AC8 b: A live). Body: A &= 0xFFFF (and #-1,a:
 * AND-immediate zero-extends lk16 per op_logical_immediate, so this
 * clears A-high, not a no-op). A -= 627; negative restores A += 627
 * (bc 0x5b05,ageq skips the add-back): single-subtract modulo 627.
 * id 0x250F != 34 adds 11036 (bc ntc to 5B0E) else adds *(0x352C)
 * (sub/add Smem SXM-sign-extended per op_add_smem; SXM = 1 assumed,
 * flagged) -- mirror of the SEG_5AC8 head bias. AR3 = A-low (stlm).
 * BANZ test-then-decrements per op_branch_sind_common (taken = (AR != 0),
 * writeback AR - 1): AR6 != 0 re-enters FRAG_5AD4 with the threaded
 * resume state (banz 0x5ad4; AR6 = 3 gives four inner passes: taken on
 * 3, 2, 1). Else B = T = 12 (ld #16.. seeds the next pass: the 5AD4
 * back-edge opens with one T = 12 nibble per SEG_5AC8 notes) and
 * AR1 != 0 re-enters FRAG_5AD2 (banz 0x5ad2; AR1 = 1 gives one outer
 * repeat: two middle runs of four passes total), else RET @5B17.
 * Bound 5AFB-5B17.
 */
extern void frag_5AD4(int *par2, int ar3, int ar5, int ar0, long b_live,
                      int t_live, int ar6, int ar1);
extern void frag_5AD2(int *par2, int ar3, int ar5, int ar0, long b_live,
                      int t_live, int ar1);

void frag_5AFD(long a_live, int *par2, int ar3, int ar5, int ar0,
               long b_live, int t_live, int ar6, int ar1)
{
    long a = a_live & 0xFFFFL;                   /* and #-1,a (hi clr) */
    long b = b_live;
    int t = t_live;
    int take;

    a -= 627;                                    /* sub #627,a */
    if (a < 0)                                   /* bc 0x5b05,ageq */
        a += 627;                                /* add #627,a */
    if (*(volatile int *)0x250F != 34)           /* cmpm; bc ntc */
        a += 11036;                              /* add #11036,a */
    else
        a += (long)*(volatile int *)0x352C;      /* add *(0x352c),a */
    ar3 = (int)(a & 0xFFFF);                     /* stlm a,ar3 */
    take = (ar6 != 0);                           /* banz test-then-dec */
    ar6 = (ar6 - 1) & 0xFFFF;
    if (take) {                                  /* banz 0x5ad4 */
        frag_5AD4(par2, ar3, ar5, ar0, b, t, ar6, ar1);
        return;
    }
    b = 12;                                      /* ld #12,b */
    t = 12;                                      /* stlm b,t (seeds T) */
    take = (ar1 != 0);                           /* banz test-then-dec */
    ar1 = (ar1 - 1) & 0xFFFF;
    if (take) {                                  /* banz 0x5ad2 */
        frag_5AD2(par2, ar3, ar5, ar0, b, t, ar1);
        return;
    }
    /* ret @5B17 */
}

void frag_5AFB(long a_live, int *par2, int ar3, int ar5, int ar0,
               long b_live, int t_live, int ar6, int ar1)
{
    /* sub #11036,a; falls into 5AFD */
    frag_5AFD(a_live - 11036L, par2, ar3, ar5, ar0, b_live, t_live,
              ar6, ar1);
}
