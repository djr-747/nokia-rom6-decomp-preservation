/* ROM6 0x500B FRAG_500B -- 80w mode word build with copy tail.
 * Verified encoding: src/rom6/kernel/500b_frag_500b.asm (recombine MATCH).
 * ORIGIN 0x500B
 * EXPECT: F074 059C 61F8 3ACA 0002 F820 502A 10F8 3ACA F030 0700 11F8 3490 F330 0007 F784 F518 F84C 505A 10F8 3ACA F030 00E0 F845 5048 F015 0001 F845 5034 F073 505A 11F8 3490 F230 0007 F845 5048 F230 0001 F845 505A 60F8 34BF 0001 F830 5048 60F8 34BF 0004 F830 5048 7713 2649 6983 0010 7713 34F3 7093 2F1F F073 5056 7713 2648 6983 0010 7713 2579 7093 2F1F F073 5056 7713 25C1 7093 2F1F 7712 2F80 EC12 E589 FC00
 *
 * Intent: Runs dark SUB_059C (call, void per 4EE0/4FF6). Every path either
 * returns (b/bc to 0x505A = ret) or builds one mode word then runs the
 * shared 0x5056 copy tail, so the C selects (orm_cell, dst) and falls
 * through. Bit 1 of cell 0x3ACA clear takes the 0x502A arm (bc ntc): A =
 * cell 0x3490 & 7 (and #7,b,a, B kept); A == 0 selects the 0x5048 build;
 * A = cell & 1; A == 0 returns; else the 0x5034 select: cell 0x34BF == 1
 * or == 4 (cmpm pair, TC-only) selects the 0x5048 build, else the 0x5034
 * build. Else (bit set): A = cell & 1792 (0x700); B = cell 0x3490 & 7;
 * B = -B (neg: 40-bit two's complement, TC preserved per ti-c54x
 * op_neg_acc.c; saturation edge noted, values small); B += A >> 8
 * (add a,-8,b, arithmetic shift); B != 0 returns. A = cell 0x3ACA & 224;
 * A == 0 selects 0x5048; A -= 32 (sub #1,5,a: A -= 1 << 5); A == 0 runs the
 * 0x5034 select; else returns. The 0x5048 build: cell 9800 |= 16 (orm),
 * dst 9593. The 0x5034 build: cell 9801 |= 16, dst 13555. Both store cell
 * 0x2F1F via *AR3++ (mvkd absolute-source load-store). Merge at 0x5056:
 * AR2 = 12160; 19 DARAM moves *AR3++ = *AR2++ (rpt #18 + mvdd); returns.
 * Words 0x5052-5055 (stm 9665 + mvkd) are unreachable -- no in-span ref
 * targets them -- omitted from control flow but covered by EXPECT. A/B
 * internal; AR2/AR3 cursor locals. Bound 500B-505A (ret).
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void frag_500B(void)
{
    long a;
    long b;
    int *par2;
    int *par3;
    int orm_cell;
    int dst;
    int i;

    sub_059C();                                        /* call 0x59c */
    if ((*(volatile int *)0x3ACA & 2) == 0) {          /* bc 0x502a,ntc */
        b = (long)*(volatile int *)0x3490;             /* 0x502a: ld */
        a = b & 7L;                                    /* and #7,b,a */
        if (a == 0) {                                  /* bc 0x5048,aeq */
            orm_cell = 9800; dst = 9593;
        } else {
            a = b & 1L;                                /* and #1,b,a */
            if (a == 0)                                /* bc 0x505a,aeq */
                return;
            if (*(volatile int *)0x34BF == 1 ||        /* 0x5034: cmpm */
                *(volatile int *)0x34BF == 4) {        /* cmpm; bc tc */
                orm_cell = 9800; dst = 9593;
            } else {
                orm_cell = 9801; dst = 13555;
            }
        }
    } else {
        a = (long)*(volatile int *)0x3ACA;             /* ld *(0x3aca),a */
        a &= 1792L;                                    /* and #1792,a */
        b = (long)*(volatile int *)0x3490;             /* ld *(0x3490),b */
        b &= 7L;                                       /* and #7,b */
        b = -b;                                        /* neg b */
        b += a >> 8;                                   /* add a,-8,b */
        if (b != 0)                                    /* bc 0x505a,bneq */
            return;
        a = (long)*(volatile int *)0x3ACA;             /* ld *(0x3aca),a */
        a &= 224L;                                     /* and #224,a */
        if (a == 0) {                                  /* bc 0x5048,aeq */
            orm_cell = 9800; dst = 9593;
        } else {
            a -= 32L;                                  /* sub #1,5,a */
            if (a != 0)                                /* bc 0x5034,aeq */
                return;                                /* b 0x505a */
            if (*(volatile int *)0x34BF == 1 ||        /* 0x5034: cmpm */
                *(volatile int *)0x34BF == 4) {        /* cmpm; bc tc */
                orm_cell = 9800; dst = 9593;
            } else {
                orm_cell = 9801; dst = 13555;
            }
        }
    }
    par3 = (int *)orm_cell;
    *par3 |= 16;                                       /* orm #16,*ar3 */
    par3 = (int *)dst;
    *par3++ = *(volatile int *)0x2F1F;                 /* mvkd 0x2f1f */
    /* 0x5056 merge */
    par2 = (int *)12160;                               /* stm #12160,ar2 */
    for (i = 0; i < 19; i++)                           /* rpt #18 + mvdd */
        *par3++ = *par2++;
    /* ret */
}
