/* ROM6 0x7EC6 DELAY_ABUT_7EC6 -- 38w.
 * Verified encoding: src/rom6/kernel/7ec6_delay_abut_7ec6.asm (recombine MATCH).
 * ORIGIN 0x7EC6
 * EXPECT: 7716 B17C 770E FFFF F274 7F55 7716 B194 770E FFF3 F273 7F95 7716 B174 770E FFFE F274 7F55 7716 B18C 770E FFF2 F273 7F95 7716 B16C 770E FFFD F274 7F55 7716 B184 770E FFF1 F273 7F95 7716 B164
 *
 * Intent: Cross-span branch-delay abut then dead lanes. Words 7EC6-7EC7 (one 2-word stm) run once as
 * the delay slot of the previous span 7EBE bd 0x7F95 (oracle: two delay WORDS; D581 precedent -- the delay
 * executes, then the bd takes effect); modeled as the delay stmt tail-joining frag_7F95 (dark).
 * Words 7EC8-7EEB repeat the stm/calld/bd lane shapes but sit past the unconditional bd with no entries
 * (unconfirmed) -- dead per 5886, preserved in asm, not modeled. No caller-live regs. Entry: post-bd head
 * (delay of 7EBE).
 */
extern void frag_7F95(void); /* joins 7f95_sub32_7f95; see docs/evidence/extern-triage.md */

void frag_7EC6(void)
{
    int *ar6;

    ar6 = (int *)(long)-20100;                             /* bd delay: stm (runs) */
    (void)ar6;                                             /* dark 7F95 may read */
    frag_7F95();                                           /* bd 0x7f95 taken (tail) */
    /* dead 7EC8-7EEB (past unconditional bd, not modeled) */
}
