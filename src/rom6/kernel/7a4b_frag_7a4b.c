/* ROM6 0x7A4B FRAG_7A4B -- 16w.
 * Verified encoding: src/rom6/kernel/7a4b_frag_7a4b.asm (recombine MATCH).
 * ORIGIN 0x7A4B
 * EXPECT: 60F8 34BF 0000 F830 7A5B 60F8 34BF 0002 F830 7A5B 7084 34CA 7713 34BE F073 7AB0
 *
 * Intent: Cell-equality pair with store tail. Cell 0x34BF == 0 or == 2 tail-enters FRAG_7A5B (bc tc pair: has .asm, no C yet, forward extern). Else stores cell 0x34CA through live-in AR4 (mvdk, AR4 fixed); AR3 = 13502 preset dead after (noted); tail-enters dark 0x7AB0 (b, forward extern). CMPM TC-on-equal per op_cmpm. Bound 7A4B-7A5A.
 */
extern void frag_7A5B(void);
extern void frag_7AB0(void);

void frag_7A4B(int *par4)
{
    if (*(volatile int *)0x34BF == 0) {          /* cmpm, bc tc */
        frag_7A5B();                             /* tail, unbound C */
        return;
    }
    if (*(volatile int *)0x34BF == 2) {          /* cmpm, bc tc */
        frag_7A5B();                             /* tail, unbound C */
        return;
    }
    *par4 = *(volatile int *)0x34CA;        /* mvdk 0x34ca,*ar4 */
    /* stm #13502,ar3 (dead preset, unused after) */
    frag_7AB0();                                 /* b 0x7ab0 tail */
}
