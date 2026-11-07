/* ROM6 0xAE49 FRAG_AE49 -- 35w block-copy gate.
 * Verified encoding: src/rom6/kernel/ae49_frag_ae49.asm (recombine MATCH).
 * ORIGIN 0xAE49
 * EXPECT: 6B82 0001 4815 F074 AE22 61F8 3EC8 0002 F820 AE65 7712 25F6 7715 25F8 E5B8 E5B8 7312 265E 7712 2602 7715 2604 E5B8 E5B8 7312 2660 F073 AE6A 61F8 3EC8 0020 F920 AE1B 8815 FC00
 *
 * Intent: Bit-gated double block copy. Cell *AR2 += 1
 * (ADDM); A = AR5 (LDM, SXM-dark, flagged); call 0xAE22
 * (joins the AD0D table-dispatch driver span at AE22 --
 * asm-owned, no C entry, provisional link name); TC =
 * bit1 of cell 0x3EC8; TC clear skips to AE65; else two
 * 2-word copies (9720->9718, 9732->9730 via MVDD pairs)
 * with the post-copy AR2 values published to cells
 * 0x265E/0x2660 (MVMD), then join at AE6A. At AE65: TC =
 * bit5 of cell 0x3EC8; CC NTC conditionally calls 0xAE1B
 * (same AD0D span join, immediate -- returns; A becomes
 * callee residue, dark, flagged). AE6A: AR5 = AL; return.
 * In AR2/AR5 (dark, flagged); A = entry-AR5 value on the
 * TC path, callee residue on the other.
 * (Wave-13: EXPECT from the image word map; CC immediate
 * conditional call, no delay slots.)
 */
extern void sub_AE22(void); /* joins AD0D driver span at AE22, asm-verified, no C entry yet */
extern void sub_AE1B(void); /* joins AD0D driver span at AE1B, asm-verified, no C entry yet */

void frag_AE49(void)
{
    long a;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar5;  /* live-in (dark, flagged) */
    int tc;

    (*ar2)++;                                                  /* addm #1,*ar2 */
    a = (long)ar5;                                             /* ldm ar5,a (SXM-dark, flagged) */
    sub_AE22();                                                /* call 0xae22 */
    tc = ((*(volatile int *)0x3EC8 & 2) != 0);                 /* bitf *(0x3ec8),#2 */
    if (!tc)                                                   /* bc 0xae65,ntc */
        goto lae65;
    ar2 = (int *)9718;                                         /* stm #9718,ar2 */
    ar5 = (int *)9720;                                         /* stm #9720,ar5 */
    *ar2++ = *ar5++;                                           /* mvdd *ar5+,*ar2+ */
    *ar2++ = *ar5++;                                           /* mvdd *ar5+,*ar2+ */
    *(volatile int *)0x265E = (int)ar2;                        /* mvmd ar2,0x265e */
    ar2 = (int *)9730;                                         /* stm #9730,ar2 */
    ar5 = (int *)9732;                                         /* stm #9732,ar5 */
    *ar2++ = *ar5++;                                           /* mvdd *ar5+,*ar2+ */
    *ar2++ = *ar5++;                                           /* mvdd *ar5+,*ar2+ */
    *(volatile int *)0x2660 = (int)ar2;                        /* mvmd ar2,0x2660 */
    goto lae6a;                                                /* b 0xae6a */
lae65:
    tc = ((*(volatile int *)0x3EC8 & 32) != 0);                /* bitf *(0x3ec8),#32 */
    if (!tc)                                                   /* cc 0xae1b,ntc (immediate) */
        sub_AE1B();                                            /* (returns; A becomes callee residue, dark, flagged) */
lae6a:
    ar5 = (int)(a & 0xFFFFL);                                  /* stlm a,ar5 (AE6A join) */
    /* ret */
    (void)tc;
}
