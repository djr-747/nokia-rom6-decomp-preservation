/* ROM6 0x36A1 FRAG_36A1 -- 15w.
 * Verified encoding: src/rom6/kernel/36a1_frag_36a1.asm (recombine MATCH).
 * ORIGIN 0x36A1
 * EXPECT: 61F8 058F 0080 F830 36B0 61F8 250F 00D0 F830 36C2 61F8 250F 0020 F820 36C2
 *
 * Intent: Three-way flag fanout. Bit 7 of cell 0x58F set tail-enters FRAG_36B0 (bc 0x36b0,tc, C: frag_36B0). Any of bits 4/6/7 of cell 0x250F (mask 208) set, or bit 5 clear, jumps away to FRAG_36C2 (bc pair: has .asm, bit-reversed, asm-only, extern only). Else falls into the 0x36AA head. BITF any-bit TC per ti-c54x op_bitf. Bound 36A1-36AF.
 */
extern void frag_36B0(void);
extern void frag_36C2(void);

void frag_36A1(void)
{
    if ((*(volatile int *)0x58F & 128) != 0) {   /* bitf, bc tc */
        frag_36B0();                             /* tail call */
        return;
    }
    if ((*(volatile int *)0x250F & 208) != 0) {  /* bitf, bc tc */
        frag_36C2();                             /* away, asm-only span */
        return;
    }
    if ((*(volatile int *)0x250F & 32) == 0) {   /* bitf, bc ntc */
        frag_36C2();                             /* away, asm-only span */
        return;
    }
    /* falls through (no exit in span) */
}
