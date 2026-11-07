/* ROM6 0x952E FRAG_952E -- 14w.
 * Verified encoding: src/rom6/kernel/952e_frag_952e.asm (recombine MATCH). init pair + port 1 kick.
 * ORIGIN 0x952E
 * EXPECT: F074 05D6 F074 97DD F020 0100 F495 75F8 0008 0001 EC14 F495 F073 283D
 * Intent: Runs dark SUB_05D6 then dark SUB_97DD (calls, forward externs; 97DD
 * has .asm only, entry regs per its listing: or-accumulates caller state, so
 * declared void per opaque-callee convention). A = 256 (ld #256,a). Kicks
 * port 1 from DP alias cell 8 (portw *(0x8),1, extern op) after a 21-cycle
 * nop settle (rpt #20 + nop). A = 256 rides dead into the tail (no in-body
 * read after the load). Tail-enters dark 0x283D (b, forward extern, void per
 * 2867/2875 precedent). Bound 952E-953B (exit F073@953A->283D + operand 953B).
 */
extern void sub_05D6(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_97DD(void); /* joins 97dd_wrap_97dd; see docs/evidence/extern-triage.md */
extern void portw_alias08_port1(void); /* HW port alias, emulator-provided */
extern void frag_283D(void); /* joins 2800_stretch_2800 interior @+0x3D; see docs/evidence/extern-triage.md */

void frag_952E(void)
{
    int a;

    sub_05D6();                                /* call 0x5d6 */
    sub_97DD();                                /* call 0x97dd */
    a = 256;                                   /* ld #256,a (dead at tail) */
    (void)a;
    /* nop; portw *(0x8),1; rpt #20 + nop settle */
    portw_alias08_port1();
    frag_283D();                               /* b 0x283d tail */
}
