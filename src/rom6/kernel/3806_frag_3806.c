/* ROM6 0x3806 FRAG_3806 -- 21w.
 * Verified encoding: src/rom6/kernel/3806_frag_3806.asm (recombine MATCH).
 * ORIGIN 0x3806
 * EXPECT: F074 06BC 7710 0001 7713 0926 EC50 E5C9 7719 00C8 7713 0926 7212 057D EC50 E59C 6BF8 057C 0001 F073 37DF
 *
 * Intent: Double-blit with counter bump. Runs dark SUB_06BC; AR0 = 1
 * (circular step), AR3 = 2342; 81 dual moves *(AR3++) = *AR2 with
 * AR2 += AR0 (rpt #80 + MVDD +0%, 457f precedent; BK = 200 set
 * in-span but the buffer base is unbound, so the modulo wrap is
 * linear-modeled and flagged -- 81 steps < BK = 200, wrap only if the
 * entry offset exceeds 118); AR3 re-armed; AR2 = cell0x57D (mvdm);
 * 81 dual moves *(AR2) = *(AR3++) same step rule; cell0x57C++;
 * tail-branch FRAG_37DF (C: none yet -- void per the 381b/3850
 * precedent). AR2 entry-live, dead after. Bound 3806-381A.
 */
extern void sub_06BC(void);
extern void frag_37DF(void);

void frag_3806(int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar3;
    int i;
    sub_06BC();                                      /* call 0x6bc (dark) */
    /* stm #1,ar0 (circular step); stm #200,bk (base unbound, flagged) */
    ar3 = (int *)2342;                               /* stm #2342,ar3 */
    for (i = 0; i < 81; i++) {                       /* rpt #80 */
        *ar3++ = *ar2;                               /* mvdd *ar2+0%,*ar3+ */
        ar2 += 1;                                    /* +0%: AR2 += AR0 */
    }
    ar3 = (int *)2342;                               /* stm #2342,ar3 */
    ar2 = (int *)*(volatile int *)0x57D;             /* mvdm 0x57d,ar2 */
    for (i = 0; i < 81; i++) {                       /* rpt #80 */
        *ar2 = *ar3++;                               /* mvdd *ar3+,*ar2+0% */
        ar2 += 1;
    }
    *(volatile int *)0x57C += 1;                     /* addm #1,*(0x57c) */
    frag_37DF();                                     /* b 0x37df */
}
