/* ROM6 0xC450 TRIO_06DA_C450 -- 16w.
 * Verified encoding: src/rom6/kernel/c450_trio_06da_c450.asm (recombine MATCH).
 * ORIGIN 0xC450
 * EXPECT: F074 06DA 771A 0057 F7B9 E817 0844 880E F272 C45E 7710 0002 14B2 0242 8293 FC00
 *
 * Intent: Shift-add tap loop. Runs dark SUB_06DA; BRC = 87; OVM on
 * (ssbx, hardware state -- saturation unmodeled, flagged); T =
 * 23 - cell0x44 (stlm); the rptbd delay slot AR0 = 2 runs once;
 * 88 passes of A = (*AR2 << T, SXM sign-extended per the 5c34
 * precedent, flagged; T range assumed sane, flagged) with AR2 +=
 * AR0, A += unsigned cell0x42 (ADDS = unsigned add per the vendored
 * TI catalog note 0x0200 row; DP = 0 assumed, flagged), *AR3++ =
 * A-high (block [RSA = PC + 4 = 0xC45C, REA = 0xC45E]; RPTBD
 * execution stays deferred, flagged); return (ARs dead, flagged).
 * Bound C450-C45F.
 */
extern void sub_06DA(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void trio_06DA_C450(int *ar2_in, int *ar3_in)
{
    int *ar2 = ar2_in;
    int *ar3 = ar3_in;
    long a;
    long t;
    int i;
    sub_06DA();                                      /* call 0x6da (dark) */
    /* stm #87,brc; ssbx st1,ovm (hardware state) */
    a = 23 - (long)*(volatile int *)0x44;            /* ld #23,a; sub 0x44,a */
    t = a;                                           /* stlm a,t */
    /* rptbd delay: AR0 = 2 (once) */
    for (i = 0; i < 88; i++) {                       /* rptbd 0xc45e */
        if (t >= 0)
            a = (long)*ar2 << t;                     /* ld *ar2+0,ts,a */
        else
            a = (long)*ar2 >> -t;
        ar2 += 2;                                    /* +0: AR2 += AR0 */
        a += (unsigned long)(unsigned)*(volatile int *)0x42; /* adds 0x42,a */
        *ar3++ = (int)((a >> 16) & 0xFFFF);          /* sth a,*ar3+ */
    }
    /* ret */
}
