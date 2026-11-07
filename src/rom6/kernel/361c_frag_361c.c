/* ROM6 0x361C FRAG_361C -- 7w.
 * Verified encoding: src/rom6/kernel/361c_frag_361c.asm (recombine MATCH).
 * ORIGIN 0x361C
 * EXPECT: 61F8 054D 0004 F820 3623 F073 2E64
 *
 * Intent: Flag test with match-loop tail. Bit 2 of cell 0x54D clear jumps away to FRAG_3623 (bc 0x3623,ntc: bit-reversed span, asm-only, extern only); else tail-enters DISPATCH_MATCH_LOOP (b 0x2e64, C: dispatch_match_loop). Bound 361C-3622.
 */
extern void frag_3623(void);
extern void dispatch_match_loop(void);

void frag_361C(void)
{
    if ((*(volatile int *)0x54D & 4) == 0) {     /* bitf, bc ntc */
        frag_3623();                             /* away, asm-only span */
        return;
    }
    dispatch_match_loop();                       /* b 0x2e64 tail */
}
