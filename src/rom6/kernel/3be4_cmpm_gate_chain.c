/* ROM6 0x3BE4 CMPM_GATE_CHAIN -- 26w.
 * Verified encoding: src/rom6/kernel/3be4_cmpm_gate_chain.asm (recombine MATCH).
 * ORIGIN 0x3BE4
 * EXPECT: 60F8 250F 0022 F820 3BFE 60F8 34BF 0003 F820 3BFE 60F8 262B 00E0 F830 3BFE 61F8 3490 0100 F830 3BFE 61F8 3490 0200 F830 3BFE FC00
 *
 * Intent: Compare/bit-test chain with shared tail. Tail-calls FRAG_3BFE (TC set, exact) when: cell 0x250F != 34 (cmpm, bc ntc), cell 0x34BF != 3, cell 0x262B == 224 (bc tc), bit 8 of cell 0x3490 set (bitf any-bit TC per ti-c54x op_bitf, bc tc), bit 9 set; else falls to RET. CMPM sets TC on equal per ti-c54x op_cmpm.
 */
extern void frag_3BFE(void);

void cmpm_gate_chain_3BE4(void)
{
    if (*(volatile int *)0x250F != 34) {         /* cmpm, bc ntc */
        frag_3BFE(); return;
    }
    if (*(volatile int *)0x34BF != 3) {          /* cmpm, bc ntc */
        frag_3BFE(); return;
    }
    if (*(volatile int *)0x262B == 224) {        /* cmpm, bc tc */
        frag_3BFE(); return;
    }
    if ((*(volatile int *)0x3490 & 256) != 0) {  /* bitf, bc tc */
        frag_3BFE(); return;
    }
    if ((*(volatile int *)0x3490 & 512) != 0) {  /* bitf, bc tc */
        frag_3BFE(); return;
    }
    /* ret */
}
