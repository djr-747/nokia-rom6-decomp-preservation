/* ROM6 0x36F0 FRAG_36F0 -- 11w.
 * Verified encoding: src/rom6/kernel/36f0_frag_36f0.asm (recombine MATCH).
 * ORIGIN 0x36F0
 * EXPECT: 60F8 0008 0003 F820 36FB F981 AA2C F074 2E2F F073 2E64
 *
 * Intent: Dispatcher-clause arm. AL (cell 0x8 alias) != 3 tail-enters FRAG_36FB (bc 0x36fb,ntc: has .asm, no C yet, forward extern per convention). Else far call 0x1AA2C (extended address, modeled as extern per b036/b0a1 precedent), call dispatcher_entry_2E2F, tail-enter DISPATCH_MATCH_LOOP (b 0x2e64, no C binding yet, forward extern). Bound 36F0-36FA.
 */
extern void frag_36FB(void);
extern void far_1AA2C(void);
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void frag_36F0(void)
{
    if (*(volatile int *)0x8 != 3) {             /* cmpm, bc ntc */
        frag_36FB();                             /* tail, unbound C */
        return;
    }
    far_1AA2C();                                 /* fcall 0x1aa2c */
    dispatcher_entry_2E2F();                     /* call 0x2e2f */
    dispatch_match_loop();                       /* b 0x2e64 tail */
}
