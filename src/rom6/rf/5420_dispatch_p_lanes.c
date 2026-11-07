/* ROM6 0x5420 DISPATCH_P_LANES_5420 -- 20w.
 * Verified encoding: src/rom6/rf/5420_dispatch_p_lanes.asm (recombine MATCH).
 * ORIGIN 0x5420
 * EXPECT: F074 06E2 6882 FF7F F074 8641 F074 864E F074 B6E6 F074 C717 F074 9FA8 10F8 3FC7 F074 54A4 F073 54BB
 *
 * Intent: P-lane filter chain. Runs dark SUB_06E2 (call). Clears bit 7 of *AR2-entry (andm, AR2 threaded as param, unstepped). Runs dark SUB_8641/SUB_864E, PARAM_BUILDER_B6E6, INIT_FILTER_C717, SUB_9FA8 (all have .asm except 8641/864E, no C yet, forward externs). A = cell 0x3FC7 into FRAG_54A4 (call, A arg); tail-enters dark 0x54BB (b, per 53D9). Bound 5420-5433.
 */
extern void sub_06E2(void);
extern void sub_8641(void);
extern void sub_864E(void);
extern void param_builder_b6e6(void);
extern void init_filter_c717(void);
extern void sub_9FA8(void);
extern void frag_54A4(int a_live);
extern void frag_54BB(void);

void frag_5420(int *par2)
{
    int a;
    sub_06E2();                                    /* call 0x6e2 */
    *par2 &= -129;                                 /* andm #-129,*ar2 */
    sub_8641();                                    /* call 0x8641 */
    sub_864E();                                    /* call 0x864e */
    param_builder_b6e6();                          /* call 0xb6e6 */
    init_filter_c717();                            /* call 0xc717 */
    sub_9FA8();                                    /* call 0x9fa8 */
    a = *(volatile int *)0x3FC7;               /* ld */
    frag_54A4(a);                                  /* call 0x54a4 */
    frag_54BB();                                   /* b 0x54bb tail */
}
