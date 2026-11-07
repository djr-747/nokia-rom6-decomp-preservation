/* ROM6 0x7C2F FRAG_7C2F -- 39w dual-accumulator sweep, RPTB in BANZ.
 * Verified encoding: src/rom6/kernel/7c2f_frag_7c2f.asm (recombine MATCH).
 * ORIGIN 0x7C2F
 * EXPECT: F074 05A0 7712 30A4 7710 0001 4E92 4E8A 7714 2FA4 771A 001F F072 7C49 5694 6C80 7C42 F484 F495 5794 FD42 F784 F485 5092 538A 4E92 4F8A 6C88 7C39 F274 42B8 7712 30A4 F470 60F8 0013 0001 FC30 F47F
 *
 * Intent: Calls sub_05A0 (low-zone unsourced, flagged); AR2 =
 * 12452, AR0 = 1; head stores entry A (dark) twice via 1-word
 * DST (32-bit MSW@AR LSW@(AR+1), AR step 2 -- the 1-word
 * indirect DST/DLD forms are absent from the ti-c54x catalog,
 * flagged oracle-gap; pairing per wave-13 MSW/LSW note +
 * oracle DST_LONG32; step 2 gives the clean head-init +
 * in-place-refine structure). RPTB block (BRC = 31, 32x)
 * nested in a BANZ outer loop back to the BRC reload: each
 * inner pass A = DLD *(AR4) (32-bit MSW|LSW, AR4 += 2, SXM
 * sign-extension dark, flagged); AR0-- (banz; skips only
 * neg a + nop by jumping to the dld-b, and the single
 * first-pass neg is absorbed by the following abs --
 * abs(neg(x)) == abs(x) -- so all passes model abs-only);
 * B = DLD *(AR4); if (A < 0) B = -B (xc 1,ageq skips neg b,
 * exact); A = |A| (abs, LONG_MIN flagged); A += *(AR2++) <<
 * 16, B += *(AR2--) << 16 (dadd per oracle catalog 0x50xx,
 * OVM saturation flagged); DST A then DST B back through
 * AR2 (net AR2 unchanged per pass). AR0 arithmetic gives
 * 1986 outer passes (33 decrements/pass from AR0 = 1, first
 * zero at the outer banz) then falls through: calld
 * ROUTINE_42B8 (delays: AR2 = 12452, runs pre-call); A >>=
 * 16 arithmetic (sfta, SXM-gated sign fill flagged); return
 * if *(0x13) == 1 (cmpm equality, oracle op_cmpm_smem_lk;
 * rc tc immediate); A >>= 1 arithmetic; abuts SUB84_7C03
 * (no exit in-span). A/B/T/SXM/OVM/AR0/BRC dark as noted.
 * EXPECT from the image.
 */
void frag_7C2F(void)
{
    long a;  /* entry dark; DLD/abs-defined in-loop */
    long b;
    int *ar2;
    int *ar4;
    int ar0;
    int i;

    sub_05A0();                                              /* call 0x5a0 (low-zone, flagged) */
    ar2 = (int *)12452;                                      /* stm #12452,ar2 */
    ar0 = 1;                                                 /* stm #1,ar0 */
    *ar2 = (int)((a >> 16) & 0xFFFFL);                       /* dst a,*ar2+ (MSW@AR) */
    *(ar2 + 1) = (int)(a & 0xFFFFL);                         /* (LSW@(AR+1); AR step 2, flagged) */
    ar2 += 2;
    *ar2 = (int)((a >> 16) & 0xFFFFL);                       /* dst a,*ar2- */
    *(ar2 + 1) = (int)(a & 0xFFFFL);
    ar2 -= 2;
    ar4 = (int *)12196;                                      /* stm #12196,ar4 */
    /* stm #31,brc @7c39 (reloaded each outer pass) */
    do {
        /* rptb 0x7c49: 32x */
        for (i = 0; i < 32; i++) {
            a = ((long)*ar4 << 16) | (unsigned int)*(ar4 + 1); /* dld *ar4+,a (SXM dark, flagged) */
            ar4 += 2;
            ar0--;                                           /* banz 0x7c42,*ar0 */
            if (ar0 == 0)                                    /* (first pass only; absorbed by abs) */
                a = -a;                                      /* neg a */
            /* nop */
            b = ((long)*ar4 << 16) | (unsigned int)*(ar4 + 1); /* dld *ar4+,b */
            ar4 += 2;
            if (a < 0)                                       /* xc 1,ageq */
                b = -b;                                      /* neg b */
            if (a < 0)                                       /* abs a (LONG_MIN flagged) */
                a = -a;
            a += (long)*ar2++ << 16;                         /* dadd *ar2+,a (OVM flagged) */
            b += (long)*ar2-- << 16;                         /* dadd *ar2-,b */
            *ar2 = (int)((a >> 16) & 0xFFFFL);               /* dst a,*ar2+ */
            *(ar2 + 1) = (int)(a & 0xFFFFL);
            ar2 += 2;
            *ar2 = (int)((b >> 16) & 0xFFFFL);               /* dst b,*ar2- */
            *(ar2 + 1) = (int)(b & 0xFFFFL);
            ar2 -= 2;
        }
        ar0--;                                               /* banz 0x7c39,*ar0- */
    } while (ar0 != 0);                                      /* (1986 passes from AR0 = 1) */
    /* stm #12452,ar2 (calld delays, run pre-call) */
    ar2 = (int *)12452;
    routine_42B8();                                          /* calld 0x42b8 */
    a = a >> 16;                                             /* sfta a,-16 (SXM-gated, flagged) */
    if (*(volatile int *)0x13 == 1)                          /* cmpm *(0x13),#1; rc tc */
        return;
    a = a >> 1;                                              /* sfta a,-1 */
    /* abuts SUB84_7C03 (no exit in-span) */
}
