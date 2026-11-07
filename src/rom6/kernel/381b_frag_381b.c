/* ROM6 0x381B FRAG_381B -- 12w.
 * Verified encoding: src/rom6/kernel/381b_frag_381b.asm (recombine MATCH).
 * ORIGIN 0x381B
 * EXPECT: 1082 F0F8 F110 0000 F84D 3827 F110 0001 F84D 382E F073 37DF
 *
 * Intent: Byte-class dispatch. A = *AR2-live-in >> 8 logical (sftl); B = A - 0 (sub #0,a,b exact); B == 0 tail-enters FRAG_3827 (bc 0x3827,beq, C: frag_3827). B = A - 1 == 0 tail-enters FRAG_382E (bc 0x382e,beq, C: frag_382E). Else tail-enters 0x37DF (b: claimed FRAG_37D8 interior, no span, forward extern). Derivation: sftl is logical so shifted == 0 needs old-high zero (old >= 0) and old < 256; shifted == 1 needs 256 <= old < 512; negatives match neither; the int range tests below are exact under both SXM states. SUB dst = src minus operand per ti-c54x op_sub. Bound 381B-3826.
 */
extern void frag_3827(void);
extern void frag_382E(void);
extern void frag_37DF(void);

void frag_381B(int *par2)
{
    int a = *par2;                               /* ld *ar2,a */
    /* sftl a,-8 (logical); sub #0/#1,a,b; bc beq pair */
    if (a >= 0 && a < 256) {                     /* shifted == 0 */
        frag_3827();                             /* tail call */
        return;
    }
    if (a >= 256 && a < 512) {                  /* shifted == 1 */
        frag_382E();                             /* tail call */
        return;
    }
    frag_37DF();                                 /* b 0x37df tail */
}
