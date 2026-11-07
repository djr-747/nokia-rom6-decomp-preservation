/* ROM6 0xC460 TRIO_06DA_C450 -- 17w.
 * Verified encoding: src/rom6/kernel/c460_trio_06da_c450.asm (recombine MATCH).
 * ORIGIN 0xC460
 * EXPECT: F074 06DA 771A 007F 7213 3148 4541 E732 ED1F 6D93 F272 C46F 4482 F600 C898 F600 FC00
 *
 * Intent: Block-fill trio head (first of C450/C460/C471; callers BE04/BE0D
 * calld->C450, BDF6/BDFB->C460, BE13/BE1B calld->C471 per asm evidence).
 * CALL 0x6DA (RAM-resident mini-kernel, zeros in-mask, forward extern);
 * BRC = 127; AR3 = *(0x3148); B = *(DP:0x41)<<16 (DP dark, flagged);
 * AR2 = AR3; ASM = -1 (shift mode, no C form, flagged); AR3++ (mar);
 * rptbd block x128 (A = *AR2<<16, A += B, store A-low + reload A = *AR3+,
 * A += B); return @C470. Abubs the C471 trio span (falls through).
 */
extern void sub_06DA(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void trio_C460(void)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int i;

    sub_06DA();                                                /* call 0x6da (RAM) */
    /* stm #127,brc */
    ar3 = (int *)(long)*(volatile int *)0x3148;                /* mvdm 0x3148,ar3 */
    b = (long)*(volatile int *)0x41 << 16;                     /* ld DP+0x41,16,b (DP dark, flagged) */
    ar2 = ar3;                                                 /* mvmm ar3,ar2 */
    /* ld #-1,asm (shift mode, no C form, flagged) */
    ar3++;                                                     /* mar *ar3+ */
    for (i = 0; i < 128; i++) {                                /* rptbd 0xc46f */
        a = (long)*ar2 << 16;                                  /* ld *ar2,16,a */
        a += b;                                                /* add b,a */
        *ar2 = (int)(a & 0xFFFFL);                             /* st a,*ar2+ (low) */
        a = (long)*ar3;                                        /* || ld *ar3+,a */
        ar2++;
        ar3++;
        a += b;                                                /* add b,a */
    }
    /* ret @C470 */
}
