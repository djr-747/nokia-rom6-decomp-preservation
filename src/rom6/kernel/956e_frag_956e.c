/* ROM6 0x956E FRAG_956E -- 35w counter gate lane.
 * Verified encoding: src/rom6/kernel/956e_frag_956e.asm (recombine MATCH).
 * ORIGIN 0x956E
 * EXPECT: 13F8 20FA F310 0002 76F8 20FA 0000 F84B 9591 E800 11F8 21FA 81F8 21FB 6182 0080 FA30 958B 80F8 20FD 61F8 20FF 0040 4913 F3E8 FD30 8913 FD20 E802 6182 0600 F830 959D F073 95A2
 *
 * Intent: Countdown gate with a TC-shaped middle and three
 * exits. B = cell 0x20FA zero-extended (LDU); B -= 2;
 * cell 0x20FA = 0; B < 0 exits to the 9591 span head (BC
 * BLT -- C entry frag_9591 with AR2/AR4 dark, branch
 * transfer, modeled terminal). Else A = 0; B = cell
 * 0x21FA; cell 0x21FB = BL; TC128 = bit7 of *AR2.
 * BCD delays run always (cell 0x20FD = AL = 0; TC64 =
 * bit6 of cell 0x20FF); TC128 set branches to the 958B
 * join, else fall through: B = AR3 (LDM, SXM-dark,
 * flagged); B <<= 8 logical; XC TC64 stores BL to AR3
 * when set; XC NTC sets A = 2 when clear; join at 958B.
 * At 958B: TC1536 = bits 10-11 of *AR2 (BITF 1536); TC
 * set transfers mid-span to 959D (past the frag_9591 C
 * head -- asm-owned join, provisional extern, transfer);
 * else tail-branch to the 95A2 span (asm-owned head, C
 * file Pool -- provisional join extern, transfer). Entry
 * F844@9559 (BC into head) per asm header. In AR2 (dark,
 * flagged); out cells/AR3.
 * (Wave-13: EXPECT from the image; BCD delays execute on
 * both paths; TC64 from the delay BITF feeds the XC pair.)
 */
extern void frag_9591(int *par2, int *par4);
extern void frag_959D(void); /* joins 9591 span at 959D (past the C head), asm-verified, no C entry yet */
extern void frag_95A2(void); /* joins 95A2 span (asm-owned head), no C entry yet */

void frag_956E(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* (dark, flagged) */
    int *ar4;  /* handoff to frag_9591 (dark, flagged) */
    int tc;

    b = (long)(unsigned)*(volatile int *)0x20FA;               /* ldu *(0x20fa),b */
    b -= 2;                                                    /* sub #2,b */
    *(volatile int *)0x20FA = 0;                               /* st #0,*(0x20fa) */
    if (b < 0) {                                               /* bc 0x9591,blt */
        frag_9591(ar2, ar4);                                   /* (branch transfer, not a call) */
        return;
    }
    a = 0;                                                     /* ld #0,a */
    b = (long)*(volatile int *)0x21FA;                         /* ld *(0x21fa),b (SXM-dark, flagged) */
    *(volatile int *)0x21FB = (int)(b & 0xFFFFL);             /* stl b,*(0x21fb) */
    tc = ((*ar2 & 128) != 0);                                  /* bitf *ar2,#128 */
    /* bcd 0x958b,tc (condition = TC128 at issue; delays below run always): */
    { int tc128 = tc;
    *(volatile int *)0x20FD = (int)(a & 0xFFFFL);             /* stl a,*(0x20fd) */
    tc = ((*(volatile int *)0x20FF & 64) != 0);                /* bitf *(0x20ff),#64 */
    if (tc128)                                                 /* (taken: skip to 958B join) */
        goto l958b; }
    b = (long)ar3;                                             /* ldm ar3,b (SXM-dark, flagged) */
    b = (long)(((unsigned long)b << 8) & 0xFFFFFFFFL);         /* sftl b,8 (logical) */
    if (tc)                                                    /* xc 1,tc */
        ar3 = (int)(b & 0xFFFFL);                              /* stlm b,ar3 */
    if (!tc)                                                   /* xc 1,ntc */
        a = 2;                                                 /* ld #2,a */
l958b:
    tc = ((*ar2 & 1536) != 0);                                 /* bitf *ar2,#1536 (958B join) */
    if (tc) {                                                  /* bc 0x959d,tc */
        frag_959D();                                           /* (branch transfer, not a call) */
        return;
    }
    frag_95A2();                                               /* b 0x95a2 (tail transfer, not a call) */
    /* (transfer, no return) */
}
