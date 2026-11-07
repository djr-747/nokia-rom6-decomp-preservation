/* ROM6 0x83FF SUB_83FF -- 20w.
 * Verified encoding: src/rom6/kernel/83ff_sub_83ff.asm (recombine MATCH).
 * ORIGIN 0x83FF
 * EXPECT: 7716 B163 F274 7F55 770E 0000 7716 B17C F274 7F95 770E FFF4 F274 7FC6 7712 2A84 69F8 2A87 0600 FC00
 *
 * Intent: Triple-calld launcher C. Same shape as SUB_838C with AR6 presets -20125/-20100 and T presets 0/-12; 0x7FC6 with AR2 = 10884; sets bits 8-9 of cell 0x2A87, returns.
 */
extern void sub_7F55(void); /* joins 7f55_sub32_7f55; see docs/evidence/extern-triage.md */
extern void sub_7F95(void); /* joins 7f95_sub32_7f95; see docs/evidence/extern-triage.md */
extern void sub_7FC6(void);

static int *G_AR6;
static int G_T;
static int *G_AR2;

void sub_83FF(void)
{
    G_AR6 = (int *)-20125;                       /* stm #-20125,ar6 */
    G_T = 0;                                     /* calld delay slot */
    sub_7F55();                                  /* calld 0x7f55 */
    G_AR6 = (int *)-20100;                       /* stm #-20100,ar6 */
    G_T = -12;                                   /* calld delay slot */
    sub_7F95();                                  /* calld 0x7f95 */
    G_AR2 = (int *)10884;                        /* calld delay slot */
    sub_7FC6();                                  /* calld 0x7fc6 */
    *(volatile int *)0x2A87 |= 1536;         /* orm #1536 */
    /* ret */
}
