/* ROM6 0x5E7D SUB_5E7D -- 54w.
 * Verified encoding: src/rom6/kernel/5e7d_sub_5e7d.asm (recombine MATCH).
 * ORIGIN 0x5E7D
 * EXPECT: F074 0598 7712 2627 6182 0001 F820 5EE1 E900 61F8 2627 0080 F830 5E96 10F8 2634 F843 5EE1 61F8 2629 8000 F830 5EE1 F120 0100 6892 FF7E 6892 1FFF 6882 1FFF 76F8 2614 0000 7712 2456 7713 2F0A 1B92 8193 E509 7093 2618 7083 2615 60F8 250F 0022 F820 5EB3 6B93 0EA6 F073 5EB5
 *
 * Intent: Masked merge plus ring stage. Runs 0x598 (dark, forward extern); cell 9767 bit 0 clear jumps away to dark 0x5EE1 (bc ntc). B = 0; cell 0x2627 bit 7 set jumps away to dark 0x5E96 (bc tc). A = cell 0x2634, negative jumps away to 0x5EE1 (bc alt: A < 0 per 6871 precedent); cell 0x2629 sign bit set jumps away too (bc tc). Else B = 256; clears bits 0 and 7 of cell 9767 (andm #-130) and bits 13-15 of 9768/9769 (andm #8191); clears cell 0x2614; B |= cell 9302 into cell 12042; moves cell 9303 to 12043 (mvdd, AR2 fixed); moves cells 0x2618/0x2615 to 12044/12045 (mvdk pair); cell 0x250F != 34 jumps away to FRAG_5EB3 (bc ntc: has .asm, no C yet, forward extern). Else cell 12045 += 3750 (addm), tail-enters dark 0x5EB5 (b, forward extern). AR2/AR3 fully preset in span, no params. Bound 5E7D-5EB2.
 */
extern void sub_0598(void);
extern void frag_5EE1(void);
extern void frag_5E96(void);
extern void frag_5EB3(void);
extern void frag_5EB5(void);

void sub_5E7D(void)
{
    int a;
    int b;
    int *ar2;
    int *ar3;
    sub_0598();                                  /* call 0x598 */
    /* stm #9767,ar2 */
    if ((*(volatile int *)9767 & 1) == 0) {      /* bitf *ar2,#1; bc ntc */
        frag_5EE1();                             /* away, dark */
        return;
    }
    b = 0;                                       /* ld #0,b */
    if ((*(volatile int *)0x2627 & 128) != 0) {  /* bitf, bc tc */
        frag_5E96();                             /* away, dark */
        return;
    }
    a = *(volatile int *)0x2634;             /* ld */
    if (a < 0) {                                 /* bc 0x5ee1,alt */
        frag_5EE1();                             /* away, dark */
        return;
    }
    if ((*(volatile int *)0x2629 & -32768) != 0) { /* bitf, bc tc */
        frag_5EE1();                             /* away, dark */
        return;
    }
    b = 256;                                     /* ld #256,b */
    *(volatile int *)9767 &= -130;           /* andm #-130,*ar2+ */
    *(volatile int *)9768 &= 8191;           /* andm #8191,*ar2+ */
    *(volatile int *)9769 &= 8191;           /* andm #8191,*ar2 */
    *(volatile int *)0x2614 = 0;             /* st #0 */
    ar2 = (int *)9302;                          /* stm #9302,ar2 */
    ar3 = (int *)12042;                         /* stm #12042,ar3 */
    b |= (unsigned short)*ar2++;                  /* or *ar2+,b (Smem zero-ext) */
    *ar3++ = b;                                  /* stl b,*ar3+ */
    *ar3++ = *ar2;                               /* mvdd *ar2,*ar3+ */
    *ar3++ = *(volatile int *)0x2618;        /* mvdk 0x2618,*ar3+ */
    *ar3 = *(volatile int *)0x2615;          /* mvdk 0x2615,*ar3 */
    if (*(volatile int *)0x250F != 34) {         /* cmpm, bc ntc */
        frag_5EB3();                             /* away, unbound C */
        return;
    }
    *ar3 += 3750;                               /* addm #3750,*ar3+ */
    frag_5EB5();                                 /* b 0x5eb5 tail */
}
