/* ROM6 0x89F4 ROUTINE_89F4 -- 20w.
 * Verified encoding: src/rom6/kernel/89f4_routine_89f4.asm (recombine MATCH).
 * ORIGIN 0x89F4
 * EXPECT: 1181 FA4A 89FB 6291 07FD F060 07FD 6381 07FD 8181 3C89 F000 0001 8091 F0EC F468 F478 FE00 F574 8389
 *
 * Intent: Scaled round-trip with delayed exits. B = *AR1-live-in; bcd delay slots always run (A = *AR1++ times 2045 per MPY Smem,#lk, ti-c54x op_mpy_smem_lk; A += 2045 << 16 per ADD #lk,16, ti-c54x op_add_lk_16). B >= 0 tail-enters dark 0x89FB (bcd bgeq, forward extern). Else B = *AR1 times 2045 stored back; A += *AR1-- << 16 (SXM-on-entry unknown, sign-extend assumed per 71d8) plus 1, stored to *AR1++; A <<= 12 logical (sftl) <<= 8 (sfta) >>= 8 arithmetic; retd delay slots always run (B = A >> 12 arithmetic; high word to *AR1-- per ti-c54x op_sth); return. AR1 modeled in-out. Bound 89F4-8A07.
 */
extern void frag_89FB(void);

void routine_89F4(int **ppar1)
{
    long a;
    long b;
    int b0;
    int *ar1 = *ppar1;
    b0 = *ar1;                                   /* ld *ar1,b */
    /* bcd delay slots (always run): */
    a = (long)(*ar1++) * 2045;                  /* mpy *ar1+,#2045,a */
    a += (long)2045 << 16;                      /* add #2045,16,a */
    if (b0 >= 0) {                               /* bcd 0x89fb,bgeq */
        *ppar1 = ar1;
        frag_89FB();                             /* away, dark */
        return;
    }
    b = (long)(*ar1) * 2045;                    /* mpy *ar1,#2045,b */
    *ar1 = (int)b;                               /* stl b,*ar1 */
    a += (long)(*ar1--) << 16;                  /* add *ar1-,16,a */
    a += 1;                                      /* add #1,a */
    *ar1++ = (int)a;                            /* stl a,*ar1+ */
    a <<= 12;                                    /* sftl a,12 (logical) */
    a <<= 8;                                     /* sfta a,8 */
    a >>= 8;                                     /* sfta a,-8 (arithmetic) */
    /* retd delay slots (always run): */
    b = a >> 12;                                /* sfta a,-12,b */
    *ar1 = (int)((b >> 16) & 0xFFFF);           /* sth b,*ar1- */
    ar1--;
    *ppar1 = ar1;
    /* retd */
}
