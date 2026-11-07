/* ROM6 0x95B8 FRAG_95B8 -- 7w.
 * Verified encoding: src/rom6/kernel/95b8_frag_95b8.asm (recombine MATCH).
 * ORIGIN 0x95B8
 * EXPECT: 8084 E801 F584 F273 9667 81F8 20FD
 *
 * Intent: FRAG_95B8 negate-and-store tail (7w). *AR4-entry = A-live-in (stl, AR4 threaded as param, unstepped); A = 1; B = -A (NEG, 40-bit narrowing noted); delayed tail into C FRAG_9667 (bd, C-bound) with cell 0x20FD = B low in the slot (always runs).
 */
extern void frag_9667(void);

void frag_95B8(int a_live, int *par4)
{
    int a = a_live;
    int b;
    *par4 = a & 0xFFFF;                            /* stl a,*ar4 */
    a = 1;                                         /* ld #1,a */
    b = -a;                                        /* neg a,b */
    *(volatile int *)0x20FD = b & 0xFFFF;      /* bd delay slot */
    frag_9667();                                   /* bd 0x9667 tail */
}
