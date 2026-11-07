/* ROM6 0x83A0 SUB_83A0 -- 20w.
 * Verified encoding: src/rom6/kernel/83a0_sub_83a0.asm (recombine MATCH).
 * ORIGIN 0x83A0
 * EXPECT: 7716 B18C F274 7F55 770E FFFE 7716 B16C F274 7F95 770E FFFA F274 7FC6 7712 2A84 69F8 2A87 0600 FC00
 *
 * Intent: Triple-calld launcher B. Same shape as SUB_838C with AR6 presets -20084/-20116 and T presets -2/-6; 0x7FC6 with AR2 = 10884; sets bits 8-9 of cell 0x2A87, returns.
 */
extern void sub_7F55(void);
extern void sub_7F95(void);
extern void sub_7FC6(void);

static int *G_AR6;
static int G_T;
static int *G_AR2;

void sub_83A0(void)
{
    G_AR6 = (int *)-20084;                       /* stm #-20084,ar6 */
    G_T = -2;                                    /* calld delay slot */
    sub_7F55();                                  /* calld 0x7f55 */
    G_AR6 = (int *)-20116;                       /* stm #-20116,ar6 */
    G_T = -6;                                    /* calld delay slot */
    sub_7F95();                                  /* calld 0x7f95 */
    G_AR2 = (int *)10884;                        /* calld delay slot */
    sub_7FC6();                                  /* calld 0x7fc6 */
    *(volatile int *)0x2A87 |= 1536;         /* orm #1536 */
    /* ret */
}
