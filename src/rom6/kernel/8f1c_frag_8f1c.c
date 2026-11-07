/* ROM6 0x8F1C FRAG_8F1C -- 4w.
 * Verified encoding: src/rom6/kernel/8f1c_frag_8f1c.asm (recombine MATCH).
 * ORIGIN 0x8F1C
 * EXPECT: 7642 FFFC 7643 000F
 *
 * Intent: Direct-store pair with fall-through. Writes -4 to cell 0x42 and 15 to cell 0x43 (st direct pair); no exit in span, execution falls into the 0x8F20 head. Bound 8F1C-8F1F.
 */
void frag_8F1C(void)
{
    *(volatile int *)0x42 = -4;              /* st #-4,0x42 */
    *(volatile int *)0x43 = 15;              /* st #15,0x43 */
    /* falls through (no ret in span) */
}
