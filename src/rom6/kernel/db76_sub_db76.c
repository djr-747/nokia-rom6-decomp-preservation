/* ROM6 0xDB76 SUB_DB76 -- 9w.
 * Verified encoding: src/rom6/kernel/db76_sub_db76.asm (recombine MATCH).
 * ORIGIN 0xDB76
 * EXPECT: 7210 0A5B 605B 001B 80E0 0AB2 6B5B 0001 FE00 FD30
 *
 * Intent: Indexed store plus tick. AR0 = cell 0xA5B; compares cell 0x5B against 27 (cmpm, TC unused in span); stores live-in A at AR0 + 0xAB2; ticks cell 0x5B. Delayed return whose two delay slots fall through into the next module words (out of span, documented like FRAG_9B6F).
 */
void sub_DB76(int a_in)
{
    int *ar0 = (int *)(*(volatile int *)0xA5B); /* mvdm 0xa5b,ar0 */
    /* cmpm 0x5b,#27: TC set on equal (ti-c54x op_cmpm), unused here */
    *(ar0 + 0xAB2) = a_in;                      /* stl a,*ar0(0xab2) */
    *(volatile int *)0x5B += 1;                /* addm #1,0x5b */
    /* retd: delay slots execute following module words (out of span) */
}
