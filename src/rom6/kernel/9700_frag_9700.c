/* ROM6 0x9700 FRAG_9700 -- 8w.
 * Verified encoding: src/rom6/kernel/9700_frag_9700.asm (recombine MATCH).
 * ORIGIN 0x9700
 * EXPECT: 6184 0040 F820 9708 F074 978F F073 970B
 *
 * Intent: FRAG_9700 bit-test fork (8w; the retd at 0x9708 belongs to the FRAG_9708 span). Bit 6 of *AR4-entry clear runs C FRAG_9708 with AR4 (bc ntc, C-bound passthrough). Else runs dark SUB_978F (call, forward extern); falls into unbound FRAG_970B with entry AR2 (has .asm, forward extern with AR2 param per its portr head).
 */
extern void frag_9708(int *par4);
extern void sub_978F(void); /* joins 978f_sub_978f; see docs/evidence/extern-triage.md */
extern void frag_970B(int *par2); /* joins 970b_frag_970b; see docs/evidence/extern-triage.md */

void frag_9700(int *par4, int *par2)
{
    if ((*par4 & 64) == 0) {                         /* bitf, bc ntc */
        frag_9708(par4);                             /* away, C-bound */
        return;
    }
    sub_978F();                                    /* call 0x978f */
    frag_970B(par2);                               /* b 0x970b fallthrough */
}
