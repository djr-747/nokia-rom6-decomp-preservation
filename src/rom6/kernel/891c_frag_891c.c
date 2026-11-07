/* ROM6 0x891C FRAG_891C -- 26w.
 * Verified encoding: src/rom6/kernel/891c_frag_891c.asm (recombine MATCH).
 * ORIGIN 0x891C
 * EXPECT: 7714 118B F274 86FB 7713 3090 7719 0000 7710 0011 7713 2F32 7712 3099 EC03 E59C 7712 309A EC03 E59C 7712 309B EC03 E59C F073 88AD
 *
 * Intent: Triple stripe copy. AR4 = 4491 (dead, noted); AR3 = 12432
 * (calld delay, dead, noted); runs dark SUB_86FB; BK = 0 (circular
 * off, strides linear -- assumed, flagged); AR0 = 17 (stride);
 * three stripes of 4 dual moves *(AR2) = *(AR3++) with AR2 += 17
 * (rpt #3 + MVDD +0%, 457f precedent; base unbound, flagged) at
 * AR2 = 12441, 12442, 12443; tail-branch FRAG_8894 interior 0x88AD
 * (.asm only, forward extern; AR liveness through the dark call
 * unbound, flagged). Bound 891C-8935.
 */
extern void sub_86FB(void); /* joins 86fb_shared_sub_86fb; see docs/evidence/extern-triage.md */
extern void frag_88AD(void); /* joins 8894_frag_8894 interior @+0x19; see docs/evidence/extern-triage.md */

void frag_891C(void)
{
    int *ar3;
    int *ar2;
    int i;
    /* stm #4491,ar4 (dead, noted) */
    /* calld delay: AR3 = 12432 (dead, noted) */
    sub_86FB();                                      /* calld 0x86fb (dark) */
    /* stm #0,bk (circular off, flagged); stm #17,ar0 */
    ar3 = (int *)12082;                              /* stm #12082,ar3 */
    ar2 = (int *)12441;                              /* stm #12441,ar2 */
    for (i = 0; i < 4; i++) {                        /* rpt #3 */
        *ar2 = *ar3++;                               /* mvdd *ar3+,*ar2+0% */
        ar2 += 17;                                   /* +0% (linear, flagged) */
    }
    ar2 = (int *)12442;                              /* stm #12442,ar2 */
    for (i = 0; i < 4; i++) {                        /* rpt #3 */
        *ar2 = *ar3++;
        ar2 += 17;
    }
    ar2 = (int *)12443;                              /* stm #12443,ar2 */
    for (i = 0; i < 4; i++) {                        /* rpt #3 */
        *ar2 = *ar3++;
        ar2 += 17;
    }
    frag_88AD();                                     /* b 0x88ad (8894 interior) */
}
