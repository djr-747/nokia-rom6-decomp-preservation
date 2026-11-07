/* ROM6 0x2ECD FRAG_2ECD -- 9w.
 * Verified encoding: src/rom6/boot/2ecd_frag_2ecd.asm (recombine MATCH).
 * ORIGIN 0x2ECD
 * EXPECT: F000 B041 4A11 8811 7710 0001 1081 8A11 F4E2
 *
 * Intent: Computed-table branch head (boot worker tail zone, entered
 * by the 2EBC bc retro-jump). A -= 20415 (add #-20415,a, 40-bit wrap
 * flagged). PSHM/POPM AR1 balanced around the lane (entry AR1
 * preserved, never read in-span; C-local LIFO per the 2D5E
 * precedent). AR1 = A-low (stlm a,ar1); AR0 = 1 (stm #1,ar0, no
 * in-span use, caller-observable, flagged not-carried). A = MEM[AR1]
 * sign-extended (ld *ar1,a -- computed-address load). bacc a via the
 * loaded cell (dark computed target; terminal-branch dark-sink per
 * the 5b26 precedent, emulator/trace ground truth).
 */
extern void dark_2ECD_target(int addr);              /* bacc a (MEM-loaded, dark) */

void frag_2ECD(long a_in)
{
    long a = a_in - 20415;                           /* add #-20415,a */
    int ar1_entry;                                   /* pshm ar1 (saved, never read) */
    int *ar1;
    int ar0;
    ar1 = (int *)(long)(a & 0xFFFF);                 /* stlm a,ar1 */
    ar0 = 1;                                         /* stm #1,ar0 */
    a = (long)*ar1;                                  /* ld *ar1,a */
    (void)ar0;                                       /* no in-span use */
    (void)ar1_entry;                                 /* popm ar1 */
    dark_2ECD_target((int)(a & 0xFFFF));             /* bacc a */
}
