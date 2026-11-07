/* ROM6 0x6954 FRAG_6954 -- 13w.
 * Verified encoding: src/rom6/kernel/6954_frag_6954.asm (recombine MATCH).
 * ORIGIN 0x6954
 * EXPECT: E808 00F8 0564 80F8 0564 F010 0010 FC42 6BF8 0060 0001 F073 692C
 *
 * Intent: Cell bump with early return. A = 8 + cell 0x564 stored back (ld, add, stl); A -= 16, non-negative returns (rc ageq). Else cell 0x60 += 1 (addm), tail-enters FRAG_692C (b 0x692c: has .asm, no C yet, forward extern). Bound 6954-6960.
 */
extern void sub_692C(void);

void frag_6954(void)
{
    int a = 8 + *(volatile int *)0x564;      /* ld; add *(0x564),a */
    *(volatile int *)0x564 = a;              /* stl a,*(0x564) */
    a -= 16;                                     /* sub #16,a */
    if (a >= 0)                                  /* rc ageq */
        return;
    *(volatile int *)0x60 += 1;              /* addm #1,*(0x60) */
    sub_692C();                                 /* b 0x692c tail */
}
