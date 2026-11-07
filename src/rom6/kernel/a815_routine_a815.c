/* ROM6 0xA815 ROUTINE_A815 -- 46w far-call bit-merge.
 * Verified encoding: src/rom6/kernel/a815_routine_a815.asm (recombine MATCH).
 * ORIGIN 0xA815
 * EXPECT: F074 067C 60F8 2510 00C0 FC20 61F8 051C 0003 F830 A830 61F8 051F 1800 F830 A830 10F8 2EFE FC44 F981 811B 7714 2579 FB81 A8DA 7713 3090 76F8 25A0 00C0 FB81 A824 7714 257E F55F 81F8 257F F46F 68F8 257E 7FFF 1AF8 257E 80F8 257E FC00
 *
 * Intent: Calls sub_067C (low-zone unsourced, flagged);
 * return unless *(0x2510) == 192 (cmpm equality, oracle;
 * rc ntc); return if *(0x51C) has bits 0-1 or *(0x51F) has
 * bits 11-12 (bitf any-bit TC, oracle; both bc 0xa830,tc
 * to the tail span, which owns); return if *(0x2EFE) != 0
 * (ld, SXM dark flagged; rc aneq). Far_1811B (uploaded XPC
 * page, off-image, extern-triage); AR4 = 9593; far_1A8DA
 * (fcalld, delays AR3 = 12432 run pre-call); *(0x25A0) =
 * 192; AR4 = 9598 (fcalld delays) into far_1A824. B =
 * A>>1 arithmetic (ld a,-1,b on the callee-defined A,
 * dark; SXM-gated, flagged); *(0x257F) = B-low; A <<= 15
 * (sfta, OVM flagged); *(0x257E) &= 32767 (andm); A |=
 * *(0x257E) zero-extended (upper preserved); *(0x257E) =
 * A-low; return. A/B callee-defined after the far calls
 * (dark); out cells/ARs.
 * EXPECT from the image.
 */
extern void far_1811B(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */
extern void far_1A8DA(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */
extern void far_1A824(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */

void routine_A815(void)
{
    long a;  /* callee-defined after far calls (dark, flagged) */
    long b;
    int *ar3;
    int *ar4;

    sub_067C();                                               /* call 0x67c (low-zone, flagged) */
    if (*(volatile int *)0x2510 != 192)                       /* cmpm, rc ntc */
        return;
    if ((*(volatile int *)0x51C & 3) != 0)                    /* bitf, bc 0xa830,tc (tail owns) */
        return;
    if ((*(volatile int *)0x51F & 6144) != 0)                 /* bitf, bc tc */
        return;
    a = (long)*(volatile int *)0x2EFE;                        /* ld *(0x2efe),a (SXM dark) */
    if (a != 0)                                               /* rc aneq */
        return;
    far_1811B();                                              /* fcall 0x1811b */
    ar4 = (int *)9593;                                        /* stm #9593,ar4 */
    ar3 = (int *)12432;                                       /* stm #12432,ar3 (fcalld delays) */
    far_1A8DA();                                              /* fcalld 0x1a8da */
    *(volatile int *)0x25A0 = 192;                            /* st #192,*(0x25a0) */
    ar4 = (int *)9598;                                        /* stm #9598,ar4 (fcalld delays) */
    far_1A824();                                              /* fcalld 0x1a824 */
    b = a >> 1;                                               /* ld a,-1,b (SXM-gated, flagged) */
    *(volatile int *)0x257F = (int)(b & 0xFFFFL);             /* stl b,*(0x257f) */
    a = a << 15;                                              /* sfta a,15 (OVM flagged) */
    *(volatile int *)0x257E &= 32767;                         /* andm #32767 */
    a |= (unsigned int)*(volatile int *)0x257E;               /* or *(0x257e),a (upper kept) */
    *(volatile int *)0x257E = (int)(a & 0xFFFFL);             /* stl a,*(0x257e) */
    /* ret */
    (void)ar3;
    (void)ar4;
}
