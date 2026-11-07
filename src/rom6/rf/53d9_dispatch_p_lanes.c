/* ROM6 0x53D9 DISPATCH_P_LANES_53D9 -- 18w.
 * Verified encoding: src/rom6/rf/53d9_dispatch_p_lanes.asm (recombine MATCH).
 * ORIGIN 0x53D9
 * EXPECT: F074 0672 F981 A7F8 F981 A7F1 F074 B6E6 F074 C717 F074 9FA8 10F8 3FC8 F074 54A4 F073 54BB
 *
 * Intent: Far-call chain with fetch. Runs dark 0x672 (call, forward extern), far calls 0x1A7F8/0x1A7F1 (extended addresses, modeled extern per b036), PARAM_BUILDER_B6E6, INIT_FILTER_C717, SUB_9FA8 (all have .asm, no C yet, forward externs). A = cell 0x3FC8 threaded into 0x54A4 (call, unbound C, A arg per B-threading precedent); tail-enters dark 0x54BB (b, forward extern). 18w per .asm header (recombine MATCH).
 */
extern void sub_0672(void);
extern void far_1A7F8(void);
extern void far_1A7F1(void);
extern void param_builder_b6e6(void);
extern void init_filter_c717(void);
extern void sub_9FA8(void);
extern void frag_54A4(int a_live);
extern void frag_54BB(void);

void frag_53D9(void)
{
    int a;
    sub_0672();                                  /* call 0x672 */
    far_1A7F8();                                 /* fcall 0x1a7f8 */
    far_1A7F1();                                 /* fcall 0x1a7f1 */
    param_builder_b6e6();                        /* call 0xb6e6 */
    init_filter_c717();                          /* call 0xc717 */
    sub_9FA8();                                  /* call 0x9fa8 */
    a = *(volatile int *)0x3FC8;             /* ld *(0x3fc8),a */
    frag_54A4(a);                                /* call 0x54a4 (A live) */
    frag_54BB();                                 /* b 0x54bb tail */
}
