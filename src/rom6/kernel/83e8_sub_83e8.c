/* ROM6 0x83E8 SUB_83E8 -- 23w.
 * Verified encoding: src/rom6/kernel/83e8_sub_83e8.asm (recombine MATCH).
 * ORIGIN 0x83E8
 * EXPECT: 7716 B194 F274 7F55 770E FFFF 7716 B174 F274 7F95 770E FFF3 F274 7FC6 7712 2A84 76F8 2630 0000 69F8 2A87 0600 FC00
 *
 * Intent: Triple-calld launcher D. Same shape as SUB_838C with AR6 presets -20076/-20108 and T presets -1/-13; 0x7FC6 with AR2 = 10884; clears cell 0x2630; sets bits 8-9 of cell 0x2A87; returns.
 */
extern void sub_7F55(void);
extern void sub_7F95(void);
extern void sub_7FC6(void);

static int *G_AR6;
static int G_T;
static int *G_AR2;

void sub_83E8(void)
{
    G_AR6 = (int *)-20076;                       /* stm #-20076,ar6 */
    G_T = -1;                                    /* calld delay slot */
    sub_7F55();                                  /* calld 0x7f55 */
    G_AR6 = (int *)-20108;                       /* stm #-20108,ar6 */
    G_T = -13;                                   /* calld delay slot */
    sub_7F95();                                  /* calld 0x7f95 */
    G_AR2 = (int *)10884;                        /* calld delay slot */
    sub_7FC6();                                  /* calld 0x7fc6 */
    *(volatile int *)0x2630 = 0;             /* st #0 */
    *(volatile int *)0x2A87 |= 1536;         /* orm #1536 */
    /* ret */
}
