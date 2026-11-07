/* ROM6 0x687F SUB14_687F -- 14w range flag (6871 twin).
 * Verified encoding: src/rom6/kernel/687f_sub14_687f.asm (recombine MATCH).
 * ORIGIN 0x687F
 * EXPECT: E900 10F8 2FD9 F010 009F F843 688C 0886 F010 0003 F846 688C E901 FC00
 *
 * Intent: Range flag 14b, same shape as SUB14_6871 (C: sub14_6871) with
 * cell 0x2FD9 and constant 159. B = 0; A = cell 0x2FD9 - 159, negative
 * returns 0 (bc 0x688c,alt; ALT = A < 0 per 5E7D/6657/6693). A -= *AR6
 * (live-in; sub Smem sign-extends under SXM = 1 per op_sub_smem.c),
 * A -= 3, positive returns 0 (bc 0x688c,agt; AGT = A > 0 per 6871/6666).
 * Else B = 1 (ld #1,b), return. Both arms land on the ret at 0x688C,
 * which closes this span (the 0x688C ret word belongs here; the 0x688D
 * routine is a separate span). Abuts SUB14_6871 at 0x687E with zero
 * overlap. Bound 687F-688C (ret FC00@688C).
 */
int sub14_687F(int *par6)
{
    int a = *(volatile int *)0x2FD9 - 159;        /* ld, sub #159,a */

    if (a < 0)                                   /* bc 0x688c,alt */
        return 0;
    a -= *par6;                                 /* sub *ar6,a */
    a -= 3;                                      /* sub #3,a */
    if (a > 0)                                   /* bc 0x688c,agt */
        return 0;
    return 1;                                    /* ld #1,b; ret (B-out) */
}
