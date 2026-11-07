/* ROM6 0x8675 FRAG_8675 -- 9w.
 * Verified encoding: src/rom6/kernel/8675_span_head_8675.asm (recombine MATCH).
 * ORIGIN 0x8675
 * EXPECT: F074 0592 76F8 10FE 0017 E800 FE00 80F8 10FF
 *
 * Intent: SPAN_HEAD_8675 constant store with delayed return (9w). Runs dark SUB_0592; cell 0x10FE = 23; A = 0; cell 0x10FF = A low in the retd delay slot (always runs); returns. A dies, void.
 */
extern void sub_0592(void);

void frag_8675(void)
{
    int a;
    sub_0592();                                    /* call 0x592 */
    *(volatile int *)0x10FE = 23;              /* st */
    a = 0;                                         /* ld #0,a */
    *(volatile int *)0x10FF = a & 0xFFFF;      /* retd delay slot */
    /* retd: return */
}
