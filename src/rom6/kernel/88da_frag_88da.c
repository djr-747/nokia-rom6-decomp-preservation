/* ROM6 0x88DA FRAG_88DA -- 45w dual-copy setup lane.
 * Verified encoding: src/rom6/kernel/88da_frag_88da.asm (recombine MATCH).
 * ORIGIN 0x88DA
 * EXPECT: 6884 FFFE 76F8 055A 0000 6884 FFF9 6984 0002 7714 118B F274 86FB 7713 3025 7710 0011 7712 3025 7713 3090 771A 0007 F272 88F6 7714 119C E509 E58A 7719 0000 7713 309B 771A 0003 F272 8902 7712 2F3A E50D E58A F074 89C4 F073 88AD
 *
 * Intent: Read-modify-write through entry AR4 (dark,
 * flagged): clear bit 0, clear bits 0-2, set bit 1; then
 * AR4 = 4491; *(0x55A) = 0; calld SHARED_SUB_86FB (delays:
 * AR3 = 12325, runs pre-call); AR0 = 17; AR2 = 12325;
 * AR3 = 12432; BRC = 7. RPTBD block, 8x (delays: AR4 =
 * 4508): *(AR3++) = *(AR2) then *(AR4++) = *(AR2++)
 * (AR2 frozen first, steps second). BK = 0; AR3 = 12443;
 * BRC = 3. RPTBD block, 4x (delays: AR2 = 12090): *(AR3) =
 * *(AR2) frozen (+0% with BK = 0: no AR update per oracle
 * indirect_circular, wrap flagged) then *(AR4++) =
 * *(AR2++). Calls ROUTINE_89C4; branches to 88AD (span
 * owns). AR0/BK/BRC/ARs computed; out cells/ARs.
 * EXPECT from the image.
 */
void frag_88DA(void)
{
    int *ar0;
    int *ar2;
    int *ar3;
    int *ar4;  /* live-in (dark, flagged) */
    int i;

    *ar4 &= -2;                                              /* andm #-2,*ar4 */
    *(volatile int *)0x55A = 0;                              /* st #0,*(0x55a) */
    *ar4 &= -7;                                              /* andm #-7,*ar4 */
    *ar4 |= 2;                                               /* orm #2,*ar4 */
    ar4 = (int *)4491;                                       /* stm #4491,ar4 */
    ar3 = (int *)12325;                                      /* stm #12325,ar3 (calld delays) */
    shared_SUB_86FB();                                       /* calld 0x86fb */
    ar0 = (int *)17;                                         /* stm #17,ar0 */
    ar2 = (int *)12325;                                      /* stm #12325,ar2 */
    ar3 = (int *)12432;                                      /* stm #12432,ar3 */
    /* stm #7,brc; rptbd 0x88f6 */
    ar4 = (int *)4508;                                       /* stm #4508,ar4 (delay) */
    for (i = 0; i < 8; i++) {                                /* (BRC+1; BRC = 7) */
        *ar3++ = *ar2;                                       /* mvdd *ar2,*ar3+ */
        *ar4++ = *ar2++;                                     /* mvdd *ar2+,*ar4+ */
    }
    /* stm #0,bk */
    ar3 = (int *)12443;                                      /* stm #12443,ar3 */
    /* stm #3,brc; rptbd 0x8902 */
    ar2 = (int *)12090;                                      /* stm #12090,ar2 (delay) */
    for (i = 0; i < 4; i++) {                                /* (BRC+1; BRC = 3) */
        *ar3 = *ar2;                                         /* mvdd *ar2,*ar3+0% (BK = 0 frozen, flagged) */
        *ar4++ = *ar2++;                                     /* mvdd *ar2+,*ar4+ */
    }
    routine_89C4();                                          /* call 0x89c4 */
    /* b 0x88ad (span owns) */
    (void)ar0;
}
