/* ROM6 ORIGIN 0x51CC (4w): HIT_51CC -- lane-hit tail.
 * Verified encoding: src/rom6/kernel/51cc_hit_51cc.asm (recombine MATCH).
 * ORIGIN 0x51CC
 * EXPECT: E900 FE00 6884 FEFF
 *
 * Intent: Hit path shared by LANE_36F/LANE_375 (in-span 51AF-taken,
 * 51C8-fall), FRAG_51D0 (51D2-taken) and ROUTINE_516A (5183/5188).
 * B = 0 (ld #0,b), return-delayed with *AR4 &= ~257 (andm #-257 = 0xFEFF
 * clears bit 8, delay slot) then return. B-out modeled as int return,
 * matching the frag_51D0 cluster convention; AR4 is caller-live, param.
 * Bound 51CC-51CF (retd + andm delay). No own callers in-image beyond
 * the five entries above (prom.lst byte-verified).
 */
int hit_51CC(int *par4)
{
    *par4 &= 0xFEFF;                                      /* andm (delay) */
    return 0;                                             /* ld #0,b; retd */
}
