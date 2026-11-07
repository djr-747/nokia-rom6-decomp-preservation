/* ROM6 0x8508 LANE_8508 -- 11w.
 * Verified encoding: src/rom6/kernel/8508_lane_8508.asm (recombine MATCH).
 * ORIGIN 0x8508
 * EXPECT: 7712 B74F 7715 30DC F074 8611 7716 B761 F074 8555 FC00
 *
 * Intent: Copy-plus-fanout launcher (twin of the 8513 lane, AR2 preset
 * differs: -18609 here). AR2/AR5 presets (-18609/12508) feed the 0x8611
 * 14-cell copy (copy14_8611), then AR6 preset -18591 feeds the 0x8555 fanout
 * (fanout_8555). Callee register mapping by the 8529 convention
 * (unverified); pp1 is live-in. Zero F074/F274 callers (lane entry by
 * fall-through/abut, unconfirmed), flagged.
 */
extern void copy14_8611(int *p2, int *p5);
extern void fanout_8555(int **pp5, int **pp1, int *ar6);

static int *G_AR2;
static int *G_AR5;
static int *G_AR6;

void lane_8508(int **pp1_in)
{
    G_AR2 = (int *)-18609;                       /* stm #-18609,ar2 */
    G_AR5 = (int *)12508;                        /* stm #12508,ar5 */
    copy14_8611(G_AR2, G_AR5);                   /* call 0x8611 */
    G_AR6 = (int *)-18591;                       /* stm #-18591,ar6 */
    fanout_8555(&G_AR5, pp1_in, G_AR6);          /* call 0x8555 */
    /* ret */
}
