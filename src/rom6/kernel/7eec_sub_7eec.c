/* ROM6 0x7EEC SUB_7EEC -- 48w four-phase clock lanes.
 * Verified encoding: src/rom6/kernel/7eec_sub_7eec.asm (recombine MATCH).
 * ORIGIN 0x7EEC
 * EXPECT: 770E 0000 F274 7F55 7716 B163 770E FFFC F273 7F95 7716 B17C 770E FFFF F274 7F55 7716 B194 770E FFFB F273 7F95 7716 B174 770E FFFE F274 7F55 7716 B18C 770E FFFA F273 7F95 7716 B16C 770E FFFD F274 7F55 7716 B184 770E FFF9 F273 7F95 7716 B164
 *
 * Intent: Same stm/calld/bd lane shape as 7EBE (wave-12
 * split), four phases. Each lane: T = T1 (stm,
 * hardware, dark call may read, flagged); the calld
 * delay pair (AR6 = M1, T = T2) runs first, then dark
 * sub_7F55; the bd delay pair (AR6 = M2, T = T3) runs
 * first, then tail-enters frag_7F95 (joins
 * sub32_7F95). Phases (T1 / call M1,T2 / exit M2,T3):
 * 7EEC: 0 / -20125,-4 / -20100,-1; 7EF8: -1 /
 * -20076,-5 / -20108,-2; 7F04: -2 / -20084,-6 /
 * -20116,-3; 7F10: -3 / -20092,-7 / -20124 (T holds
 * -7). Lane entries per TRACE 7EEC-7F1A heads
 * (HYPOTHESIS per lane, flagged). AR6 modeled as a
 * voided local per 7ebe (dark callee may read).
 * EXPECT from the image.
 */
extern void sub_7F55(void);  /* dark, no symbol per 7ebe */
extern void frag_7F95(void); /* joins sub32_7f95; see docs/evidence/extern-triage.md */

void sub_7EEC(void)
{
    int *ar6;

    /* stm #0,t (T = 0, hardware) */
    ar6 = (int *)(long)-20125;                             /* calld delay: stm (runs first) */
    (void)ar6;                                             /* dark 7F55 may read (flagged) */
    sub_7F55();                                            /* calld 0x7f55 */
    ar6 = (int *)(long)-20100;                             /* bd delay: stm (runs first) */
    (void)ar6;                                             /* dark 7F95 may read (flagged) */
    frag_7F95();                                           /* bd 0x7f95 (tail) */
}

void lane_7EF8(void)
{
    int *ar6;

    /* stm #-1,t (T = -1, hardware) */
    ar6 = (int *)(long)-20076;                             /* calld delay: stm */
    (void)ar6;
    sub_7F55();                                            /* calld 0x7f55 */
    ar6 = (int *)(long)-20108;                             /* bd delay: stm */
    (void)ar6;
    frag_7F95();                                           /* bd 0x7f95 (tail) */
}

void lane_7F04(void)
{
    int *ar6;

    /* stm #-2,t (T = -2, hardware) */
    ar6 = (int *)(long)-20084;                             /* calld delay: stm */
    (void)ar6;
    sub_7F55();                                            /* calld 0x7f55 */
    ar6 = (int *)(long)-20116;                             /* bd delay: stm */
    (void)ar6;
    frag_7F95();                                           /* bd 0x7f95 (tail) */
}

void lane_7F10(void)
{
    int *ar6;

    /* stm #-3,t (T = -3, hardware) */
    ar6 = (int *)(long)-20092;                             /* calld delay: stm */
    (void)ar6;
    sub_7F55();                                            /* calld 0x7f55 */
    ar6 = (int *)(long)-20124;                             /* bd delay: stm (T holds -7) */
    (void)ar6;
    frag_7F95();                                           /* bd 0x7f95 (tail) */
}
