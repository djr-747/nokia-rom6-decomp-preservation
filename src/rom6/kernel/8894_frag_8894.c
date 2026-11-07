/* ROM6 0x8894 FRAG_8894 -- 37w splat-fill + OR-merge lane.
 * Verified encoding: src/rom6/kernel/8894_frag_8894.asm (recombine MATCH).
 * ORIGIN 0x8894
 * EXPECT: E800 7713 3090 F274 86E3 7714 118B 7719 0000 7710 0011 7714 2F32 7712 3099 EC03 E5CA 7712 309A EC03 E5CA 7712 309B EC03 E5CA 7712 119C 771A 000B F272 88B7 7713 2F32 9498 1A82 8092 FC00
 *
 * Intent: A = 0; AR3 = 12432; calld SUB_86E3 (delays: AR4 =
 * 4491, runs pre-call); BK = 0; AR0 = 17; then three RPT-4
 * splat fills with frozen source (BK = 0 means no post-access
 * AR update per oracle indirect_circular + sequencer
 * UPDATE_PHASE_NONE: access address = AR, AR stays): cells
 * 12082-12085 = *(12441), cells 12086-12089 = *(12442),
 * cells 12090-12093 = *(12443) (mvdd second operand is the
 * destination, 25F2 precedent; rpt #k runs k+1). Then AR2 =
 * 4508, BRC = 11, RPTBD block (delays: AR3 = 12082; block
 * runs 12x): A = *(AR3++) << 8; A |= *(AR2) zero-extended
 * (upper preserved under OR; AR2 not stepped); *(AR2++) =
 * A-low; return. AR0 = 17 unused in-span (out, flagged).
 * In cells; out filled/merged cells/ARs/BK.
 * EXPECT from the image.
 */
void frag_8894(void)
{
    long a;  /* clobbered (entry dark) */
    int *ar2;
    int *ar3;
    int *ar4;
    int i;

    a = 0;                                                   /* ld #0,a */
    ar3 = (int *)12432;                                      /* stm #12432,ar3 */
    ar4 = (int *)4491;                                       /* stm #4491,ar4 (calld delays) */
    sub_86E3();                                              /* calld 0x86e3 */
    /* stm #0,bk: BK = 0 (freezes the % sources below) */
    /* stm #17,ar0 (unused in-span; out, flagged) */
    ar4 = (int *)12082;                                      /* stm #12082,ar4 */
    ar2 = (int *)12441;                                      /* stm #12441,ar2 */
    for (i = 0; i < 4; i++)                                  /* rpt #3 (k+1) */
        *ar4++ = *ar2;                                       /* mvdd *ar2+0%,*ar4+ (BK=0: frozen) */
    ar2 = (int *)12442;                                      /* stm #12442,ar2 */
    for (i = 0; i < 4; i++)
        *ar4++ = *ar2;
    ar2 = (int *)12443;                                      /* stm #12443,ar2 */
    for (i = 0; i < 4; i++)
        *ar4++ = *ar2;
    ar2 = (int *)4508;                                       /* stm #4508,ar2 */
    /* stm #11,brc; rptbd 0x88b7 */
    ar3 = (int *)12082;                                      /* stm #12082,ar3 (rptbd delay) */
    for (i = 0; i < 12; i++) {                               /* rptb block x (BRC+1) */
        a = (long)*ar3++ << 8;                               /* ld *ar3+,8,a */
        a |= (unsigned int)*ar2;                             /* or *ar2,a (zero-extend; upper kept) */
        *ar2++ = (int)(a & 0xFFFFL);                         /* stl a,*ar2+ */
    }
    /* ret */
}
