/* ROM6 0xA4BA ROUTINE_A4BA -- 28w.
 * Verified encoding: src/rom6/kernel/a4ba_routine_a4ba.asm (recombine MATCH).
 * ORIGIN 0xA4BA
 * EXPECT: F074 0656 7712 262B 1082 FC45 F010 00F0 FC45 61F8 263A 0200 F820 A4CB 69F8 051E 0100 11F8 2639 F330 0002 68F8 2639 FFFD F074 7C57 FC00
 *
 * Intent: Cell test plus flag merge. Runs 0x656; A = cell 0x262B, zero returns early (rc aeq, exact skip); A -= 240, zero returns early (rc aeq); bit 9 of cell 0x263A clear jumps to the A4CB fragment (bc 0xa4cb,ntc: bytes ld/and/andm at target, forward extern, no C binding yet, per convention). Else sets bit 8 of cell 0x51E; B = cell 0x2639 AND 2 (dead, B unused after); clears low 2 bits of cell 0x2639; calls 0x7C57; return.
 */
extern void helper_0656(void);
extern void frag_A4CB(void);
extern void sub_7C57(void);

void routine_A4BA(void)
{
    int a;
    int b;
    helper_0656();                               /* call 0x656 */
    a = *(volatile int *)0x262B;             /* stm; ld *ar2,a */
    if (a == 0)                                  /* rc aeq */
        return;
    a -= 240;                                    /* sub #240,a */
    if (a == 0)                                  /* rc aeq */
        return;
    if ((*(volatile int *)0x263A & 512) == 0) {  /* bitf, bc ntc */
        frag_A4CB();                             /* away, unbound */
        return;
    }
    *(volatile int *)0x51E |= 256;           /* orm #256 */
    b = *(volatile int *)0x2639 & 2;         /* ld, and (dead) */
    (void)b;
    *(volatile int *)0x2639 &= -3;           /* andm #-3 */
    sub_7C57();                                  /* call 0x7c57 */
    /* ret */
}
