/* ROM6 0x382E FRAG_382E -- 17w.
 * Verified encoding: src/rom6/kernel/382e_frag_382e.asm (recombine MATCH).
 * ORIGIN 0x382E
 * EXPECT: 1282 F030 00FF F110 0000 F84D 383F F110 0001 F84D 3844 F110 0002 F84D 3849 F073 37DF
 *
 * Intent: Small-value dispatch. A = *AR2-live-in unsigned AND 255 (ldu plus and); B = A - N for N = 0/1/2 (sub #N,a,b per op_sub), zero tail-enters FRAG_383F/3844/3849 respectively (bc beq trio, all C this turn); else tail-enters 0x37DF (b, forward extern). ldu makes the int compares exact. Bound 382E-383E.
 */
extern void frag_383F(void);
extern void frag_3844(void);
extern void frag_3849(void);
extern void frag_37DF(void);

void frag_382E(int *par2)
{
    int a = (unsigned)*par2 & 255;               /* ldu; and #255,a */
    if (a - 0 == 0) {                            /* sub #0,a,b; bc beq */
        frag_383F();                             /* tail call */
        return;
    }
    if (a - 1 == 0) {                            /* sub #1,a,b; bc beq */
        frag_3844();                             /* tail call */
        return;
    }
    if (a - 2 == 0) {                            /* sub #2,a,b; bc beq */
        frag_3849();                             /* tail call */
        return;
    }
    frag_37DF();                                 /* b 0x37df tail */
}
