/* ROM6 0x3557 FRAG_3557 -- 5w.
 * Verified encoding: src/rom6/kernel/3557_frag_3557.asm (recombine MATCH).
 * ORIGIN 0x3557
 * EXPECT: 61F8 3EC8 0200 F820 35A0
 *
 * Intent: Flag test with fall-through. Bit 9 of cell 0x3EC8 clear jumps away to FRAG_35A0 (bc 0x35a0,ntc: has .asm, no C yet, forward extern); else falls into the 0x355C head. Bound 3557-355B.
 */
extern void frag_35A0(void);

void frag_3557(void)
{
    if ((*(volatile int *)0x3EC8 & 512) == 0) {  /* bitf, bc ntc */
        frag_35A0();                             /* away, unbound C */
        return;
    }
    /* falls through (no exit in span) */
}
