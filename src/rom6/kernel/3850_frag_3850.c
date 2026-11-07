/* ROM6 0x3850 FRAG_3850 -- 18w.
 * Verified encoding: src/rom6/kernel/3850_frag_3850.asm (recombine MATCH).
 * ORIGIN 0x3850
 * EXPECT: 4814 F030 00FF 4913 F3E8 F1A0 8910 4813 F030 FF00 4914 F3F8 F2A0 E902 F074 93CE F073 37DF
 *
 * Intent: Register zigzag with classify call. A = AR4-live-in AND 255; B = AR3-live-in << 8 logical OR A (sftl plus or); AR0 = B (stlm, dead preset, noted). A = AR3 AND -256 (clears low byte); B = AR4 >> 8 logical OR into A; B = 2 threaded into 0x93CE (call, has .asm, no C yet, forward extern with B arg: lane id per caller-classify role, noted); tail-enters 0x37DF (b: claimed FRAG_37D8 interior, no span, forward extern). ldm reads registers as values (no AR movement, int params). sftl shifts logical per barrel semantics. Bound 3850-3861.
 */
extern void frag_93CE(int b_live);
extern void frag_37DF(void);

void frag_3850(int ar3_live, int ar4_live)
{
    int a;
    int b;
    a = ar4_live & 255;                          /* ldm ar4,a; and #255,a */
    b = ar3_live << 8;                           /* ldm ar3,b; sftl b,8 */
    b |= a;                                      /* or a,b */
    /* stlm b,ar0 (AR0 dead preset, unused after) */
    a = ar3_live & -256;                         /* ldm ar3,a; and #-256,a */
    b = (ar4_live >> 8) & 0xFF;                  /* ldm ar4,b; sftl b,-8 */
    a |= b;                                      /* or b,a */
    b = 2;                                       /* ld #2,b */
    frag_93CE(b);                                /* call 0x93ce (B live) */
    frag_37DF();                                 /* b 0x37df tail */
}
