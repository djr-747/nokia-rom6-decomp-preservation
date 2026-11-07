/* ROM6 0x838C SUB_838C -- 20w.
 * Verified encoding: src/rom6/kernel/838c_sub_838c.asm (recombine MATCH).
 * ORIGIN 0x838C
 * EXPECT: 7716 B184 F274 7F55 770E FFFD 7716 B164 F274 7F95 770E FFF9 F274 7FC6 7712 2A84 69F8 2A87 0600 FC00
 *
 * Intent: Triple-calld launcher A. AR6 = -20092 feeds 0x7F55 with T = -3 in the calld delay slot (executes first); AR6 = -20124 feeds 0x7F95 with T = -7; 0x7FC6 runs with AR2 = 10884 preset in its delay slot; sets bits 8-9 of cell 0x2A87 (orm #1536), returns.
 */
extern void sub_7F55(void); /* joins 7f55_sub32_7f55; see docs/evidence/extern-triage.md */
extern void sub_7F95(void); /* joins 7f95_sub32_7f95; see docs/evidence/extern-triage.md */
extern void sub_7FC6(void);

static int *G_AR6;
static int G_T;
static int *G_AR2;

void sub_838C(void)
{
    G_AR6 = (int *)-20092;                       /* stm #-20092,ar6 */
    G_T = -3;                                    /* calld delay slot */
    sub_7F55();                                  /* calld 0x7f55 */
    G_AR6 = (int *)-20124;                       /* stm #-20124,ar6 */
    G_T = -7;                                    /* calld delay slot */
    sub_7F95();                                  /* calld 0x7f95 */
    G_AR2 = (int *)10884;                        /* calld delay slot */
    sub_7FC6();                                  /* calld 0x7fc6 */
    *(volatile int *)0x2A87 |= 1536;         /* orm #1536 */
    /* ret */
}
