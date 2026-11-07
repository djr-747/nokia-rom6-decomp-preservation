/* ROM6 0x4A12 FRAG_4A12 -- 7w.
 * Verified encoding: src/rom6/kernel/4a12_frag_4a12.asm (recombine MATCH).
 * ORIGIN 0x4A12
 * EXPECT: 60F8 37B0 000F F830 4A1E F073 4A4B
 *
 * Intent: B-lane chain link. Cell 0x37B0 == 15 tail-enters 0x4A1E (bc 0x4a1e,tc: dark, no .asm span so no C file, forward extern); else tail-enters FRAG_4A4B (b 0x4a4b: has .asm, no C yet, forward extern). NOTE: symbols.yaml notes for 4A12/4A46 claim other targets (self-loop/back-edge); ROM bytes verify 4A4B/4ADF and the .asm files agree, flagged for symbols cleanup. Bound 4A12-4A18.
 */
extern void frag_4A1E(void); /* joins 4a19_frag_4a19 interior @+0x5; see docs/evidence/extern-triage.md */
extern void frag_4A4B(void);

void frag_4A12(void)
{
    if (*(volatile int *)0x37B0 == 15) {         /* cmpm, bc tc */
        frag_4A1E();                             /* tail, dark */
        return;
    }
    frag_4A4B();                                 /* b 0x4a4b tail */
}
