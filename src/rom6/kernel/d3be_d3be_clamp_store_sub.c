/* ROM6 0xD3BE D3BE_CLAMP_STORE_SUB -- 49w min/max clamp-store lane.
 * Verified encoding: src/rom6/kernel/d3be_d3be_clamp_store_sub.asm (recombine MATCH).
 * ORIGIN 0xD3BE
 * EXPECT: 61F8 0A60 0001 FA20 D3E1 E804 1868 F844 D3D4 7212 3000 1059 6FE2 FBA6 0D4E F845 D3D1 445C F587 835C F073 D3E4 F274 D39E 7712 0C2A 445B F487 7212 0B5A 825B F273 D3E4 31E2 FC34 E900 FD45 835C 83F8 3003 F062 1000 F587 7712 0C2A EC03 7092 0C2B FE00
 *
 * Intent: TC = bit 0 of cell 0xA60 (bitf); the bcd
 * delay pair (A = 4, A &= *(0x68)) always runs, then
 * clear TC exits to the E1 lane (bcd ntc). Main
 * lane: A != 0 continues to the D4 lane (bc aneq),
 * else AR2 = cell 0x3000 (mvdm); A = cell 0x59; B =
 * *(AR2 - 1354) << 14 (ld long-offset, SXM
 * unbound, flagged); A == 0 skips the min (bc
 * aeq); else A = cell 0x5C << 16, B = min(A,B)
 * (min b: dst B per oracle bit-8 rule and ba32;
 * C side effect unobserved, flagged); cell 0x5C =
 * B-high (sth); joins E4 (b). D4 lane: calld delay
 * sets AR2 = 3114 first, then pooled D39E (call, no
 * C entry, effects dark, flagged); A = cell 0x5B
 * << 16; A = min(A,B) (min a: dst A); AR2 = cell
 * 0xB5A (mvdm); cell 0x5B = A-high; the bd delay
 * runs B = *(AR2 - 972) x A-high (mpya long-offset,
 * MPYA_SMEM row; replace per oracle + 87eb/e442,
 * signed 16x16 per op_multiply, FRCT/SXM dark;
 * T <- Smem unobserved downstream, flagged) then
 * takes the E4 join (bd). E1 lane: B = 0; A == 0
 * stores B-high to cell 0x5C (xc 1,aeq,
 * execute-when-true); falls into E4. Join E4: cell
 * 0x3003 = B-high; A = 4096 << 16; A = min(A,B);
 * AR2 = 3114; 4x *(AR2++) = cell 0xC2B (rpt #3 +
 * mvkd); retd with its 2 delay words owned by the
 * next span (wave-11 spill, D3EF-D3F0 execute
 * there). A/B/AR2/T caller-live across the pooled
 * call (dark, flagged).
 * EXPECT from the image.
 */
/* calld 0xd39e: pooled, no C entry (see d39e_leaf_d39e Pool note) */

void clamp_store_sub_D3BE(void)
{
    long a;
    long b;
    int *ar2;
    int i;

    /* bitf *(0xa60),#1 (TC = bit set) */
    /* bcd 0xd3e1,ntc (delays run before the branch) */
    a = 4L;                                                /* delay 1: ld #4,a */
    a &= (long)(unsigned)*(volatile int *)0x68;            /* delay 2: and 0x68,a */
    if ((*(volatile int *)0xA60 & 1) == 0)                  /* bcd ntc taken */
        goto lane_e1;
    if (a != 0L)                                           /* bc 0xd3d4,aneq */
        goto lane_d4;
    ar2 = (int *)(long)*(volatile int *)0x3000;            /* mvdm 0x3000,ar2 */
    a = (long)*(volatile int *)0x59;                       /* ld 0x59,a */
    b = (long)*(ar2 - 1354) << 14;                         /* ld *ar2(0xfba6),14,b */
    if (a == 0L)                                           /* bc 0xd3d1,aeq */
        goto store_b;
    a = (long)*(volatile int *)0x5C << 16;                 /* ld 0x5c,16,a */
    if (a < b)                                             /* min b (B = min) */
        b = a;
store_b:
    *(volatile int *)0x5C = (int)((b >> 16) & 0xFFFFL);    /* sth b,0x5c */
    goto join_e4;                                          /* b 0xd3e4 */
lane_d4:
    /* calld 0xd39e (delay stm #3114,ar2 runs first) */
    ar2 = (int *)(long)3114;
    /* calld 0xd39e (pooled; A/B/AR effects dark, flagged) */
    a = (long)*(volatile int *)0x5B << 16;                 /* ld 0x5b,16,a */
    if (b < a)                                             /* min a (A = min) */
        a = b;
    ar2 = (int *)(long)*(volatile int *)0xB5A;             /* mvdm 0xb5a,ar2 */
    *(volatile int *)0x5B = (int)((a >> 16) & 0xFFFFL);    /* sth a,0x5b */
    /* bd 0xd3e4 (delay runs before the branch) */
    b = (long)*(ar2 - 972) *                               /* delay: mpya *ar2(0xfc34) */
        (long)(short)((a >> 16) & 0xFFFFL);                /* (B = Smem x A-high) */
    goto join_e4;                                          /* bd 0xd3e4 */
lane_e1:
    b = 0L;                                                /* ld #0,b */
    if (a == 0L)                                           /* xc 1,aeq */
        *(volatile int *)0x5C = (int)((b >> 16) & 0xFFFFL); /* sth b,0x5c */
    /* falls into join_e4 */
join_e4:
    *(volatile int *)0x3003 = (int)((b >> 16) & 0xFFFFL); /* sth b,*(0x3003) */
    a = 4096L << 16;                                       /* ld #4096,16,a */
    if (a < b)                                             /* min b (B = min) */
        b = a;
    ar2 = (int *)(long)3114;                               /* stm #3114,ar2 */
    for (i = 0; i < 4; i++)                                /* rpt #3 */
        *ar2++ = *(volatile int *)0xC2B;                   /* mvkd 0xc2b,*ar2+ */
    /* retd (delays D3EF-D3F0 owned by next span, run before return) */
}
