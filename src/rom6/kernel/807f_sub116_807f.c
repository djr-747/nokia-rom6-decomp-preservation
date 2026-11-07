/* ROM6 0x807F SUB116_807F -- 36w call + XOR-mask lane.
 * Verified encoding: src/rom6/kernel/807f_sub116_807f.asm (recombine MATCH).
 * ORIGIN 0x807F
 * EXPECT: F074 059E F274 3A27 E732 E801 F274 3AB6 7712 2F96 7712 2F96 6A92 FFFF 6A92 FFFF 6A92 FFFF 6D8A 448A F063 FF00 138A F2A8 1382 F2B8 6DEB 000D 828B 808B 6883 00FF F768 FE00 1B83 8183
 *
 * Intent: Call pair plus invert-and-merge lane. Call 0x59E
 * (RAM); deferred call 0x3A27 (C entry
 * pa60_57_writer_b(A, AR2) -- AR2 = entry AR3 via MVMM,
 * A = 1 in the delay slots; entry AR3/AR2 dark, flagged)
 * with the return address falling into the deferred call
 * 0x3AB6 (C entry frag_3AB6(AR2) -- AR2 = 12182 from the
 * delay STM, which re-executes idempotently at the return
 * address); then 3x invert of *AR2+ (XORM #65535 --
 * 16-bit cell XOR, no widening issue); AR2--; A =
 * *AR2-- << 16; A &= (-256) << 16 (AND #lk shifted);
 * B = *AR2-- zero-extended (LDU); A |= B << 8; B =
 * *AR2 zero-extended; A |= B >> 8 (B upper-clear, exact);
 * AR3 += 13; store A MSW then AL to *AR3- pair; cell
 * *AR3 &= 255 (ANDM); B <<= 8; return with A |= *AR3 and
 * store of BL in the delay slots. In AR2/AR3 (dark,
 * flagged); out *AR3 pair/cells.
 * (Wave-13: EXPECT from the image; CALLD delay order;
 * XORM/ANDM are 16-bit cell ops.)
 */
extern void sub_059E(void); /* low-region: zero in mask dump; see docs/evidence/extern-triage.md */
extern void pa60_57_writer_b(long a_0632_out, int *ar2_in);
extern void frag_3AB6(int *ar2_in);

void sub116_807F(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int i;

    sub_059E();                                                /* call 0x59e (RAM) */
    ar2 = ar3;                                                 /* calld delay 1: mvmm ar3,ar2 */
    a = 1;                                                     /* calld delay 2: ld #1,a */
    pa60_57_writer_b(a, ar2);                                  /* calld 0x3a27 */
    /* (return address: calld 0x3ab6 below) */
    ar2 = (int *)12182;                                        /* calld delay: stm #12182,ar2 (fills both words) */
    frag_3AB6(ar2);                                            /* calld 0x3ab6 */
    /* (return address: stm #12182,ar2 re-executes, idempotent) */
    for (i = 0; i < 3; i++)                                    /* 3x xorm */
        *ar2++ ^= 0xFFFF;                                      /* xorm #65535,*ar2+ */
    ar2--;                                                     /* mar *ar2- */
    a = (long)*ar2-- << 16;                                    /* ld *ar2-,16,a */
    a &= (long)-256 << 16;                                     /* and #-256,16,a */
    b = (long)(unsigned)*ar2--;                                /* ldu *ar2-,b */
    a |= b << 8;                                               /* or b,8,a */
    b = (long)(unsigned)*ar2;                                  /* ldu *ar2,b */
    a |= b >> 8;                                               /* or b,-8,a (B upper-clear, exact) */
    ar3 += 13;                                                 /* mar *+ar3(0xd) */
    *ar3-- = (int)((a >> 16) & 0xFFFFL);                       /* sth a,*ar3- */
    *ar3-- = (int)(a & 0xFFFFL);                               /* stl a,*ar3- */
    *ar3 &= 255;                                               /* andm #255,*ar3 */
    b <<= 8;                                                   /* sfta b,8 */
    /* retd (delay words run, then return): */
    b |= (long)(*ar3 & 0xFFFF);                                /* or *ar3,b (Smem zero-extended) */
    *ar3 = (int)(b & 0xFFFFL);                                 /* stl b,*ar3 */
    /* retd */
}
