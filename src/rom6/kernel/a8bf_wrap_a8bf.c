/* ROM6 0xA8BF WRAP_A8BF -- 21w.
 * Verified encoding: src/rom6/kernel/a8bf_wrap_a8bf.asm (recombine MATCH).
 * ORIGIN 0xA8BF
 * EXPECT: F074 067C 10F8 2EFD FC45 60F8 2510 00C0 F820 A8CD 60F8 2EF5 0000 FC20 E900 F074 4BA8 76F8 2EFD 0000 FC00
 *
 * Intent: Cell test plus shared tail. Runs 0x67C; A = cell 0x2EFD, zero returns at once (rc aeq: taken return per the op_rc leaf). Else TC = (cell 0x2510 == 192), clear jumps to the tail with B live (bc 0xa8cd,ntc). Else cell 0x2EF5 != 0 returns at once (rc ntc: taken return); else B = 0. Tail: call 0x4BA8 with (A = cell, B); clear cell 0x2EFD; return. CMPM is TC-only per ti-c54x op_cmpm.
 */
extern void sub_067C(void);
extern void sub_4BA8(int a_live, int b_live);

void wrap_A8BF(int b_live)
{
    int tc;
    int b = b_live;
    int a;
    sub_067C();                                  /* call 0x67c */
    a = *(volatile int *)0x2EFD;                 /* ld *(0x2efd),a */
    if (a == 0)                                  /* rc aeq */
        return;
    tc = (*(volatile int *)0x2510 == 192);       /* cmpm */
    if (!tc)                                     /* bc ntc: A8CD tail */
        goto L_TAIL;
    if (*(volatile int *)0x2EF5 != 0)            /* cmpm; rc ntc */
        return;                                  /* taken return */
    b = 0;                                       /* ld #0,b */
L_TAIL:
    sub_4BA8(a, b);                              /* call 0x4ba8 */
    *(volatile int *)0x2EFD = 0;             /* st #0 */
    /* ret */
}
