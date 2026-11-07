/* ROM6 0xDBC1 EXP_NORM_DB8C -- 2w.
 * Verified encoding: src/rom6/modem/dbc1_exp_norm_db8c.asm (recombine MATCH).
 * ORIGIN 0xDBC1
 * EXPECT: F495 F48F
 *
 * Intent: Delay-slot spill: single-cycle settle (nop, no state) then one
 * normalize step on A (norm a: A <<= T with signed-T shift per ti-c54x
 * op_norm_acc ground truth; 4315 hand-roll precedent). Entered via the
 * DBC0 retd delay slots (wave-11 spill fix); falls through into pooled
 * SUB_DBC3. A/T are delay-slot residues (dark live-ins, explicit
 * params). 40-bit wraparound, OVM saturation, and the SXM-dependent
 * negative-T fill are unmodelable in 32-bit long (flagged).
 */
extern void sub_DBC3(void);                          /* fall-through abut, pooled */

void frag_DBC1(int a_in, int t_in)
{
    int a = a_in;
    int t = t_in;
    /* nop (single-cycle settle, no state) */
    if (t >= 0) {
        a <<= t;                                     /* norm a, T >= 0 lane */
    } else {
        a >>= -t;                                    /* norm a, T < 0 lane (SXM fill flagged) */
    }
    (void)a;
    sub_DBC3();                                      /* fall-through abut */
}
