/* ROM6 0x3460 DISPATCH_CMP_3460 -- 21w.
 * Verified encoding: src/rom6/rf/3460_dispatch_cmp_3460.asm (recombine MATCH).
 * ORIGIN 0x3460
 * EXPECT: F0F8 F030 00FF 8813 60F8 250F 0022 F210 0070 F845 3475 F210 00B0 F845 3480 F210 00B1 F845 3491 F073 3497
 *
 * Intent: Masked compare fanout. A = A-live-in >> 8 logical AND 255 (sftl per logical barrel semantics, and); AR3 = A (stlm, live-out, consumer unknown, noted). Cell 0x250F == 34 sets TC (cmpm, TC live-out, may feed the dark lane consumers since no in-span TC test reads it, noted). Then A = B-live-in - 112/-176/-177 in turn (sub per op_sub: dst = src minus operand), zero tail-enters dark 0x3475/0x3480/0x3491 respectively (bc aeq trio, forward externs); else tail-enters dark 0x3497 (b, forward extern). Bound 3460-3474 per .asm header (recombine MATCH).
 */
extern void frag_3475(void);
extern void frag_3480(void);
extern void frag_3491(void);
extern void frag_3497(void);

void frag_3460(int a_live, int b_live)
{
    int a;
    a = (a_live >> 8) & 0xFF;                    /* sftl a,-8; and #255,a */
    /* stlm a,ar3 (AR3 live-out, consumer unknown) */
    /* cmpm *(0x250f),#34 (TC live-out, may feed lane consumers) */
    a = b_live - 112;                            /* sub #112,b,a */
    if (a == 0) {                                /* bc 0x3475,aeq */
        frag_3475();                             /* tail, dark */
        return;
    }
    a = b_live - 176;                            /* sub #176,b,a */
    if (a == 0) {                                /* bc 0x3480,aeq */
        frag_3480();                             /* tail, dark */
        return;
    }
    a = b_live - 177;                            /* sub #177,b,a */
    if (a == 0) {                                /* bc 0x3491,aeq */
        frag_3491();                             /* tail, dark */
        return;
    }
    frag_3497();                                 /* b 0x3497 tail */
}
