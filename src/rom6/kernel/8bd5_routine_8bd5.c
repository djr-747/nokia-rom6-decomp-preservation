/* ROM6 0x8BD5 ROUTINE_8BD5 -- 9w.
 * Verified encoding: src/rom6/kernel/8bd5_routine_8bd5.asm (recombine MATCH).
 * ORIGIN 0x8BD5
 * EXPECT: E800 771A 008B F272 8BDC 7712 1000 8092 FC00
 *
 * Intent: Window-fill loop. A = 0; BRC = 139; RPTBD repeats the
 * single-word block at 0x8BDC 140 times (BRC + 1 per the 5a68/4ebc
 * RPTB precedent): AR2 = 0x1000 (rptbd delay slot stm, runs once per
 * the delayed form), *(AR2++) = A-low each pass (stl, a_live & 0xFFFF
 * per the 397b precedent); return. RPTBD shape per the vendored TI
 * SPRU172C 4-147--4-148 note in ti-c54x opcode_catalog.def (Z = 1
 * delayed form: RSA = PC + 4 = 0x8BDC = REA; delay words run once);
 * RPTBD execution stays deferred in the ti-c54x core (flagged).
 * AR2 live-out (0x1096) dropped at return (flagged); A-low only,
 * 40-bit guard bits unmodeled (flagged). Bound 8BD5-8BDD.
 */
void routine_8BD5(int a_live)
{
    int *ar2;
    int i;
    ar2 = (int *)4096;                               /* rptbd delay: stm #4096,ar2 */
    for (i = 0; i < 140; i++)                        /* stm #139,brc; rptbd 0x8bdc */
        *ar2++ = a_live;                             /* stl a,*ar2+ */
    /* ret */
}
