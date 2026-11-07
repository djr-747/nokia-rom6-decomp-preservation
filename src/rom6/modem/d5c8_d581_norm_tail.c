/* ROM6 0xD5C8 D581_NORM_TAIL -- 2w.
 * Verified encoding: src/rom6/modem/d5c8_d581_norm_tail.asm (recombine MATCH).
 * ORIGIN 0xD5C8
 * EXPECT: 7182 0B58
 *
 * Intent: Tail store with fall-through. Moves *AR2-live-in (fixed, no step) to cell 0xB58 (mvdk); no exit in span, falls into the 0xD5CA head. 2w per .asm header (Bound D5C8-D5C9, executed delay slots of the 0xD5C7 retd; recombine MATCH).
 */
void frag_D5C8(int *par2)
{
    *(volatile int *)0xB58 = *par2;          /* mvdk *ar2,0xb58 */
    /* falls through (no exit in span) */
}
