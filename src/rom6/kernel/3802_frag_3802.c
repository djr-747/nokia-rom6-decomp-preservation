/* ROM6 0x3802 FRAG_3802 -- 4w.
 * Verified encoding: src/rom6/kernel/3802_frag_3802.asm (recombine MATCH).
 * ORIGIN 0x3802
 * EXPECT: F074 8413 F073 37DF
 *
 * Intent: Vestibule arm. Runs SUB_8413 (has .asm, no C yet, forward extern), tail-enters 0x37DF (b 0x37df: claimed FRAG_37D8 interior code, no span so no C file, forward extern). Bound 3802-3805 (micro-arm of the 3802-388B vestibule converging on 37DF).
 */
extern void sub_8413(void);
extern void frag_37DF(void); /* joins 37d8_frag_37d8 interior @+0x7; see docs/evidence/extern-triage.md */

void frag_3802(void)
{
    sub_8413();                                  /* call 0x8413 */
    frag_37DF();                                 /* b 0x37df tail */
}
