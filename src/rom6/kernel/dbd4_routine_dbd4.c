/* ROM6 0xDBD4 ROUTINE_DBD4 -- 6w.
 * Verified encoding: src/rom6/kernel/dbd4_routine_dbd4.asm (recombine MATCH).
 * ORIGIN 0xDBD4
 * EXPECT: 770E 0470 F58C EC1B 2992 FC00
 *
 * Intent: MAC dot-product loop. T = 1136; B = T times A-high (MPYA dst overwrites B per ti-c54x op_mpya_dst, A live-in); 28 MAC steps (rpt #27) add T times *AR2++ (live-in pointer); returns B-low.
 */
long routine_DBD4(int a_live, int *par2)
{
    long b = (long)1136 * (a_live >> 16);        /* stm t; mpya b */
    int i;
    for (i = 0; i < 28; i++)                     /* rpt #27 */
        b += (long)1136 * *par2++;               /* mac *ar2+,b */
    return (int)b;                               /* ret */
}
