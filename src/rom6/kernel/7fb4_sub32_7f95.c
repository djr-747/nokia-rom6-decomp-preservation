/* ROM6 0x7FB5 SUB32_7F95 -- 17w.
 * Verified encoding: src/rom6/kernel/7fb4_sub32_7f95.asm (recombine MATCH).
 * ORIGIN 0x7FB5
 * EXPECT: F120 AAAA 771A 0007 F072 7FBD 1082 F280 8092 6D8A FC00 F120 5555 F074 7FB7 E721 FC00
 *
 * Intent: Dual-entry mask lane (two entries, disjoint returns; the 7FB7 loop
 * is shared in ROM, shown per entry here for lane-exact returns). Entry 7FB5
 * (post-unconditional-b head): B = -21846 mask; stm #7,brc; rptb block x8
 * (A = *AR2 & B, store, AR2++); AR2-- (mar); return @7FBF. Entry 7FC0:
 * B = 21845; interior call into the shared 7FB7 loop; on return AR1 = AR2
 * (mvmm); return @7FC5. No exterior calls. AR2 live-in (dark, flagged);
 * AR1 dead after (flagged).
 */
void sub32_7F95(void)
{
    long a;
    long b;
    int *ar1;
    int *ar2;  /* live-in (dark, flagged) */
    int i;

l7fb5:
    b = -21846;                                                /* ld #-21846,b */
    /* stm #7,brc */
    for (i = 0; i < 8; i++) {                                  /* rptb 0x7fbd */
        a = (long)*ar2;                                        /* ld *ar2,a */
        a &= b;                                                /* and b,a */
        *(ar2++) = (int)(a & 0xFFFFL);                         /* stl a,*ar2+ */
    }
    ar2--;                                                     /* mar *ar2- */
    (void)a;
    return;                                                    /* ret @7FBF */
l7fc0:
    b = 21845;                                                 /* ld #21845,b */
    /* stm #7,brc (interior call 0x7fb7 target) */
    for (i = 0; i < 8; i++) {                                  /* rptb 0x7fbd */
        a = (long)*ar2;                                        /* ld *ar2,a */
        a &= b;                                                /* and b,a */
        *(ar2++) = (int)(a & 0xFFFFL);                         /* stl a,*ar2+ */
    }
    ar2--;                                                     /* mar *ar2- */
    ar1 = ar2;                                                 /* mvmm ar2,ar1 */
    (void)ar1;
    /* ret @7FC5 */
}
