/* ROM6 0x6871 SUB14_6871 -- 14w.
 * Verified encoding: src/rom6/kernel/6871_sub14_6871.asm (recombine MATCH).
 * ORIGIN 0x6871
 * EXPECT: E900 10F8 2FD7 F010 0002 F843 687E 0886 F010 0003 F846 687E E901 FC00
 *
 * Intent: Range flag 14a. B = 0; A = cell 0x2FD7 - 2, negative returns 0 (bc 0x687e,alt). A -= *AR6 (live-in), A -= 3, positive returns 0 (bc 0x687e,agt). Else B = 1, return. Callers F074 @6497/@6522.
 */
int sub14_6871(int *par6)
{
    int a = *(volatile int *)0x2FD7 - 2;         /* ld, sub #2 */
    if (a < 0)                                   /* bc 0x687e,alt */
        return 0;
    a -= *par6;                                 /* sub *ar6,a */
    a -= 3;                                      /* sub #3,a */
    if (a > 0)                                   /* bc 0x687e,agt */
        return 0;
    return 1;                                    /* ld #1,b; ret */
}
