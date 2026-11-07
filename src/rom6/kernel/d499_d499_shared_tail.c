/* ROM6 0xD499 D499_SHARED_TAIL -- 51w min/max filter pump.
 * Verified encoding: src/rom6/kernel/d499_d499_shared_tail.asm (recombine MATCH).
 * ORIGIN 0xD499
 * EXPECT: 6168 0004 F820 D4CE F274 D39E 7712 0C2F 445D 7212 0B5A F487 7716 3002 31E2 FC3B 835D 8386 7712 0C18 4592 3F92 3F92 3F8A F77E F062 F6B3 F586 4D8A 4D8A 4D82 8382 7712 0C2F EC03 7092 0C30 1061 7082 0B5D FD45 105E EA14 F074 DB81 EA16 4815 F010 0078 FC44 FE00
 *
 * Intent: Entered via bc 0xd499,bneq (caller at
 * 0xD45A, byte-verified). Bit 2 of cell 0x68 set
 * skips to the D4CE exit (bc ntc; cell DP = 0
 * assumed per da40, flagged). Else the calld delay
 * (AR2 = 3119) runs first, then pooled D39E (call,
 * no C entry, effects dark, flagged); A = cell
 * 0x5D << 16; AR2 = cell 0xB5A (mvdm); A = min(A,B)
 * (min a: dst A per oracle bit-8 rule and ba32);
 * AR6 = 12290; T <- *(AR2 - 197), B = *(AR2 - 197)
 * x A-high (mpya long-offset, MPYA_SMEM row,
 * replace per oracle + 87eb/e442, signed 16x16 per
 * op_multiply, FRCT/SXM dark, T-write unobserved
 * downstream, flagged); cell 0x5D = B-high; *(AR6)
 * = B-high. AR2 = 3096; B = *(AR2++) << 16;
 * B += *(AR2++) << 16 twice; B += *(AR2--) << 16;
 * B >>= 2 arithmetic (sfta); A = -2381 << 16;
 * B = max(A,B) (max b: dst B); the three delays
 * pump the tap line -- *(AR2 + 1) = *(AR2) then
 * the AR step (per oracle op_delay_smem: Smem
 * write-back to Smem + 1, not a nop; 25f2's
 * no-C-form note now correction-debt); *(AR2) =
 * B-high. AR2 = 3119; 4x *(AR2++) = cell 0xC30
 * (rpt #3 + mvkd); A = cell 0x61 (DP = 0
 * assumed); *(AR2) = cell 0xB5D (mvkd); A == 0
 * loads A = cell 0x5E (xc 1,aeq,
 * execute-when-true). DP = 20 (hardware, flagged);
 * runs routine_DB81(A); DP = 22 (hardware). A =
 * AR5 register value (ldm, AR5 entry-dark,
 * flagged); A -= 120; nonzero returns (rc aneq);
 * retd with its 2 delay words owned by the next
 * span (D4CC-D4CD run there). Entry AR5 caller-live
 * dark; A/B entry dead (set in-span).
 * EXPECT from the image.
 */
/* calld 0xd39e: pooled, no C entry (see d39e_leaf_d39e Pool note) */
extern void routine_DB81(long a_live);

void d499_shared_tail(void)
{
    long a;
    long b;
    int *ar2;
    int *ar5;   /* live-in (dark, flagged) */
    int *ar6;
    int i;

    if ((*(volatile int *)0x68 & 4) == 0)                  /* bitf 0x68,#4; bc ntc */
        goto lane_d4ce;                                    /* b 0xd4ce (tail) */
    /* calld 0xd39e (delay stm #3119,ar2 runs first) */
    ar2 = (int *)(long)3119;
    /* calld 0xd39e (pooled; effects dark, flagged) */
    a = (long)*(volatile int *)0x5D << 16;                 /* ld 0x5d,16,a */
    ar2 = (int *)(long)*(volatile int *)0xB5A;             /* mvdm 0xb5a,ar2 */
    if (b < a)                                             /* min a (A = min) */
        a = b;
    ar6 = (int *)(long)12290;                              /* stm #12290,ar6 */
    b = (long)*(ar2 - 197) *                               /* mpya *ar2(0xfc3b) */
        (long)(short)((a >> 16) & 0xFFFFL);                /* (B = Smem x A-high) */
    *(volatile int *)0x5D = (int)((b >> 16) & 0xFFFFL);    /* sth b,0x5d */
    *ar6 = (int)((b >> 16) & 0xFFFFL);                     /* sth b,*ar6 */
    ar2 = (int *)(long)3096;                               /* stm #3096,ar2 */
    b = (long)*ar2++ << 16;                                /* ld *ar2+,16,b */
    b += (long)*ar2++ << 16;                               /* add *ar2+,16,b */
    b += (long)*ar2++ << 16;                               /* add *ar2+,16,b */
    b += (long)*ar2-- << 16;                               /* add *ar2-,16,b */
    b >>= 2;                                               /* sfta b,-2 */
    a = -2381L << 16;                                      /* ld #-2381,16,a */
    if (a > b)                                             /* max b (B = max) */
        b = a;
    *(ar2 + 1) = *ar2;                                     /* delay *ar2- */
    ar2--;
    *(ar2 + 1) = *ar2;                                     /* delay *ar2- */
    ar2--;
    *(ar2 + 1) = *ar2;                                     /* delay *ar2 */
    *ar2 = (int)((b >> 16) & 0xFFFFL);                     /* sth b,*ar2 */
    ar2 = (int *)(long)3119;                               /* stm #3119,ar2 */
    for (i = 0; i < 4; i++)                                /* rpt #3 */
        *ar2++ = *(volatile int *)0xC30;                   /* mvkd 0xc30,*ar2+ */
    a = (long)*(volatile int *)0x61;                       /* ld 0x61,a */
    *ar2 = *(volatile int *)0xB5D;                         /* mvkd 0xb5d,*ar2 */
    if (a == 0L)                                           /* xc 1,aeq */
        a = (long)*(volatile int *)0x5E;                   /* ld 0x5e,a */
    /* ld #20,dp (DP hardware; call intake, flagged) */
    routine_DB81(a);                                       /* call 0xdb81 */
    /* ld #22,dp (DP hardware) */
    a = (long)ar5;                                         /* ldm ar5,a */
    a -= 120L;                                             /* sub #120,a */
    if (a != 0L)                                           /* rc aneq */
        return;
    /* retd (delays D4CC-D4CD owned by next span, run before return) */
    return;
lane_d4ce:
    /* b 0xd4ce (tail; lane owned elsewhere) */
    return;
}
