/* ROM6 0x9453 FRAG_9453 -- 6w.
 * Verified encoding: src/rom6/kernel/9453_frag_9453.asm (recombine MATCH).
 * ORIGIN 0x9453
 * EXPECT: F274 9A50 7714 009A F846 942E
 *
 * Intent: FRAG_9453 guarded verify tail (6w). Delayed-call into unbound SUB_9A50 (calld, forward extern void; delay stm #154,ar4 preset dead in C, noted). A-live-in positive runs unbound COBBA_VERIFY_LOOP 0x942E (bc agt, signed per 6871, has .asm, forward extern; A at the branch is 9A50's A-out, unobservable, not threaded). Else falls through (dark).
 */
extern void sub_9A50(void);
extern void frag_942E(void);

void frag_9453(int a_live)
{
    int a = a_live;
    /* stm #154,ar4 (calld delay slot, dead preset, noted) */
    sub_9A50();                                    /* calld 0x9a50 */
    if (a > 0) {                                   /* bc 0x942e,agt */
        frag_942E();                               /* away, unbound C */
        return;
    }
    /* fallthrough dark */
}
