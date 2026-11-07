/* ROM6 0x95E2 FRAG_95E2 -- 8w.
 * Verified encoding: src/rom6/kernel/95e2_frag_95e2.asm (recombine MATCH).
 * ORIGIN 0x95E2
 * EXPECT: 76F8 20FD FFFF F0E8 8084 E801 F073 9667
 *
 * Intent: Shift store plus join. Writes -1 to cell 0x20FD; A-live-in <<= 8 logical (sftl) stored through live-in AR4; A = 1 is dead (b follows, noted); tail-enters FRAG_9667 (b 0x9667: has .asm, no C yet, forward extern). Bound 95E2-95E9.
 */
extern void frag_9667(void);

void frag_95E2(int a_live, int *par4)
{
    int a;
    *(volatile int *)0x20FD = -1;            /* st #-1 */
    a = a_live << 8;                             /* sftl a,8 (logical) */
    *par4 = a;                                   /* stl a,*ar4 */
    /* ld #1,a (dead, b follows) */
    frag_9667();                                 /* b 0x9667 tail */
}
