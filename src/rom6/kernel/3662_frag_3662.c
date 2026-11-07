/* ROM6 0x3662 FRAG_3662 -- 18w.
 * Verified encoding: src/rom6/kernel/3662_frag_3662.asm (recombine MATCH).
 * ORIGIN 0x3662
 * EXPECT: F340 0100 8184 4815 8090 6183 0001 FC20 6183 0008 F820 3671 69F8 054F 0200 4816 8080 FC00
 *
 * Intent: Flag-cell copy with in-span gate. B = live-in OR 256, stored through live-in AR4; A = AR5 (as value), stored through live-in AR0++; bit 0 of live-in *AR3 tested (bitf, TC on any-bit); clear skips the next test (rc ntc keeps that TC); bit 8 clear jumps to 3671 in-span (bc 0x3671,ntc, forward extern, no C binding yet); else sets bit 9 of cell 0x54F, A = AR6 stored through AR0, return.
 */
extern void frag_3671_entry(void); /* 3662_frag_3662 interior @+15; see docs/evidence/extern-triage.md */
void frag_3662(int b_live, int *par4, int *par5, int **ppar0, int *par3, int *par6)
{
    int a;
    int tc;
    int b = b_live | 256;                        /* or #256,b */
    *par4 = b;                                   /* stl b,*ar4 */
    a = (int)par5;                               /* ldm ar5,a */
    **ppar0 = a; (*ppar0)++;                     /* stl a,*ar0+ */
    tc = (*par3 & 1) != 0;                       /* bitf *ar3,#1 */
    if (tc)                                      /* rc ntc */
        tc = (*par3 & 8) != 0;                   /* bitf *ar3,#8 */
    if (!tc) {                                   /* bc 0x3671,ntc */
        frag_3671_entry();                       /* in-span, unbound */
        return;
    }
    *(volatile int *)0x54F |= 512;           /* orm #512 */
    **ppar0 = (int)par6;                         /* ldm ar6,a; stl a,*ar0 */
    /* ret */
}
