/* ROM6 0xC7A4 C7A4_ZERO_FILL_SUB -- 13w.
 * Verified encoding: src/rom6/kernel/c7a4_c7a4_zero_fill_sub.asm (recombine MATCH).
 * ORIGIN 0xC7A4
 * EXPECT: F074 0694 7712 2899 F071 0017 8092 7712 28B1 EC1E 7092 B609 FC00
 *
 * Intent: Zero-fill plus table copy. Runs 0x694; A = 0 with 24 stores (rptz a,#23) from AR2 = 10393; then 31 copies (rpt #30) of cell 0xB609 through AR2 = 10417 (mvkd), return.
 */
extern void sub_0694(void);

void c7a4_zero_fill_sub(void)
{
    int i;
    int *ar2;
    sub_0694();                                  /* call 0x694 */
    ar2 = (int *)10393;                          /* stm #10393,ar2 */
    for (i = 0; i < 24; i++)                     /* rptz a,#23 */
        *ar2++ = 0;                              /* stl a,*ar2+ */
    ar2 = (int *)10417;                          /* stm #10417,ar2 */
    for (i = 0; i < 31; i++)                     /* rpt #30 */
        *ar2++ = *(volatile int *)0xB609;     /* mvkd 0xb609,*ar2+ */
    /* ret */
}
