/* ROM6 0x546B DISPATCH_P_LANES_546B -- 30w.
 * Verified encoding: src/rom6/rf/546b_dispatch_p_lanes.asm (recombine MATCH).
 * ORIGIN 0x546B
 * EXPECT: F074 06E4 60F8 0573 A249 F820 5489 6882 FF7F 76F8 0B68 0000 F074 D970 E901 81F8 0C4C 76F8 0A5A 0003 F074 B6E6 F074 C717 F074 9FA8 10F8 3FC9 F073 53CD
 *
 * Intent: P-lane store chain with compare tail. Runs dark SUB_06E4 (call). Cell 0x573 != -23991 runs unbound FRAG_5489 with entry AR2 (bc ntc, has .asm, forward extern with AR2 param per its own header). Else clears bit 7 of *AR2-entry (andm, AR2 threaded as param, unstepped); cell 0xB68 = 0; runs dark SUB_D970; B = 1 stored low to cell 0xC4C; cell 0xA5A = 3; runs PARAM_BUILDER_B6E6, INIT_FILTER_C717, SUB_9FA8 (forward externs); A = cell 0x3FC9 tail-enters dark 0x53CD (b, forward extern with A arg). Bound 546B-5488.
 */
extern void sub_06E4(void);
extern void frag_5489(int *par2);
extern void sub_D970(void);
extern void param_builder_b6e6(void);
extern void init_filter_c717(void);
extern void sub_9FA8(void);
extern void frag_53CD(int a_live);

void frag_546B(int *par2)
{
    int a;
    sub_06E4();                                    /* call 0x6e4 */
    if (*(volatile int *)0x573 != -23991) {    /* cmpm, bc ntc */
        frag_5489(par2);                           /* away, AR2 live */
        return;
    }
    *par2 &= -129;                                 /* andm #-129,*ar2 */
    *(volatile int *)0x0B68 = 0;               /* st */
    sub_D970();                                    /* call 0xd970 */
    *(volatile int *)0x0C4C = 1;               /* ld #1,b; stl */
    *(volatile int *)0x0A5A = 3;               /* st */
    param_builder_b6e6();                          /* call 0xb6e6 */
    init_filter_c717();                            /* call 0xc717 */
    sub_9FA8();                                    /* call 0x9fa8 */
    a = *(volatile int *)0x3FC9;               /* ld */
    frag_53CD(a);                                  /* b 0x53cd tail */
}
