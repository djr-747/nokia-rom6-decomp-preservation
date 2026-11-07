/* ROM6 0x53BA DISPATCH_P_LANES_53BA -- 31w.
 * Verified encoding: src/rom6/rf/53ba_dispatch_p_lanes.asm (recombine MATCH).
 * ORIGIN 0x53BA
 * EXPECT: F074 0672 60F8 0573 A249 F820 53D9 F981 A7F8 F981 A7F1 F074 B6E6 F074 C717 F074 9FA8 10F8 3FC8 F074 06E2 F074 54A4 68F8 263A FEFF E904 F074 B461 F073 54BB
 *
 * Intent: P-lane far-call chain with measure tail. Runs dark SUB_0672 (call, per 53D9). Cell 0x573 != -23991 runs C FRAG_53D9 (bc ntc, C-bound). Else far calls 0x1A7F8/0x1A7F1 (modeled extern per 53D9), PARAM_BUILDER_B6E6, INIT_FILTER_C717, SUB_9FA8 (all have .asm, no C yet, forward externs). A = cell 0x3FC8 threaded through dark SUB_06E2 into FRAG_54A4 (call, A arg per 53D9 B-threading precedent; 6E2 clobbers unobservable). Clears bit 8 of cell 0x263A; B = 4; runs unbound FRAG_B461 (call, has .asm, forward extern); tail-enters dark 0x54BB (b, per 53D9). Bound 53BA-53D8.
 */
extern void sub_0672(void);
extern void frag_53D9(void);
extern void far_1A7F8(void);
extern void far_1A7F1(void);
extern void param_builder_b6e6(void);
extern void init_filter_c717(void);
extern void sub_9FA8(void);
extern void sub_06E2(void);
extern void frag_54A4(int a_live);
extern void frag_B461(void);
extern void frag_54BB(void);

void frag_53BA(void)
{
    int a;
    sub_0672();                                    /* call 0x672 */
    if (*(volatile int *)0x573 != -23991) {    /* cmpm, bc ntc */
        frag_53D9();                               /* away, C-bound */
        return;
    }
    far_1A7F8();                                   /* fcall 0x1a7f8 */
    far_1A7F1();                                   /* fcall 0x1a7f1 */
    param_builder_b6e6();                          /* call 0xb6e6 */
    init_filter_c717();                            /* call 0xc717 */
    sub_9FA8();                                    /* call 0x9fa8 */
    a = *(volatile int *)0x3FC8;               /* ld */
    sub_06E2();                                    /* call 0x6e2 (A threads) */
    frag_54A4(a);                                  /* call 0x54a4 */
    *(volatile int *)0x263A &= -257;           /* andm */
    /* ld #4,b (B = 4, dead: B461 intake unknown, noted) */
    frag_B461();                                   /* call 0xb461 */
    frag_54BB();                                   /* b 0x54bb tail */
}
