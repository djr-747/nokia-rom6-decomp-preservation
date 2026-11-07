/* ROM6 0x388C FRAG_388C -- 16w.
 * Verified encoding: src/rom6/kernel/388c_frag_388c.asm (recombine MATCH).
 * ORIGIN 0x388C
 * EXPECT: F074 062A 61F8 3EC8 0002 F830 3938 61F8 051F 0080 F830 3907 11F8 3E7F F073 38AA
 *
 * Intent: Flag pair with B handoff. Runs 0x62A (dark, forward extern); bit 1 of cell 0x3EC8 set jumps away to FRAG_3938 (bc tc: has .asm, no C yet, forward extern). Bit 7 of cell 0x51F set runs ROUTINE_3907 (bc tc: has .asm, no C yet, forward extern; tail position). Else B = cell 0x3E7F threaded into dark 0x38AA (b, forward extern with B arg). BITF any-bit TC per op_bitf. Bound 388C-389B.
 */
extern void sub_062A(void);
extern void frag_3938(void);
extern void routine_3907(void);
extern void frag_38AA(int b_live);

void frag_388C(void)
{
    int b;
    sub_062A();                                  /* call 0x62a */
    if ((*(volatile int *)0x3EC8 & 2) != 0) {    /* bitf, bc tc */
        frag_3938();                             /* away, unbound C */
        return;
    }
    if ((*(volatile int *)0x51F & 128) != 0) {   /* bitf, bc tc */
        routine_3907();                          /* tail, unbound C */
        return;
    }
    b = *(volatile int *)0x3E7F;             /* ld *(0x3e7f),b */
    frag_38AA(b);                                /* b 0x38aa tail */
}
