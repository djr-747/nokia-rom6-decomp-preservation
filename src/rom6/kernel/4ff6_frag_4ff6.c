/* ROM6 0x4FF6 FRAG_4FF6 -- 21w.
 * Verified encoding: src/rom6/kernel/4ff6_frag_4ff6.asm (recombine MATCH).
 * ORIGIN 0x4FF6
 * EXPECT: F074 059C 60F8 250F 0022 F820 5002 61F8 3ACA 0010 F830 500B 61F8 051C 0003 F830 5052 F273 1000 10F8 2F1F
 *
 * Intent: Triple-flag chain with delayed away-branch. Runs 0x59C (dark, forward extern); cell 0x250F != 34 jumps away to dark 0x5002 (bc ntc). Bit 4 of cell 0x3ACA set runs FRAG_500B (bc tc: has .asm, no C yet, forward extern; tail position). Bit 0-1 of cell 0x51C set jumps away to dark 0x5052 (bc tc). Else A = cell 0x2F1F in the bd delay slot (always runs, dead after, noted); branch to dark 0x1000 (bd, forward extern). BITF any-bit TC per op_bitf. Bound 4FF6-500A.
 */
extern void sub_059C(void);
extern void frag_5002(void);
extern void frag_500B(void);
extern void frag_5052(void);
extern void frag_1000(void);

void frag_4FF6(void)
{
    sub_059C();                                  /* call 0x59c */
    if (*(volatile int *)0x250F != 34) {         /* cmpm, bc ntc */
        frag_5002();                             /* away, dark */
        return;
    }
    if ((*(volatile int *)0x3ACA & 16) != 0) {   /* bitf, bc tc */
        frag_500B();                             /* tail, unbound C */
        return;
    }
    if ((*(volatile int *)0x51C & 3) != 0) {     /* bitf, bc tc */
        frag_5052();                             /* away, dark */
        return;
    }
    /* ld *(0x2f1f),a (bd delay: always runs, dead) */
    frag_1000();                                 /* bd 0x1000 */
}
