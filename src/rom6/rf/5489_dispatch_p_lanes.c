/* ROM6 0x5489 DISPATCH_P_LANES_5489 -- 27w.
 * Verified encoding: src/rom6/rf/5489_dispatch_p_lanes.asm (recombine MATCH).
 * ORIGIN 0x5489
 * EXPECT: F074 06E4 6882 FF7F 76F8 0B68 0000 F074 D970 E901 81F8 0C4C 76F8 0A5A 0003 F074 B6E6 F074 C717 F074 9FA8 10F8 3FC9 F074 54A4 F073 54BB
 *
 * Intent: P-lane store chain with filter tail. Runs dark SUB_06E4 (call). Clears bit 7 of *AR2-entry (andm, AR2 threaded as param, unstepped); cell 0xB68 = 0; runs dark SUB_D970; B = 1 stored low to cell 0xC4C; cell 0xA5A = 3; runs PARAM_BUILDER_B6E6, INIT_FILTER_C717, SUB_9FA8 (forward externs); A = cell 0x3FC9 into FRAG_54A4 (call, A arg); tail-enters dark 0x54BB (b, per 53D9). Bound 5489-54A3. Entered from FRAG_546B with the same AR2 (interior join, C: frag_546B passes par2).
 */
extern void sub_06E4(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_D970(void);
extern void param_builder_b6e6(void); /* joins b6e6_param_builder_b6e6; see docs/evidence/extern-triage.md */
extern void init_filter_c717(void); /* joins c717_init_filter_c717; see docs/evidence/extern-triage.md */
extern void sub_9FA8(void); /* joins 9fa8_sub_9fa8; see docs/evidence/extern-triage.md */
extern void msg_fetch_routine_54A4(int a_live);
extern void frag_54BB(void);

void frag_5489(int *par2)
{
    int a;
    sub_06E4();                                    /* call 0x6e4 */
    *par2 &= -129;                                 /* andm #-129,*ar2 */
    *(volatile int *)0x0B68 = 0;               /* st */
    sub_D970();                                    /* call 0xd970 */
    *(volatile int *)0x0C4C = 1;               /* ld #1,b; stl */
    *(volatile int *)0x0A5A = 3;               /* st */
    param_builder_b6e6();                          /* call 0xb6e6 */
    init_filter_c717();                            /* call 0xc717 */
    sub_9FA8();                                    /* call 0x9fa8 */
    a = *(volatile int *)0x3FC9;               /* ld */
    msg_fetch_routine_54A4(a);                                  /* call 0x54a4 */
    frag_54BB();                                   /* b 0x54bb tail */
}
