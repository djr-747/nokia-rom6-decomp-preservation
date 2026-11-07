/* ROM6 0x5336 DISPATCH_SLED_A -- 31w.
 * Verified encoding: src/rom6/rf/5336_dispatch_sled_a.asm (recombine MATCH).
 * ORIGIN 0x5336
 * EXPECT: 76F8 056F 00B0 7711 263C E820 8091 8081 60F8 250F 0030 FA20 5355 7712 2546 6082 0050 F820 5355 76F8 0574 0001 7682 0051 68F8 2549 FFEF 7681 0008 F073 5371
 *
 * Intent: Branch-entered dispatch sled fragment (5282-family; zero
 * F074 callers). MEM[0x56F] = 176 (st). AR1 = 9788, A = 32 (stm/ld
 * locals; AR1 never leaves, not carried). MEM[9788] = MEM[9789] =
 * 32 (stl pair). TC = (*(0x250F) == 48) (cmpm, 3691 precedent).
 * bcd 0x5355,ntc: the 2-word stm delay fills the window and always
 * runs (AR2 = 9542; 520C/5d38 word-count rule), then NTC-taken jumps
 * (taken path skips the delay-cmpm). Fall path runs cmpm *AR2,#80 as
 * code (TC = (*AR2 == 80)), NTC exits via bc 0x5355,ntc (C:
 * frag_5355). Else MEM[0x574] = 1, MEM[AR2=9542] = 81 (st pair),
 * MEM[0x2549] &= ~17 (andm #-17), MEM[AR1=9789] = 8 (st), tail into
 * the 5362 span at 5371 (b 0x5371; mid-span entry, frag_5371 per the
 * 5371 precedent).
 */
extern void frag_5355(void);                         /* C: 5355_dispatch_sled_a */
extern void frag_5371(void);                         /* mid-span entry */

void frag_5336(void)
{
    long a = 32;                                     /* ld #32,a */
    int *ar1;
    int *ar2;
    int tc;
    *(volatile int *)0x56F = 176;                    /* st #176,*(0x56f) */
    ar1 = (int *)(long)9788;                         /* stm #9788,ar1 */
    *ar1++ = (int)(a & 0xFFFF);                      /* stl a,*ar1+ */
    *ar1 = (int)(a & 0xFFFF);                        /* stl a,*ar1 */
    tc = (*(volatile int *)0x250F == 48);            /* cmpm *(0x250f),#48 */
    ar2 = (int *)(long)9542;                         /* bcd delay: stm (always runs) */
    if (!tc) {                                       /* bcd 0x5355,ntc taken */
        frag_5355();
        return;
    }
    tc = (*ar2 == 80);                               /* cmpm *ar2,#80 (fall path) */
    if (!tc) {                                       /* bc 0x5355,ntc */
        frag_5355();
        return;
    }
    *(volatile int *)0x574 = 1;                      /* st #1,*(0x574) */
    *ar2 = 81;                                       /* st #81,*ar2 */
    *(volatile int *)0x2549 &= -17;                  /* andm #-17,*(0x2549) */
    *ar1 = 8;                                        /* st #8,*ar1 */
    frag_5371();                                     /* b 0x5371 */
}
