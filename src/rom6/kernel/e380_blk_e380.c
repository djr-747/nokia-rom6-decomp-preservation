/* ROM6 0xE380 BLK_E380 -- 11w.
 * Verified encoding: src/rom6/kernel/e380_blk_e380.asm (recombine MATCH).
 * ORIGIN 0xE380
 * EXPECT: 8A12 7711 1100 EC0A 7092 0C57 F071 0003 8091 FC00
 *
 * Intent: Restore plus fill pair. AR2 = restored (popm ar2, modeled as saved-value param); AR1 = 4352; 11 copies (rpt #10) of cell 0xC57 through AR2 (mvkd); A = 0 with 4 stores (rptz a,#3) through AR1, return.
 */
void blk_E380(int *ar2_saved)
{
    int i;
    int *ar2 = ar2_saved;                        /* popm ar2 */
    int *ar1 = (int *)4352;                      /* stm #4352,ar1 */
    for (i = 0; i < 11; i++)                     /* rpt #10 */
        *ar2++ = *(volatile int *)0xC57;     /* mvkd 0xc57,*ar2+ */
    for (i = 0; i < 4; i++)                      /* rptz a,#3 */
        *ar1++ = 0;                              /* stl a,*ar1+ */
    /* ret */
}
