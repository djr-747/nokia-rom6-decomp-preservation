/* ROM6 0x9233 FRAG_9233 -- 24w.
 * Verified encoding: src/rom6/kernel/9233_frag_9233.asm (recombine MATCH).
 * ORIGIN 0x9233
 * EXPECT: 7313 0060 7710 0020 7713 2F60 7715 2F00 7714 2F40 7719 0080 F020 C001 EC3F 8095 7715 2F00 E800 8085 7717 304D 7716 2F80 FC00
 *
 * Intent: Block preset plus fills. Cell 0x60 = AR3 (mvmd MMR to data, AR3 live-in); AR0 = 32 (index step, unused in span, noted); AR3 = 12128, AR5 = 12032, AR4 = 12096; BK = 128 (circular-buffer size, hardware state, no C form); A = -16383 with 64 stores (rpt #63) through AR5++; AR5 = 12032, A = 0, one store; AR7 = 12365, AR6 = 12160; return.
 */
void frag_9233(int *par3)
{
    int i;
    int *ar5;
    *(volatile int *)0x60 = (int)par3;       /* mvmd ar3,0x60 */
    /* stm #32,ar0 (index step, unused in span) */
    /* stm #12128,ar3; stm #12096,ar4 (unused) */
    /* stm #128,bk (circular size, hardware state) */
    ar5 = (int *)12032;                          /* stm #12032,ar5 */
    for (i = 0; i < 64; i++)                     /* ld #-16383,a; rpt #63 */
        *ar5++ = -16383;                         /* stl a,*ar5+ */
    ar5 = (int *)12032;                          /* stm #12032,ar5 */
    *ar5 = 0;                                    /* ld #0,a; stl a,*ar5 */
    /* stm #12365,ar7; stm #12160,ar6; ret */
}
