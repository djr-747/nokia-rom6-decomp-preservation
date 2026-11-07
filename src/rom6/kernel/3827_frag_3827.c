/* ROM6 0x3827 FRAG_3827 -- 7w.
 * Verified encoding: src/rom6/kernel/3827_frag_3827.asm (recombine MATCH).
 * ORIGIN 0x3827
 * EXPECT: 1082 F030 00FF 80F8 054D F073 37DF
 *
 * Intent: Masked store plus join. Cell 0x54D = *AR2-live-in AND 255 (ld plus and); tail-enters 0x37DF (b, forward extern). Bound 3827-382D.
 */
extern void frag_37DF(void); /* joins 37d8_frag_37d8 interior @+0x7; see docs/evidence/extern-triage.md */

void frag_3827(int *par2)
{
    *(volatile int *)0x54D =
        *par2 & 255;                         /* ld; and #255,a; stl */
    frag_37DF();                                 /* b 0x37df tail */
}
