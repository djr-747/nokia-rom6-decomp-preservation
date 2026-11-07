/* ROM6 0x5B5C FRAG_5B5C -- 66w pshm/calld twin + copy-out, three entries.
 * Verified encoding: src/rom6/kernel/5b5c_frag_5b5c.asm (recombine MATCH).
 * ORIGIN 0x5B5C
 * EXPECT: F7B9 44F8 2621 3CF8 01D3 82F8 2621 F6B9 7711 2B55 7710 2BC7 4A11 E896 8217 7715 DCFC F274 5BD9 7714 0160 8A10 7714 0161 6D97 E897 F274 5BD9 7715 DCFC 10F8 2EF5 F844 5BB2 76F8 2F02 00C0 10F8 2621 F842 5BB2 76F8 2F02 00B1 F073 5BB2 F7B9 3CF8 01D3 82F8 2622 F6B9 76F8 2621 0000 7713 2BC7 7712 2B1C E721 EC38 E598 F273 5B48 7710 2B55
 *
 * Intent: No-static-xref head (computed/dark entry, HYPOTHESIS) plus the
 * 5B68 twin of the 5B26 5B48 tail. FRAG_5B5C: OVM = 1 (hardware);
 * A = (*(0x2621) << 16) + (*(0x1D3) << 16); *(0x2621) = A-high;
 * OVM = 0 (hardware); AR1 = 11093, AR0 = 11207; falls into 5B68.
 * FRAG_5B68 (also bcd/b target from the FRAG_5B9E span): push AR1
 * (balanced by the popm below); A = 150, *(0x17) = A-high = 0
 * (sth A,DP+0x17; DP = 0 assumed -- no static entry, trace-confirmable);
 * AR5 = -9021; calld SUB_5BD9 with AR4 = 352 riding in the delay stm
 * (callee-visible); popm restores AR0 = pushed AR1; AR4 = 353;
 * AR7++ (mar *ar7+; AR7 live-in, never read: caller state, noted);
 * A = 151; calld SUB_5BD9 with AR5 = -9021 riding in the delay stm.
 * Flag cascade (A fresh throughout): *(0x2EF5) != 0 exits to FRAG_5BB2
 * (bc aneq); else *(0x2F02) = 192; *(0x2621) >= 0 exits to FRAG_5BB2
 * (bc ageq); else *(0x2F02) = 177; all arms join FRAG_5BB2 (b).
 * FRAG_5B8A (zero static xrefs; computed-entry HYPOTHESIS, same class as
 * SEG_5B3D): copy-out tail. OVM = 1 (hardware); A = (*(0x2621) << 16) +
 * (*(0x1D3) << 16) (A entry-dead: the cascade above reloaded A, so the
 * add recomputes from the 177/192 cell value -- transcribed literally);
 * *(0x2622) = A-high; OVM = 0; *(0x2621) = 0; AR3 = 11207, AR2 = 11036,
 * AR1 = AR2 (mvmm); 57 DARAM moves *AR3++ = *AR2++ (rpt #56 + mvdd);
 * unconditional delayed branch to FRAG_5B48 (bd 0x5b48; delay
 * stm #11093,ar0 executes first; the pshm twin head inside SEG_5B26's
 * span -- forward extern frag_5B48). Bound 5B5C-5B9D.
 */
extern void sub_5BD9(long a_live, int *par4, int *par5, int ar0_live);
extern void frag_5BB2(int ar0_live);
extern void frag_5B48(int ar0_live, int ar1_live);

void frag_5B68(int ar0_live, int ar1_live)
{
    int ar0 = ar0_live;
    int ar1 = ar1_live;
    long a;

    /* pshm ar1 (balanced by the popm below) */
    a = 150L;                                            /* ld #150,a */
    *(volatile int *)0x17 = 0;     /* sth a,DP+0x17 (A-hi = 0; DP = 0?) */
    /* stm #-9021,ar5 */
    /* calld 0x5bd9 (delay stm #352,ar4 rides in, callee-visible) */
    sub_5BD9(150L, (int *)352, (int *)0xDCFC, ar0);
    ar0 = ar1;                            /* popm ar0: pops pushed AR1 */
    /* stm #353,ar4 */
    /* mar *ar7+: AR7 live-in ++ (never read: caller state, noted) */
    a = 151L;                                            /* ld #151,a */
    /* calld 0x5bd9 (delay stm #-9021,ar5 rides in) */
    sub_5BD9(151L, (int *)353, (int *)0xDCFC, ar0);
    a = (long)*(volatile int *)0x2EF5;                   /* ld */
    if (a != 0) {                                        /* bc aneq */
        frag_5BB2(ar0);
        return;
    }
    *(volatile int *)0x2F02 = 192;                       /* st #192 */
    a = (long)*(volatile int *)0x2621;                   /* ld */
    if (a >= 0) {                                        /* bc ageq */
        frag_5BB2(ar0);
        return;
    }
    *(volatile int *)0x2F02 = 177;                       /* st #177 */
    frag_5BB2(ar0);                                      /* b 0x5bb2 */
}

void frag_5B8A(void)
{
    long a;
    int k;
    int *par2 = (int *)11036;                        /* stm #11036,ar2 */
    int *par3 = (int *)11207;                        /* stm #11207,ar3 */

    /* ssbx st1,ovm (hardware, no C form) */
    a = ((long)*(volatile int *)0x2621 << 16) +
        ((long)*(volatile int *)0x1D3 << 16);        /* ld/add,16 */
    *(volatile int *)0x2622 = (int)((a >> 16) & 0xFFFF); /* sth */
    /* rsbx st1,ovm (hardware, no C form) */
    *(volatile int *)0x2621 = 0;                     /* st #0 */
    /* mvmm ar2,ar1 (AR1 = AR2) */
    for (k = 0; k < 57; k++)                         /* rpt #56 + mvdd */
        *par2++ = *par3++;
    /* bd 0x5b48 (delay stm #11093,ar0 runs first) */
    frag_5B48(11093, 11036);
}

void frag_5B5C(void)
{
    long a;

    /* ssbx st1,ovm (hardware, no C form) */
    a = ((long)*(volatile int *)0x2621 << 16) +
        ((long)*(volatile int *)0x1D3 << 16);            /* ld/add,16 */
    *(volatile int *)0x2621 = (int)((a >> 16) & 0xFFFF); /* sth */
    /* rsbx st1,ovm (hardware, no C form) */
    /* stm #11093,ar1; stm #11207,ar0; fall into 5B68 */
    frag_5B68(11207, 11093);
}
