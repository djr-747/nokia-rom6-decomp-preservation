/* ROM6 0x84CF SUB_84CF -- 50w.
 * Verified encoding: src/rom6/kernel/84cf_sub_84cf.asm (recombine MATCH).
 * ORIGIN 0x84CF
 * EXPECT: F074 0648 61F8 058F 000F FC30 68F8 0537 FF97 F274 2262 7712 0009 76F8 04FB 0000 7711 0210 E801 7311 0554 EC07 8091 E800 80F8 0556 80F8 0558 7711 0220 7311 0555 EC07 8091 68F8 0552 FFEF 69F8 0552 0400 76F8 0540 000C 62F8 3EAE 0003 F47E 80F8 0541 FC00
 *
 * Intent: measurement init plus fixed-point scale. Helper call;
 * if bits 0-3 of 0x58F set, clear bits 0/2/6 of 0x537
 * (andm #-105 under the rc tc conditional prefix). The calld
 * 0x2262 runs after its delay slots (AR2 seed, cell 0x4FB clear);
 * the AR2 seed belongs to the callee and has no C equivalent here.
 * Then: 8 cells of 1 at 528 with end pointer to 0x554, three zero
 * cells, 8 zero cells at 544 with end pointer to 0x555, status-bit
 * updates on 0x552, scale constant 12 to 0x540, and
 * *(0x541) = *(0x3EAE) * 3 / 4 (mpy #3 plus sfta -2; the source is
 * a nonnegative tune parameter, so the shift matches division).
 */
extern void helper_0648(void);
extern void sub_2262(void);

void sub_84CF_init(void)
{
    int i, *p;
    helper_0648();                                /* call 0x648 */
    if (*(volatile int *)0x58F & 15)              /* bitf, rc tc */
        *(volatile int *)0x537 &= ~104;           /* andm #-105 */
    *(volatile int *)0x4FB = 0;                    /* calld delay slot */
    sub_2262();                                   /* calld 0x2262 */
    p = (int *)528;                               /* stm #528,ar1 */
    *(volatile int *)0x554 = (int)p;              /* mvmd ar1,0x554 */
    for (i = 0; i < 8; i++)                       /* ld #1, rpt #7 */
        *p++ = 1;                                 /* stl a,*ar1+ */
    *(volatile int *)0x556 = 0;                   /* st */
    *(volatile int *)0x558 = 0;                   /* st */
    p = (int *)544;                               /* stm #544,ar1 */
    *(volatile int *)0x555 = (int)p;              /* mvmd ar1,0x555 */
    for (i = 0; i < 8; i++)                       /* ld #0, rpt #7 */
        *p++ = 0;                                 /* stl a,*ar1+ */
    *(volatile int *)0x552 &= ~16;                /* andm #-17 */
    *(volatile int *)0x552 |= 1024;               /* orm #1024 */
    *(volatile int *)0x540 = 12;                  /* st #12 */
    *(volatile int *)0x541 =
        (*(volatile int *)0x3EAE * 3) / 4;        /* mpy #3, sfta -2 */
    /* ret */
}
