/* ROM6 0xDB81 ROUTINE_DB81 -- 11w.
 * Verified encoding: src/rom6/kernel/db81_routine_db81.asm (recombine MATCH).
 * ORIGIN 0xDB81
 * EXPECT: 7210 0A63 6063 001B 80E0 0B14 6B63 0001 FE00 FD30 8263
 *
 * Intent: Compare-and-bump cell with indexed store. AR0 = *(0xA63)
 * (mvdm, full 16-bit address); TC = (cell0x63 == 27) (cmpm); store A-low
 * at AR0 + 0xB14 (stl, 5c34 address-arithmetic precedent); cell0x63++;
 * retd delays: xc 1,tc skips the STH when equal, else cell0x63 = A-high
 * (sth: (a >> 16) & 0xFFFF per the 3a8e/397b precedents); far return.
 * A is caller-live as long (32-bit; 40-bit guard bits unmodeled,
 * flagged). Cells absolute per the da40 precedent (DP = 0 assumed for
 * the DP-relative cells, flagged). Bound DB81-DB8B.
 */
void routine_DB81(long a_live)
{
    int ar0 = *(volatile int *)0xA63;                /* mvdm 0xa63,ar0 */
    int cell63 = *(volatile int *)0x63;
    int tc = (cell63 == 27);                         /* cmpm 0x63,#27 */
    *(volatile int *)(ar0 + 0xB14) = (int)(a_live & 0xFFFF); /* stl a,*ar0(0xb14) */
    *(volatile int *)0x63 = cell63 + 1;              /* addm #1,0x63 */
    if (tc)                                          /* retd delay: xc 1,tc (taken runs sth) */
        *(volatile int *)0x63 = (int)((a_live >> 16) & 0xFFFF); /* sth a,0x63 */
    /* retd */
}
