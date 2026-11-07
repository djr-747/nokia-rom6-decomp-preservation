/* ROM6 0xDB3E ROUTINE_DB3E -- 12w.
 * Verified encoding: src/rom6/kernel/db3e_routine_db3e.asm (recombine MATCH).
 * ORIGIN 0xDB3E
 * EXPECT: EC3B E576 771A 0009 F272 DB48 770E FFFF 1492 0493 8096 FC00
 *
 * Intent: Block move plus halve-add loop. 60 dual moves *(AR4--) =
 * *(AR5--) (rpt #59 + MVDD, 457f precedent); then 10 passes (BRC = 9,
 * rptb 0xDB48... RPTBD delayed form: RSA = PC + 4 = 0xDB46, REA =
 * 0xDB48, per the vendored TI note in ti-c54x opcode_catalog.def;
 * RPTBD execution stays deferred in the core, flagged) of A =
 * (*AR2++ >> 1) + (*AR3++ >> 1) with T = -1 constant from the delay
 * slot stm (TS right-shift-1, arithmetic per SXM = 1, flagged; the
 * 5a68/5ac8/5c34 precedents model the variable-TS form), stored to
 * *(AR6++) low word (stl, 397b precedent). All ARs caller-live,
 * dead at return (flagged). Bound DB3E-DB49.
 */
void routine_DB3E(int *ar4, int *ar5, int *ar2, int *ar3, int *ar6)
{
    int i;
    long a;
    for (i = 0; i < 60; i++) {                       /* rpt #59 */
        *ar4 = *ar5;                                 /* mvdd *ar5-,*ar4- */
        ar4--;
        ar5--;
    }
    /* delay slot stm #-1,t runs once: T = -1 constant (folded below) */
    for (i = 0; i < 10; i++) {                       /* stm #9,brc; rptbd 0xdb48 */
        a = (long)*ar2++ >> 1;                       /* ld *ar2+,ts,a */
        a += (long)*ar3++ >> 1;                      /* add *ar3+,ts,a */
        *ar6++ = (int)(a & 0xFFFF);                  /* stl a,*ar6+ */
    }
    /* ret */
}
