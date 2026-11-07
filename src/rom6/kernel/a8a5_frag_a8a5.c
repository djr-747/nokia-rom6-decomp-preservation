/* ROM6 0xA8A5 FRAG_A8A5 -- 12w.
 * Verified encoding: src/rom6/kernel/a8a5_frag_a8a5.asm (recombine MATCH).
 * ORIGIN 0xA8A5
 * EXPECT: 10F8 3082 1AF8 2EF7 F844 A8B9 6FF8 3083 0C5F F845 A8B9 FC00
 *
 * Intent: OR-measure plus shift test. A = cell 0x3082 OR cell 0x2EF7; nonzero tail-calls FRAG_A8B9 (bc aneq); else A = cell 0x3083 halved (ld shift -1), zero tail-calls FRAG_A8B9 (bc aeq), else returns. Mid-entry from FRAG_A89B.
 */
extern void frag_a8b9_zero(void);

void frag_A8A5(void)
{
    int a = *(volatile int *)0x3082 |
              *(volatile int *)0x2EF7;         /* ld, or */
    if (a != 0) {                                /* bc 0xa8b9,aneq */
        frag_a8b9_zero();                        /* tail call */
        return;
    }
    a = *(volatile int *)0x3083 >> 1;        /* ld shift -1 */
    if (a == 0) {                                /* bc 0xa8b9,aeq */
        frag_a8b9_zero();                        /* tail call */
        return;
    }
    /* ret */
}
