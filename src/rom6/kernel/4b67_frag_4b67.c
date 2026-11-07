/* ROM6 0x4B67 FRAG_4B67 -- 26w dual accumulate-store lane.
 * Verified encoding: src/rom6/kernel/4b67_frag_4b67.asm (recombine MATCH).
 * ORIGIN 0x4B67
 * EXPECT: 7693 D25C 7693 99FE 7693 3C55 45E2 0001 1B92 F761 8193 8393 45E2 0001 1B92 F761 F363 001F F365 FF00 8393 F120 FFFF EC03 8193 FC00
 *
 * Intent: Three immediates (-11684, -26114, 15445) stored via *AR3-entry
 * post-increment (st). Then twice: B = *(AR2+1) << 16 (ld Smem,16,b) OR
 * *AR2-entry post-increment (or, Smem zero-extended into B-low); B <<= 1
 * (sfta b,1, 40-bit). First lane stores B-low then B-high via *AR3++
 * (stl, sth: high word is B bits 31:16 per STH convention). Second lane
 * masks B &= 31 << 16 then B ^= 65280 << 16 (and/xor #lk,16,b) and stores
 * B-high via *AR3++. B = -1 (ld); four B-low stores via *AR3++ (rpt #3 +
 * stl: repeat runs 4 times). Returns. AR2/AR3 post-increments ride in the
 * local cursors only (no caller write-back, per 4439/9B63/DBD4 precedent).
 * A untouched (dead). Bound 4B67-4B80 (exit FC00@4B80).
 */
void frag_4B67(int *par2, int *par3)
{
    long b;

    *par3++ = -11684;                            /* st #-11684,*ar3+ */
    *par3++ = -26114;                            /* st #-26114,*ar3+ */
    *par3++ = 15445;                             /* st #15445,*ar3+ */
    b = (long)par2[1] << 16;                     /* ld *ar2(0x1),16,b */
    b |= (unsigned short)*par2++;                /* or *ar2+,b */
    b <<= 1;                                     /* sfta b,1 */
    *par3++ = (int)(b & 0xFFFF);                 /* stl b,*ar3+ */
    *par3++ = (int)((b >> 16) & 0xFFFF);         /* sth b,*ar3+ (high) */
    b = (long)par2[1] << 16;                     /* ld *ar2(0x1),16,b */
    b |= (unsigned short)*par2++;                /* or *ar2+,b */
    b <<= 1;                                     /* sfta b,1 */
    b &= (long)31 << 16;                         /* and #31,16,b */
    b ^= (long)65280 << 16;                      /* xor #65280,16,b */
    *par3++ = (int)((b >> 16) & 0xFFFF);         /* sth b,*ar3+ (high) */
    b = -1L;                                     /* ld #-1,b */
    *par3++ = (int)(b & 0xFFFF);                 /* rpt #3 + stl x4 */
    *par3++ = (int)(b & 0xFFFF);
    *par3++ = (int)(b & 0xFFFF);
    *par3++ = (int)(b & 0xFFFF);
    /* ret */
}
