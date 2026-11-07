/* ROM6 0x6657 FRAG_6657 -- 15w.
 * Verified encoding: src/rom6/kernel/6657_frag_6657.asm (recombine MATCH).
 * ORIGIN 0x6657
 * EXPECT: E8CC F274 6976 7712 2FD9 F200 0033 F010 00CC F495 F495 FF43 F000 00CC F587
 *
 * Intent: Conditional rebias with B floor. A = 204; runs 0x6976 (dark, calld, forward extern; delay stm #12249,ar2 dead, noted); A = B-live-in + 51 (add #51,b,a) - 204 (sub); two nops; A < 0 runs A += 204 then B = min(A,B) (xc 2,alt pair; MIN signed 40-bit per op_compare, A/B live-in). Falls through with A and B live-out (out-params; accumulators as long). Bound 6657-6665.
 */
extern void sub_6976(void);

void frag_6657(int b_live, long *pa_out, long *pb_out)
{
    long a;
    long b = b_live;
    a = 204;                                     /* ld #204,a */
    sub_6976();                                  /* calld (delay: dead stm) */
    a = b + 51;                                  /* add #51,b,a */
    a -= 204;                                    /* sub #204,a */
    /* nop; nop */
    if (a < 0) {                                 /* xc 2,alt */
        a += 204;                                /* add #204,a */
        b = (a < b) ? a : b;                     /* min b (signed) */
    }
    *pa_out = a;
    *pb_out = b;
    /* falls through (no exit in span) */
}
