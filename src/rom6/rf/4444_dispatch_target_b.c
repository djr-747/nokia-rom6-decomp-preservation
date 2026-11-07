/* ROM6 0x4444 DISPATCH_TARGET_B -- 12w.
 * Verified encoding: src/rom6/rf/4444_dispatch_target_b.asm (recombine MATCH).
 * ORIGIN 0x4444
 * EXPECT: 4913 7715 052A EC02 7C95 4450 81F8 052B F074 052A 6D93 FC00
 *
 * Intent: Program-table broadcast plus call. B = AR3 (live-in, as value); AR5 = 1322; 3 copies (rpt #2) of program word 0x4450 (mvpd absolute: fixed program address, same word broadcast, no auto-increment evidenced) through AR5; cell 0x52B = B; call 0x52A; AR3++ (mar), return.
 */
extern int prom_read_word(int prog_addr);      /* mvpd: program read */
extern void sub_052A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void dispatch_target_B_4444(int *par3, int *par4)
{
    int i;
    int b = (int)par3;                           /* ldm ar3,b */
    int *ar5 = (int *)1322;                      /* stm #1322,ar5 */
    (void)par4;
    for (i = 0; i < 3; i++)                       /* rpt #2 */
        *ar5++ = prom_read_word(0x4450);         /* mvpd 0x4450,*ar5+ */
    *(volatile int *)0x52B = b;              /* stl b,*(0x52b) */
    sub_052A();                                  /* call 0x52a */
    par3++;                                      /* mar *ar3+ */
    /* ret */
}
