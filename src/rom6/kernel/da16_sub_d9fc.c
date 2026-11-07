/* ROM6 0xDA16 SUB_D9FC -- 2w repeat high-fill, one EXPECT.
 * Verified encoding: src/rom6/kernel/da16_sub_d9fc.asm (recombine MATCH).
 * ORIGIN 0xDA16
 * EXPECT: EC1B 8292
 *
 * Intent: 28 x *(AR2++) = A-high (rpt #27 + sth a,*ar2+; RPT #k runs
 * k + 1). A and AR2 ride in from entry (A unchanged). Called via calld
 * @D9BF (per header); the span is the RETD @DA15 delay pair.
 * Bound DA16-DA17.
 */
void sub_D9FC(long a_live, int *par2)
{
    int hi = (int)((a_live >> 16) & 0xFFFF);         /* sth a */
    int k;

    for (k = 0; k < 28; k++)                         /* rpt #27 */
        *par2++ = hi;                                /* sth a,*ar2+ */
}
