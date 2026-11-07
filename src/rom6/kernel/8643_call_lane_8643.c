/* ROM6 0x8643 CALL_LANE_8643 -- 11w.
 * Verified encoding: src/rom6/kernel/8643_call_lane_8643.asm (recombine MATCH).
 * ORIGIN 0x8643
 * EXPECT: F074 8BD5 F074 8F97 F074 8813 F074 8653 F074 8675 FC00
 *
 * Intent: Boot-stage five-call fanout. Calls routine_8BD5(a_live) (A caller-live, unbound, flagged; MSB
 * lane inside callee); then routine_8F97(); routine_8813(); sub_8653() (2w head-call stub, C);
 * frag_8675(); return. Entry: post-call head (prev 8641 call 592); exterior callers 0x83CA/0x2FD9B (xrefs).
 */
extern void routine_8BD5(int a_live);
extern void routine_8F97(void);
extern void routine_8813(void);
extern void sub_8653(void);
extern void frag_8675(void);

void sub_8643(int a_live)
{

    routine_8BD5(a_live);                                  /* call 0x8bd5 */
    routine_8F97();                                        /* call 0x8f97 */
    routine_8813();                                        /* call 0x8813 */
    sub_8653();                                            /* call 0x8653 */
    frag_8675();                                           /* call 0x8675 */
    /* ret @864D */
}
