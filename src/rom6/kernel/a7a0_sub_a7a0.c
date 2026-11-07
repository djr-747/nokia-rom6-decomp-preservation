/* ROM6 0xA7A0 SUB_A7A0 -- 23w.
 * Verified encoding: src/rom6/kernel/a7a0_sub_a7a0.asm (recombine MATCH).
 * ORIGIN 0xA7A0
 * EXPECT: 7714 09C8 F274 86FB 7713 3090 7712 2799 EC4B 7092 3090 61F8 051C 0001 FC20 10F8 3082 FC45 E800 EC4B 7308 2799 FC00
 *
 * Intent: Gated copy plus clear. AR4 = 2504, AR3 = 12432 (calld
 * delay; both dead after, noted), AR2 = 10137; runs dark SUB_86FB;
 * 76 copies *(AR2++) = cell0x3090 (rpt #75 + MVKD, 457f precedent);
 * TC = (cell0x51C & 1) != 0 (bitf, 32b4 precedent), clear
 * near-returns (rc ntc); A = cell0x3082, zero near-returns
 * (rc aeq); A = 0; 76 idempotent zeroes to cell0x2799 (rpt #75 +
 * MVMD-AL to a fixed cell: no AR, no stepping, same cell rewritten);
 * return. Bound A7A0-A7B6.
 */
extern void sub_86FB(void);

void sub_A7A0(void)
{
    int *ar2;
    long a;
    int tc;
    int i;
    /* stm #2504,ar4 (dead, noted) */
    /* calld delay: AR3 = 12432 (dead, noted) */
    sub_86FB();                                      /* calld 0x86fb (dark) */
    ar2 = (int *)10137;                              /* stm #10137,ar2 */
    for (i = 0; i < 76; i++)                         /* rpt #75 */
        *ar2++ = *(volatile int *)0x3090;            /* mvdk 0x3090,*ar2+ */
    tc = (*(volatile int *)0x51C & 1) != 0;          /* bitf *(0x51c),#1 */
    if (!tc)                                         /* rc ntc */
        return;
    a = (long)*(volatile int *)0x3082;               /* ld *(0x3082),a */
    if (a == 0)                                      /* rc aeq */
        return;
    a = 0;                                           /* ld #0,a */
    for (i = 0; i < 76; i++)                         /* rpt #75 (same cell) */
        *(volatile int *)0x2799 = (int)(a & 0xFFFF); /* mvmd al,0x2799 */
    /* ret */
}
