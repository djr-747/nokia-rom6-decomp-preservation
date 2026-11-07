/* ROM6 0x5B9E FRAG_5B9E -- 59w flag gate + mod-4 dispatch, three entries.
 * Verified encoding: src/rom6/kernel/5b9e_frag_5b9e.asm (recombine MATCH).
 * ORIGIN 0x5B9E
 * EXPECT: F7B9 3CF8 01D3 82F8 2621 F6B9 76F8 2622 0000 7711 2B1C FA42 5B68 7710 2B55 76F8 2EF5 0001 F073 5B68 7310 264C 76F8 09C6 0000 10F8 2EFF F845 5BC6 60F8 2F02 00C0 F820 5BC6 76F8 09C6 0001 76F8 2EFF 0000 E801 00F8 264D F030 0003 80F8 264D F7BE 30F8 2620 20F8 2F02 FC45 E800 80F8 2F02 80F8 2620 FC00
 *
 * Intent: No-static-xref head (computed/dark entry, HYPOTHESIS -- reached
 * linearly only past FRAG_5B5C's always-taken bd, so entry is external or
 * computed). FRAG_5B9E: OVM = 1 (hardware); A = A-live-in +
 * (*(0x1D3) << 16) (ADD Smem,16: SXM-widened << 16); *(0x2621) = A-high;
 * OVM = 0; *(0x2622) = 0; AR1 = 11036; delayed branch-if-A>=0 to
 * FRAG_5B68 (bcd 0x5b68,ageq; delay stm #11093,ar0 always runs: AR0 = 11093
 * on both arms); negative falls to st #1,*(0x2EF5) then b to FRAG_5B68.
 * So: A >= 0 tail-enters the 5B68 twin with AR0 = 11093, else sets the
 * 0x2EF5 flag first (same twin, AR0 = 11093 from the bcd delay).
 * FRAG_5BB2 (all cascade exits from the FRAG_5B68 twin): *(0x264C) = AR0
 * (mvmd; 11093 on every path -- the twin's popm restores the pushed AR1);
 * *(0x9C6) = 0; *(0x2EFF) == 0 exits to FRAG_5BC6 (bc aeq); else
 * *(0x2F02) != 192 exits to FRAG_5BC6 (cmpm + bc ntc); else *(0x9C6) = 1,
 * *(0x2EFF) = 0, falls into 5BC6. FRAG_5BC6: cell 0x264D = (cell + 1) & 3
 * (mod-4 counter: ld/add/and/stl); CPL = 1 (hardware); T = *(0x2620);
 * A = T * *(0x2F02) (MPY Smem: signed T-register times Smem into A per
 * op_mpy_smem); A == 0 returns (rc aeq) leaving both cells set, else
 * clears *(0x2F02) and *(0x2620) and returns (RET @5BD8).
 * Bound 5B9E-5BD8.
 */
extern void frag_5B68(int ar0_live, int ar1_live);

void frag_5BC6(void)
{
    long a;
    int t;

    a = 1L + (long)*(volatile int *)0x264D;              /* ld; add */
    a &= 3;                                              /* and #3,a */
    *(volatile int *)0x264D = (int)(a & 0xFFFF);         /* stl */
    /* ssbx st1,cpl (hardware, no C form) */
    t = *(volatile int *)0x2620;                         /* ld t */
    a = (long)t * (long)*(volatile int *)0x2F02;        /* mpy */
    if (a == 0)                                          /* rc aeq */
        return;
    *(volatile int *)0x2F02 = 0;                         /* stl */
    *(volatile int *)0x2620 = 0;                         /* stl */
    /* ret @5BD8 */
}

void frag_5BB2(int ar0_live)
{
    *(volatile int *)0x264C = ar0_live;           /* mvmd ar0,0x264c */
    *(volatile int *)0x9C6 = 0;                          /* st #0 */
    if (*(volatile int *)0x2EFF == 0) {                  /* ld; bc aeq */
        frag_5BC6();
        return;
    }
    if (*(volatile int *)0x2F02 != 192) {                /* cmpm; bc ntc */
        frag_5BC6();
        return;
    }
    *(volatile int *)0x9C6 = 1;                          /* st #1 */
    *(volatile int *)0x2EFF = 0;                         /* st #0 */
    frag_5BC6();                                    /* fall into 5BC6 */
}

void frag_5B9E(long a_live)
{
    long a = a_live + ((long)*(volatile int *)0x1D3 << 16); /* add,16 */
    int ar0 = 11093;                       /* bcd delay stm (always) */

    /* ssbx st1,ovm (hardware, no C form) */
    *(volatile int *)0x2621 = (int)((a >> 16) & 0xFFFF); /* sth */
    /* rsbx st1,ovm (hardware, no C form) */
    *(volatile int *)0x2622 = 0;                         /* st #0 */
    /* stm #11036,ar1 */
    if (a >= 0) {                                     /* bcd 0x5b68,ageq */
        frag_5B68(ar0, 11036);
        return;
    }
    *(volatile int *)0x2EF5 = 1;                         /* st #1 */
    frag_5B68(ar0, 11036);                                /* b 0x5b68 */
}
