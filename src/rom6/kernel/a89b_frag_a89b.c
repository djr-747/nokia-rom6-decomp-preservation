/* ROM6 0xA89B FRAG_A89B -- 10w.
 * Verified encoding: src/rom6/kernel/a89b_frag_a89b.asm (recombine MATCH).
 * ORIGIN 0xA89B
 * EXPECT: 60F8 0008 1000 F820 A8A5 10F8 3083 F845 A8B9 FC00
 *
 * Intent: Compare-and-fanout. Tail-calls FRAG_A8A5 when cell 0x8 differs from 4096 (cmpm sets TC on equal per ti-c54x op_cmpm, bc ntc taken when unequal); else loads cell 0x3083 and tail-calls FRAG_A8B9 when zero (bc aeq), else returns.
 */
extern void frag_A8A5(void);
extern void frag_a8b9_zero(void);

void frag_A89B(void)
{
    if (*(volatile int *)0x8 != 4096) {          /* cmpm, bc ntc */
        frag_A8A5();                             /* tail call 0xa8a5 */
        return;
    }
    if (*(volatile int *)0x3083 == 0) {          /* ld, bc aeq */
        frag_a8b9_zero();                        /* tail call 0xa8b9 */
        return;
    }
    /* ret */
}
