/* ROM6 0xD9E1 ROUTINE_D9E1 -- 27w config-table initializer.
 * Verified encoding: src/rom6/kernel/d9e1_routine_d9e1.asm (recombine MATCH).
 * ORIGIN 0xD9E1
 * EXPECT: E907 7712 0A58 8192 7692 7FFF 7692 0003 8392 7692 7081 7692 6958 7712 0A66 771A 0006 F272 D9F8 EC05 8392 EC09 7C92 D9C9 FE00 EC1B 8392
 *
 * Intent: Write the config block at 2648+: B = 7; header
 * words 7, 32767, 3, B-high 0, 28801, 26968; AR2 = 2662;
 * BRC = 6; RPTBD block x7: 6x zero MSW (rpt #5 sth b) then
 * 10x template words from DROM 0xD9C9 (rpt #9 mvpd; Pmad
 * auto-increment under RPT proven by the ROM ramp
 * prog[D9C9..D9D2] = 0568..3585; Pmad re-fetches 0xD9C9 each
 * block pass); return with a 28x zero-MSW tail in the delay
 * slots (rpt #27 sth b). 6 + 7*16 + 28 = 146 words at
 * 2648+. No live entry state; clobbers B/AR2/BRC.
 */
extern int prom_read_word(int prog_addr);          /* mvpd */

void routine_D9E1(void)
{
    long b;
    int *ar2;
    int g;
    int i;

    b = 7;                                                     /* ld #7,b */
    ar2 = (int *)2648;                                         /* stm #2648,ar2 */
    *ar2++ = (int)(b & 0xFFFFL);                               /* stl b,*ar2+ */
    *ar2++ = 32767;                                            /* st #32767,*ar2+ */
    *ar2++ = 3;                                                /* st #3,*ar2+ */
    *ar2++ = (int)((b >> 16) & 0xFFFFL);                       /* sth b,*ar2+ */
    *ar2++ = 28801;                                            /* st #28801,*ar2+ */
    *ar2++ = 26968;                                            /* st #26968,*ar2+ */
    ar2 = (int *)2662;                                         /* stm #2662,ar2 */
    /* stm #6,brc */
    for (g = 0; g < 7; g++) {                                  /* rptbd 0xd9f8 */
        for (i = 0; i < 6; i++)                                /* rpt #5 */
            *ar2++ = (int)((b >> 16) & 0xFFFFL);               /* sth b,*ar2+ */
        for (i = 0; i < 10; i++)                               /* rpt #9 */
            *ar2++ = prom_read_word(0xD9C9 + i);                /* mvpd 0xd9c9,*ar2+ */
    }
    /* retd (delay words run, then return): */
    for (i = 0; i < 28; i++)                                   /* rpt #27 */
        *ar2++ = (int)((b >> 16) & 0xFFFFL);                   /* sth b,*ar2+ */
    /* retd */
}
