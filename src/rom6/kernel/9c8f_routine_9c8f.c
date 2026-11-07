/* ROM6 0x9C8F ROUTINE_9C8F -- 10w.
 * Verified encoding: src/rom6/kernel/9c8f_routine_9c8f.asm (recombine MATCH).
 * ORIGIN 0x9C8F
 * EXPECT: F1C0 F330 00FF F300 DE54 8914 F0F8 F495 1C84 FC00
 *
 * Intent: XOR-fold plus table tap. B ^= A (live-ins); B low byte kept, bias -8620 added, AR4 = B; A >>= 8 (sftl, nop pad); A ^= *AR4; returns A.
 */
int routine_9C8F(int a_in, int b_in)
{
    int b = (a_in ^ b_in) & 255;                 /* xor a,b; and #255,b */
    int *ar4;
    int a;
    b += -8620;                                  /* add #-8620,b */
    ar4 = (int *)b;                              /* stlm b,ar4 */
    a = a_in >> 8;                               /* sftl a,-8; nop */
    a ^= *ar4;                                   /* xor *ar4,a */
    return a;                                    /* ret */
}
