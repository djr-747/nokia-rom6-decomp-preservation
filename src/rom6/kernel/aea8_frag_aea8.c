/* ROM6 0xAEA8 FRAG_AEA8 -- 4w.
 * Verified encoding: src/rom6/kernel/aea8_frag_aea8.asm (recombine MATCH).
 * ORIGIN 0xAEA8
 * EXPECT: 7713 3EFA E598 E598
 *
 * Intent: copy 2 cells from 16122 onward to the caller pointer
 * (stm + mvdd *ar3+,*ar2+ twice). Caller passes destination in AR2.
 */
void frag_aea8_copy2(int *dst)
{
    int *src = (int *)16122;              /* stm #16122,ar3 */
    *dst++ = *src++;                      /* mvdd *ar3+,*ar2+ */
    *dst++ = *src++;                      /* mvdd *ar3+,*ar2+ */
}
