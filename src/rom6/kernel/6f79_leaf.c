/* ROM6 0x6F79 LEAF_6F79 -- 15w.
 * Verified encoding: src/rom6/kernel/6f79_leaf.asm (recombine MATCH).
 * ORIGIN 0x6F79
 * EXPECT: F074 05B4 7712 03D9 E880 EC1F 8092 7712 2494 E800 EC1F 8092 EC3F 8092 FC00
 *
 * Intent: helper call, then fixed-pattern DARAM fills: 32 cells of 128
 * at 985, 32 cells of 0 at 9364, 64 more cells of 0 continuing past.
 * Shape is memset-like; the counts (rpt #31 / #63) are exact.
 */
extern void helper_05B4(void);

void leaf_6F79_fill(void)
{
    int i, *p;
    helper_05B4();                         /* call 0x5b4 */
    p = (int *)985;                        /* stm #985,ar2 */
    for (i = 0; i < 32; i++)               /* ld #128,a / rpt #31 */
        *p++ = 128;                        /* stl a,*ar2+ */
    p = (int *)9364;                       /* stm #9364,ar2 */
    for (i = 0; i < 32 + 64; i++)          /* ld #0,a / rpt #31 + #63 */
        *p++ = 0;                          /* stl a,*ar2+ */
}
