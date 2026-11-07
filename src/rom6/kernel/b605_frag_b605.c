/* ROM6 0xB605 FRAG_B605 -- 26w cell-sum gate (DROM lane).
 * Verified encoding: src/rom6/kernel/b605_frag_b605.asm (recombine MATCH).
 * ORIGIN 0xB605
 * EXPECT: 10F8 04C4 00F8 04C5 8813 7712 04C6 6F83 0C5F F030 7F80 0892 1183 F330 00FF F84C B61F 818A 81F8 04C8 6F83 0C5F F030 7F80 8082 FC00
 *
 * Intent: A = cell 0x4C4 + cell 0x4C5 (ld, add Smem: arithmetic Smem reads
 * sign-extend under SXM = 1 per ti-c54x op_sub_smem.c). AR3 = A-low
 * (stlm); AR2 = 1222 (stm). A = *AR3 >> 1 (ld *ar3,-1,a, arithmetic);
 * A &= 32640 (0x7F80); A -= *(1222) sign-extended, AR2 -> 1223
 * (sub *ar2+,a). B = *AR3 & 255 (ld, and #255,b); B != 0 tail-enters
 * FRAG_B61F with B-live (bc bneq; has .asm reading B via sfta b,3,
 * forward extern void frag_B61F(long b_live)). Else *1223 = B-low = 0
 * (stl b,*ar2-, AR2 back to 1222); cell 0x4C8 = 0 (stl); A = *AR3 >> 1 &
 * 32640 again; *1222 = A-low (stl); returns. A/B/AR2/AR3 all internal.
 * Bound B605-B61E (exit FC00@B61E).
 */
extern void frag_B61F(long b_live); /* joins b61f_frag_b61f; see docs/evidence/extern-triage.md */

void frag_B605(void)
{
    long a;
    long b;
    int *par3;
    int *par2;

    a = (long)*(volatile int *)0x4C4;              /* ld *(0x4c4),a */
    a += (long)*(volatile int *)0x4C5;             /* add *(0x4c5),a */
    par3 = (int *)(long)(a & 0xFFFF);              /* stlm a,ar3 */
    par2 = (int *)1222;                            /* stm #1222,ar2 */
    a = (long)*par3 >> 1;                          /* ld *ar3,-1,a */
    a &= 32640L;                                   /* and #32640,a */
    a -= (long)*par2++;                            /* sub *ar2+,a (signed) */
    b = (long)*par3;                               /* ld *ar3,b */
    b &= 255L;                                     /* and #255,b */
    if (b != 0) {                                  /* bc 0xb61f,bneq */
        frag_B61F(b);
        return;
    }
    *par2-- = (int)(b & 0xFFFF);                   /* stl b,*ar2- (writes 0) */
    *(volatile int *)0x4C8 = (int)(b & 0xFFFF);    /* stl b,*(0x4c8) */
    a = (long)*par3 >> 1;                          /* ld *ar3,-1,a */
    a &= 32640L;                                   /* and #32640,a */
    *par2 = (int)(a & 0xFFFF);                     /* stl a,*ar2 */
    /* ret */
}
