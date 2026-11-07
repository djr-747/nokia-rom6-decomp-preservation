/* ROM6 0x5B26 SEG_5B26 -- 54w dispatch head + twin tail, three entries.
 * Entries: SEG_5B26 (dispatch head), SEG_5B3D (computed-entry twin head),
 * FRAG_5B48 (bd target from FRAG_5B8A's copy-out tail).
 * Verified encoding: src/rom6/kernel/5b26_seg_5b26.asm (recombine MATCH).
 * ORIGIN 0x5B26
 * EXPECT: F074 0674 10F8 264D F000 B10A 8811 E900 83F8 2F02 1181 F6BE EA00 F7B9 44F8 01D2 3CF8 2622 F6B9 F7E2 82F8 2622 F7B9 44F8 2621 3CF8 01D3 82F8 2621 F6B9 7711 2B55 7710 2BC7 4A11 E800 8817 7715 DCC3 F274 5BD9 7714 0160 8A10 7714 0161 E801 8817 F274 5BD9 7715 DCC3 F073 5BC6
 *
 * Intent: Table-dispatch head plus pshm/calld twin tail. Post-RET abut
 * entry after FC00@5B25 (thin: A/ARs caller-live). SEG_5B26: runs dark
 * SUB_0674 (call); AR1 = cell 0x264D - 20214 (address-valued; SUB #lk
 * per op_sub_lk); B = *(AR1-address) (dispatch-word table read);
 * CPL = 0, DP = 0, OVM = 1 (hardware state, no C form); A =
 * (*(0x1D2) << 16) + (*(0x2622) << 16) (LD/ADD Smem,16: SXM-widened
 * << 16 per op_ld_xmem_shift/op_add_xmem); OVM = 0 (hardware); computed
 * jump via baccd B (delays sth a,*(0x2622) [A-high store] + OVM = 1 run
 * first): target dark (forward extern dark_5B39_target; ROM never falls
 * through mid-span). SEG_5B3D (zero static xrefs; computed-entry
 * HYPOTHESIS): A = (*(0x2621) << 16) + (*(0x1D3) << 16);
 * *(0x2621) = A-high; then the twin tail: AR1 = 11093, AR0 = 11207,
 * push AR1 (balanced by the popm below), AR7 = 0 then 1 (set, never read
 * in span: dead live-out, noted), AR5 = -9021, calld SUB_5BD9 twice with
 * AR4 = 352/353 riding in the delay stm (callee-visible pre-branch state
 * per 4BA8), popm restoring AR0 = pushed AR1 between the calls; exits
 * via b to FRAG_5BC6 (forward extern, defined with FRAG_5B9E).
 * Bound 5B26-5B5B.
 */
extern void sub_0674(void);
extern void sub_5BD9(long a_live, int *par4, int *par5, int ar0_live);
extern void dark_5B39_target(int b_live);
extern void frag_5BC6(void);

void seg_5B26(void)
{
    long a;
    long b;
    int ar1addr;

    sub_0674();                                        /* call 0x674 */
    a = (long)*(volatile int *)0x264D - 20214L;        /* ld; add */
    ar1addr = (int)(a & 0xFFFF);                       /* stlm a,ar1 */
    b = 0;                                             /* ld #0,b */
    *(volatile int *)0x2F02 = 0;          /* sth b,*(0x2f02) (B-hi = 0) */
    b = (long)*(volatile int *)ar1addr;                /* ld *ar1,b */
    /* rsbx cpl; ld #0,dp; ssbx ovm (hardware state, no C form) */
    a = ((long)*(volatile int *)0x1D2 << 16) +
        ((long)*(volatile int *)0x2622 << 16);         /* ld/add,16 */
    /* rsbx ovm (hardware, no C form) */
    *(volatile int *)0x2622 = (int)((a >> 16) & 0xFFFF); /* baccd delay */
    /* ssbx ovm (baccd delay, hardware, no C form) */
    dark_5B39_target((int)(b & 0xFFFF));               /* baccd b */
    /* ROM never falls through: computed jump leaves mid-span */
}

void frag_5B48(int ar0_live, int ar1_live)
{
    int ar0 = ar0_live;
    int ar1 = ar1_live;
    int ar7;

    /* pshm ar1 (balanced by the popm below) */
    ar7 = 0;                                /* ld #0,a; stlm a,ar7 */
    /* calld 0x5bd9 (delay stm #352,ar4 rides in, callee-visible) */
    sub_5BD9(0L, (int *)352, (int *)0xDCC3, ar0);
    ar0 = ar1;                            /* popm ar0: pops pushed AR1 */
    /* stm #353,ar4 */
    ar7 = 1;                                /* ld #1,a; stlm a,ar7 */
    /* calld 0x5bd9 (delay stm #-9021,ar5 rides in) */
    sub_5BD9(1L, (int *)353, (int *)0xDCC3, ar0);
    frag_5BC6();                                       /* b 0x5bc6 */
}

void seg_5B3D(void)
{
    long a;

    /* ssbx ovm (hardware, no C form) */
    a = ((long)*(volatile int *)0x2621 << 16) +
        ((long)*(volatile int *)0x1D3 << 16);          /* ld/add,16 */
    *(volatile int *)0x2621 = (int)((a >> 16) & 0xFFFF); /* sth */
    /* rsbx ovm (hardware, no C form) */
    /* stm #11093,ar1; stm #11207,ar0; fall into 5B48 */
    frag_5B48(11207, 11093);
}
