/* ROM6 0x7EBC BD_7EBE -- 10w (span 7EBC-7EC5, single entry; overlap-split wave-12).
 * Verified encoding: src/rom6/kernel/7ebe_bd_7ebe.asm (recombine MATCH).
 * ORIGIN 0x7EBC
 * EXPECT: 770E 0000 F274 7F55 7716 B163 770E FFF4 F273 7F95
 *
 * Intent: Delayed-call-and-branch tail (split out of the 7EA6
 * superset draft). Entry frag_7EBE (HYPOTHESIS: no in-span
 * caller; direct-entry shape, bacc-lane fall-through
 * possible); no live-ins (T/AR6/BRC set in-span; A/B unread
 * -- the dark call clobbers both); void. T = 0 (stm,
 * hardware); delayed call to dark SUB_7F55 (calld, forward
 * extern void) with its single complete 2-word delay stm
 * AR6 = -20125 running first (WORD-count clean); T = -12 and
 * BRC = -12 (stm pair; dark callee may read either, flagged);
 * unconditional delayed branch tail-entering dark 0x7F95
 * (bd, forward extern void; its 2 delay words live in the
 * following span and execute there -- cross-span delay abut
 * per the D581 precedent). A/B/ARs dead after (void).
 */
extern void sub_7F55(void);                              /* dark, no symbol */
extern void frag_7F95(void);                             /* dark (bd target) */

void frag_7EBE(void)
{
    int *ar6;
    /* stm #0,t (T = 0, hardware; dark call may read, flagged) */
    ar6 = (int *)(long)-20125;                           /* calld delay: stm (complete) */
    (void)ar6;                                           /* dark 7F55 may read (flagged) */
    sub_7F55();                                          /* calld 0x7f55 (dark) */
    /* stm #-12,t; stm #-12,brc (hardware; dark lane may read, flagged) */
    /* bd 0x7f95 (delays in following span, executed, abut) */
    frag_7F95();                                         /* bd tail */
}
