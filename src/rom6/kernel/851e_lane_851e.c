/* ROM6 0x851E LANE_851E -- 11w.
 * Verified encoding: src/rom6/kernel/851e_lane_851e.asm (recombine MATCH).
 * ORIGIN 0x851E
 * EXPECT: 7712 B749 7715 30DC F074 8611 7716 B76D F074 853B FC00
 *
 * Intent: Copy-plus-fanout launcher (twin of the 8501 lane shape with the
 * 8529 copy half). AR2/AR5 presets (-18615/12508) feed the 0x8611 14-cell
 * copy (copy14_8611, 8529 mapping), then AR6 preset -18579 feeds the 0x853B
 * fanout driver (fanout26_853B, 8501 mapping: pp1/AR4 live-in). Covered only
 * by the deleted 8500-giant before. Mappings by convention (unverified),
 * flagged. Zero F074/F274 callers (lane entry by fall-through/abut,
 * unconfirmed), flagged.
 */
extern void copy14_8611(int *p2, int *p5);
extern void fanout26_853B(int **pp1, int *ar4, int *ar6);

static int *G_AR2;
static int *G_AR5;
static int *G_AR6;

void lane_851E(int **pp1_in, int *ar4_in)
{
    G_AR2 = (int *)-18615;                       /* stm #-18615,ar2 */
    G_AR5 = (int *)12508;                        /* stm #12508,ar5 */
    copy14_8611(G_AR2, G_AR5);                   /* call 0x8611 */
    G_AR6 = (int *)-18579;                       /* stm #-18579,ar6 */
    fanout26_853B(pp1_in, ar4_in, G_AR6);        /* call 0x853b */
    /* ret */
}
