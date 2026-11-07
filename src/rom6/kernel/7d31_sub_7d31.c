/* ROM6 0x7D31 SUB_7D31 -- 47w mode-gated zero-init lane.
 * Verified encoding: src/rom6/kernel/7d31_sub_7d31.asm (recombine MATCH).
 * ORIGIN 0x7D31
 * EXPECT: 76F8 058C 0004 E800 80F8 264F 80F8 2650 80F8 2631 68F8 2639 0FAF 1182 F330 00F0 60F8 000B 00C0 F830 7D48 80F8 2579 80F8 259F 80F8 25A0 80F8 25C1 60F8 2510 00C0 F830 7D57 60F8 2510 00B1 FC20 80F8 2630 76F8 264F FFFF 68F8 2EF9 013F FC00
 *
 * Intent: Cell 0x58C = 4; A = 0; cells 0x264F/0x2650/
 * 0x2631 = 0; cell 0x2639 &= 4015. B = *(AR2 entry,
 * dark) & 240 (B flag-dead; no use). If cell 0xB ==
 * 192, skip the 0x2579/0x259F/0x25A0/0x25C1 zero block
 * (cmpm sets TC = (Smem == lk) per oracle
 * op_cmpm_smem_lk; bc tc). If cell 0x2510 == 192, skip
 * to the tail; else if cell 0x2510 != 177, return (rc
 * ntc). Tail: cell 0x2630 = 0; cell 0x264F = -1;
 * cell 0x2EF9 &= 319; return. Entry AR2 caller-live
 * (flagged); out cells.
 * EXPECT from the image.
 */
void sub_7D31(int *ar2_in)
{
    long a;
    long b;
    int *ar2 = ar2_in;   /* entry AR2 (live-in, caller-live, flagged) */

    *(volatile int *)0x58C = 4;                            /* st #4,*(0x58c) */
    a = 0L;                                                /* ld #0,a */
    *(volatile int *)0x264F = (int)a;                      /* stl a,*(0x264f) */
    *(volatile int *)0x2650 = (int)a;                      /* stl a,*(0x2650) */
    *(volatile int *)0x2631 = (int)a;                      /* stl a,*(0x2631) */
    *(volatile int *)0x2639 &= 4015;                       /* andm #4015,*(0x2639) */
    b = (long)*ar2;                                        /* ld *ar2,b */
    b &= 240L;                                             /* and #240,b (flag-dead) */
    if (*(volatile int *)0xB != 192) {                      /* cmpm *(0xb),#192; bc tc */
        *(volatile int *)0x2579 = (int)a;                  /* stl a,*(0x2579) */
        *(volatile int *)0x259F = (int)a;                  /* stl a,*(0x259f) */
        *(volatile int *)0x25A0 = (int)a;                  /* stl a,*(0x25a0) */
        *(volatile int *)0x25C1 = (int)a;                  /* stl a,*(0x25c1) */
    }
    if (*(volatile int *)0x2510 == 192)                    /* cmpm *(0x2510),#192; bc tc */
        goto tail;
    if (*(volatile int *)0x2510 != 177)                    /* cmpm *(0x2510),#177; rc ntc */
        return;
tail:
    *(volatile int *)0x2630 = (int)a;                      /* stl a,*(0x2630) */
    *(volatile int *)0x264F = -1;                           /* st #-1,*(0x264f) */
    *(volatile int *)0x2EF9 &= 319;                        /* andm #319,*(0x2ef9) */
    /* ret */
}
