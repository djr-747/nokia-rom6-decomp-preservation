/* ROM6 0x36E1 FRAG_36E1 -- 15w.
 * Verified encoding: src/rom6/kernel/36e1_frag_36e1.asm (recombine MATCH).
 * ORIGIN 0x36E1
 * EXPECT: 60F8 0008 0017 F820 36F0 68F8 058F 0FFF 69F8 058F 3000 F074 2E2F F073 2E64
 *
 * Intent: Dispatcher-clause arm. AL != 23 tail-enters FRAG_36F0 (bc 0x36f0,ntc, C: frag_36F0). Else clears low 12 bits of cell 0x58F and sets bits 12-13 (andm #4095; orm #12288), calls dispatcher_entry_2E2F, tail-enters DISPATCH_MATCH_LOOP (b 0x2e64, forward extern). Bound 36E1-36EF.
 */
extern void frag_36F0(void);
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void frag_36E1(void)
{
    if (*(volatile int *)0x8 != 23) {            /* cmpm, bc ntc */
        frag_36F0();                             /* tail call */
        return;
    }
    *(volatile int *)0x58F &= 4095;          /* andm #4095 */
    *(volatile int *)0x58F |= 12288;         /* orm #12288 */
    dispatcher_entry_2E2F();                     /* call 0x2e2f */
    dispatch_match_loop();                       /* b 0x2e64 tail */
}
