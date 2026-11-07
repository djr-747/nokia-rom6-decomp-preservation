/* ROM6 0x36C2 FRAG_36C2 -- 31w.
 * Verified encoding: src/rom6/kernel/36c2_frag_36c2.asm (recombine MATCH).
 * ORIGIN 0x36C2
 * EXPECT: 12D2 60F8 0008 0001 F820 36E1 76F8 058F 0001 71D2 27FE 71D2 27FF 71D2 2940 71D2 2941 71D2 2979 71D2 244F 71D2 2450 F074 2E2F F074 E79D F074 E7EF F073 2E64
 *
 * Intent: Cell-fanout plus call chain. A = unsigned *AR2 with
 * AR2 += AR0-live (ldu +0%, circular wrap needs caller-live BK,
 * linear flagged); cell0x8 != 1 tail-enters FRAG_36E1 (cmpm
 * equality per op_cmpm_smem_lk, 3691 precedent; void); else
 * cell0x58F = 1 and 7 cells (0x27FE/27FF/2940/2941/2979/244F/2450)
 * each take *(AR2++) with AR2 += AR0 per tap (MVKD absolute-dest,
 * 457f precedent; wrap flagged); runs dark SUB_2E2F, dark
 * SUB_E79D, BLK_E7EF (C: blk_E7EF), tail-branches dark 0x2E64.
 * AR2 caller-live, dead after (dark-call liveness flagged).
 * Bound 36C2-36E0.
 */
extern void sub_2E2F(void);
extern void sub_E79D(void);
extern void blk_E7EF(void);
extern void frag_2E64(void);
extern void frag_36E1(void);

void frag_36C2(int *ar2_in, int ar0_live)
{
    int *ar2 = ar2_in;
    long a;
    int tc;
    a = (unsigned long)(unsigned)*ar2;               /* ldu *ar2+%,a */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    tc = (*(volatile int *)0x8 == 1);                /* cmpm *(0x8),#1 */
    if (!tc) {                                       /* bc 0x36e1,ntc */
        frag_36E1();
        return;
    }
    *(volatile int *)0x58F = 1;                      /* st #1,*(0x58f) */
    *(volatile int *)0x27FE = *ar2;                  /* mvdk *ar2+%,0x27fe */
    ar2 += ar0_live;
    *(volatile int *)0x27FF = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x2940 = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x2941 = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x2979 = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x244F = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x2450 = *ar2;
    ar2 += ar0_live;
    sub_2E2F();                                      /* call 0x2e2f (dark) */
    sub_E79D();                                      /* call 0xe79d (dark) */
    blk_E7EF();                                      /* call 0xe7ef */
    frag_2E64();                                     /* b 0x2e64 (dark tail) */
    (void)a;                                         /* A dead after (flagged) */
}
