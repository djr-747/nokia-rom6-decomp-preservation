/* ROM6 0x772F FRAG_772F -- 31w dual-MAC retry block.
 * Verified encoding: src/rom6/kernel/772f_frag_772f.asm (recombine MATCH).
 * ORIGIN 0x772F
 * EXPECT: 25C2 2DDE 43BA 47B4 1AE4 4EB0 A7D8 EF12 B962 040F 2D45 761B F074 059E E907 E725 E736 E800 47F8 000B B089 4E94 6DEE 0002 F310 0002 FA4E 7740 E752 E763 FC00
 *
 * Intent: Mixed MAC prelude then a BGT-gated retry loop (4
 * passes). Prelude: MPYU (B = unsigned(*AR2-) * T, T dark,
 * circular AR2, flagged); MAS (B -= T * *AR6+, circular);
 * shifted SUB (B -= mem[AR2+AR0] << 16; +0B = bit-reversed
 * step, BK/BRAF dark, flagged); RPT-count from *AR4+
 * (RC = *AR4++); A |= mem[AR4+0x4EB0]; MACSU dual product
 * (B += unsigned(*AR3+0%) * signed(*AR2+); X-unsigned per
 * MACSU, circular AR3, flagged); literal word 0xEF12 (no C
 * form -- byte-owned by the .asm, noted); 4-operand MAS
 * (B = (*AR4-) * (*AR4) - A, src/dst pattern parallel to
 * the SUB/ADD 4-op forms, SPRU172 to confirm, flagged);
 * A += mem(0x0F) << TS (TS = T & 31, T dark, flagged);
 * B -= T * mem(0x45); cell 0x1B = -3980; B += *AR6 << TS.
 * Main (interior-projection calld F274@749E->773B lands on
 * the call 0x59e word -- alternate entry, flagged): B = 7; AR5 =
 * AR2; AR6 = AR3; per pass: A = 0; RPT-count from cell
 * 0x0B, dual-MAC accumulate A += X*Y RC+1 times; 32-bit DST
 * pair store (MSW at *AR4, LSW at *(AR4+1), AR4++);
 * AR6 += 2; B -= 2; BCD/BGT retries at 7740 (delays restore
 * AR2/AR5... AR2 = AR5, AR3 = AR6, then branch while B > 0:
 * 7,5,3,1 then -1 falls through); restore pointers; return.
 */
extern void sub_059E(void); /* low-region: zero in mask dump; see docs/evidence/extern-triage.md */

void frag_772F(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;  /* live-in (dark, flagged) */
    int *ar5;
    int *ar6;
    int t;  /* T live-in (dark, flagged) */
    int ts;
    int rc;
    int pass;
    int k;

    b = (long)(unsigned)*ar2-- * (long)t;                      /* mpyu *ar2-%,b (circular, flagged) */
    b -= (long)t * (long)*ar6++;                               /* mas *ar6+0%,b (circular, flagged) */
    b -= (long)*(ar2) << 16;                                   /* sub *ar2+0B,16,b (bit-reversed step flagged) */
    rc = *ar4++;                                               /* rpt *ar4+0 */
    a |= (long)*(ar4 + 0x4EB0);                                /* or *ar4(0x4eb0),a */
    b += (long)(unsigned)*ar3++ * (long)*ar2++;                /* macsu *ar3+0%,*ar2+,b (X-unsigned, circular, flagged) */
    /* .word 0xEF12 (literal, byte-verified, no C form) */
    b = (long)*ar4-- * (long)*ar4 - a;                         /* mas *ar4-,*ar4,a,b (4-op dst = X*Y - src, flagged) */
    ts = t & 31;
    a += (long)*(volatile int *)0x0F << ts;                    /* add 0x0f,ts,a */
    b -= (long)t * (long)*(volatile int *)0x45;                /* mas 0x45,b */
    *(volatile int *)0x1B = -3980;                             /* st #-3980,0x1b */
    b += (long)*ar6 << ts;                                     /* add *+ar6,ts,b */
    sub_059E();                                                /* call 0x59e (RAM; exterior calld 749E->773B re-enters here) */
    b = 7;                                                     /* ld #7,b */
    ar5 = ar2;                                                 /* mvmm ar2,ar5 */
    ar6 = ar3;                                                 /* mvmm ar3,ar6 */
    for (pass = 0; pass < 4; pass++) {
        a = 0;                                                 /* ld #0,a */
        rc = *(volatile int *)0x0B;                            /* rpt *(0xb) */
        for (k = 0; k <= rc; k++)                              /* (RC+1 dual-MAC taps) */
            a += (long)*ar2++ * (long)*ar3++;                  /* mac *ar2+,*ar3+,a (dual) */
        *ar4 = (int)((a >> 16) & 0xFFFFL);                     /* dst a,*ar4+ (MSW) */
        *(ar4 + 1) = (int)(a & 0xFFFFL);                       /* (LSW) */
        ar4++;
        ar6 += 2;                                              /* mar *+ar6(0x2) */
        b -= 2;                                                /* sub #2,b */
        ar2 = ar5;                                             /* bcd delays: mvmm ar5,ar2 */
        ar3 = ar6;                                             /* mvmm ar6,ar3 */
        /* bcd 0x7740,bgt (taken while B > 0: 7,5,3,1 then -1 falls through) */
    }
    /* ret */
    (void)t;
}
