/* ROM6 0xD9C7 SUB_D970 -- 2w repeat high-fill, one EXPECT.
 * Verified encoding: src/rom6/kernel/d9c7_sub_d970.asm (recombine MATCH).
 * ORIGIN 0xD9C7
 * EXPECT: EC27 8293
 *
 * Intent: 40 x *(AR3++) = A-high (rpt #39 + sth a,*ar3+; RPT #k runs
 * k + 1). A and AR3 ride in from entry (A unchanged). Called via F074
 * @5477/@5490 (per header); the span is the RETD @D9C6 delay pair.
 * Bound D9C7-D9C8.
 */
void sub_D970(long a_live, int *par3)
{
    int hi = (int)((a_live >> 16) & 0xFFFF);         /* sth a */
    int k;

    for (k = 0; k < 40; k++)                         /* rpt #39 */
        *par3++ = hi;                                /* sth a,*ar3+ */
}
