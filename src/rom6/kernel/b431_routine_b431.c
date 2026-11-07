/* ROM6 0xB431 ROUTINE_B431 -- 48w mode-cell switch with block copy.
 * Verified encoding: src/rom6/kernel/b431_routine_b431.asm (recombine MATCH).
 * ORIGIN 0xB431
 * EXPECT: F074 05A8 71F8 2639 34C9 60F8 34BF 0001 F830 B453 60F8 34BF 0004 F830 B453 7712 3490 1182 F330 FFF0 8182 F074 B39E 60F8 34BF 0003 F820 B460 7713 2A84 7714 0492 EC07 E59A 7712 3490 1182 F330 FFF0 F340 0001 8182 71F8 34C9 2639 F074 B39E FC00
 *
 * Intent: Runs dark sub_05A8 (call, low-zone, flagged).
 * Cell 0x34C9 = cell 0x2639 (mvdk, dmad = source).
 * Cell 0x34BF == 1 or == 4 skips to the set-bit lane
 * (cmpm, oracle TC = equality; bc tc). Else AR2 =
 * 13456; B = *(AR2) & -16 (and #-16,b: src/dst B per
 * oracle layout bits 9/8); *(AR2) = B-low; runs
 * routine_B39E; cell 0x34BF != 3 returns (bc ntc to
 * the ret). Else AR3 = 10884, AR4 = 1170; 8x *(AR4++)
 * = *(AR3++) (rpt #7 + mvdd). Set-bit lane (B453):
 * AR2 = 13456; B = *(AR2) & -16; B |= 1 (or #1,b);
 * *(AR2) = B-low; cell 0x2639 = cell 0x34C9 (mvdk
 * restore); runs routine_B39E; return.
 * EXPECT from the image.
 */
extern void sub_05A8(void); /* dark, no symbol per b358 */
extern void routine_B39E(void);

void routine_B431(void)
{
    long b;
    int *ar2;
    int *ar3;
    int *ar4;
    int i;

    sub_05A8();                                            /* call 0x5a8 */
    *(volatile int *)0x34C9 = *(volatile int *)0x2639;    /* mvdk *(0x2639),0x34c9 */
    if (*(volatile int *)0x34BF == 1 ||                    /* cmpm; bc tc */
        *(volatile int *)0x34BF == 4)                      /* cmpm; bc tc */
        goto setbit;
    ar2 = (int *)(long)13456;                              /* stm #13456,ar2 */
    b = (long)*ar2;                                        /* ld *ar2,b */
    b &= -16L;                                             /* and #-16,b */
    *ar2 = (int)(b & 0xFFFFL);                             /* stl b,*ar2 */
    routine_B39E();                                        /* call 0xb39e */
    if (*(volatile int *)0x34BF != 3)                      /* cmpm; bc ntc */
        return;                                            /* b 0xb460 (ret) */
    ar3 = (int *)(long)10884;                              /* stm #10884,ar3 */
    ar4 = (int *)(long)1170;                               /* stm #1170,ar4 */
    for (i = 0; i < 8; i++)                                /* rpt #7 */
        *ar4++ = *ar3++;                                   /* mvdd *ar3+,*ar4+ */
setbit:
    ar2 = (int *)(long)13456;                              /* stm #13456,ar2 */
    b = (long)*ar2;                                        /* ld *ar2,b */
    b &= -16L;                                             /* and #-16,b */
    b |= 1L;                                               /* or #1,b */
    *ar2 = (int)(b & 0xFFFFL);                             /* stl b,*ar2 */
    *(volatile int *)0x2639 = *(volatile int *)0x34C9;    /* mvdk *(0x34c9),0x2639 */
    routine_B39E();                                        /* call 0xb39e */
    /* ret */
}
