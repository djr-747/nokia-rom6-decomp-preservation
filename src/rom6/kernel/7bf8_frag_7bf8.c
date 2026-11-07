/* ROM6 0x7BF8 FRAG_7BF8 -- 11w.
 * Verified encoding: src/rom6/kernel/7bf8_frag_7bf8.asm (recombine MATCH).
 * ORIGIN 0x7BF8
 * EXPECT: F486 F120 03FF F487 8081 7712 2619 E800 EC03 8092 FC00
 *
 * Intent: Clamp plus zero-fill. A = max(A,B) then A = min(A,1023) (MAX/MIN signed 40-bit select per ti-c54x op_compare, A/B live-in, C-bit write unused); store A-low through live-in AR1; AR2 = 9753; A = 0 with 4 stores (rpt #3); return A (0).
 */
int frag_7BF8(int a_live, int b_live, int *par1)
{
    int a = (a_live >= b_live) ? a_live : b_live; /* max a */
    if (a > 1023) a = 1023;                      /* ld #1023,b; min a */
    *par1 = a;                                   /* stl a,*ar1 */
    {
        int i;
        int *ar2 = (int *)9753;                  /* stm #9753,ar2 */
        for (i = 0; i < 4; i++)                  /* ld #0,a; rpt #3 */
            *ar2++ = 0;                          /* stl a,*ar2+ */
    }
    return 0;                                    /* ret (A = 0) */
}
