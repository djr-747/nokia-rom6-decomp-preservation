/* ROM6 0x2A73 FRAG_2A73 -- 23w.
 * Verified encoding: src/rom6/boot/2a73_frag_2a73.asm (recombine MATCH).
 * ORIGIN 0x2A73
 * EXPECT: 7212 265E 7213 2660 6D92 F495 7593 0031 F495 F495 7593 0032 7313 2660 F495 7592 0004 EC0B F495 F273 2979 7312 265E
 *
 * Intent: Port 49/50/4 sequence with delayed branch. AR2 = cell 0x265E, AR3 = cell 0x2660 (mvdm pair, locals); AR2++; *AR3++ out to ports 49 then 50 (portw pair); cell 0x2660 = AR3 (post-double-step); *AR2++ out to port 4; 12 idle cycles (rpt #11 nop); branch to dark 0x2979 (bd, forward extern) with cell 0x265E = AR2 in the delay slot (always runs, final AR2). 23w per .asm header (recombine MATCH).
 */
extern void port_write_49(int v);
extern void port_write_50(int v);
extern void port_write_4(int v);
extern void frag_2979(void);

void frag_2A73(void)
{
    int i;
    int *ar2 = (int *)(long)*(volatile int *)0x265E; /* mvdm */
    int *ar3 = (int *)(long)*(volatile int *)0x2660; /* mvdm */
    ar2++;                                           /* mar *ar2+ */
    /* nop */
    port_write_49(*ar3++);                           /* portw *ar3+,49 */
    /* nop; nop */
    port_write_50(*ar3++);                           /* portw *ar3+,50 */
    *(volatile int *)0x2660 = (int)(long)ar3;    /* mvmd ar3,0x2660 */
    /* nop */
    port_write_4(*ar2++);                            /* portw *ar2+,4 */
    for (i = 0; i < 12; i++) {}                      /* rpt #11; nop */
    *(volatile int *)0x265E = (int)(long)ar2;    /* bd delay (always runs) */
    frag_2979();                                     /* bd 0x2979 */
}
