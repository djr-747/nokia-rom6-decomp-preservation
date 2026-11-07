/* ROM6 0xE442 SUB41_E442 -- 41w quad-lane MAC engine.
 * Verified encoding: src/rom6/kernel/e442_sub41_e442.asm (recombine MATCH).
 * ORIGIN 0xE442
 * EXPECT: 941A 908E 3183 8270 1868 8071 F44F F48C 3564 F641 406A 908E 3183 8272 1868 8073 F44F F48C 3564 F641 5470 908E 3183 8270 1868 8071 F44F F48C 3564 F641 5472 908E 3183 1868 F44F F48C 3564 5570 FE00 91CD F666
 *
 * Intent: Four MAC lanes over caller-live AR2/AR3 (dark,
 * flagged; AR3 never stepped, AR2 +1 per lane) with direct
 * cells (DP = 0 assumed, flagged). Per lane: A =
 * *(AR3)<<10 (SXM dark, flagged); A += *(AR2++)<<14; B =
 * *(AR3) x A-high (mpya Smem, oracle; FRCT doubling dark,
 * flagged); T = *(0x64) via the maca read-phase T load
 * (oracle; lane 1 mpya-a uses entry T dark, later lanes use
 * *(0x64)); *(cell) = A-high (sth, ASM dark, flagged); A &=
 * *(0x68) (zero-extend, oracle op_and_smem); *(cell+1) =
 * A-low; A <<= 15; A = T x A-high (mpya a, T dark, flagged);
 * B += *(0x64) x A-high (maca, oracle op_maca_smem); A =
 * B<<1; A -= tail-cell<<16 (sub/dsub Smem<<16). Lane stores
 * go to 0x70/0x71, 0x72/0x73, 0x70/0x71; lane 4 stores
 * nothing and ends B -= *(0x70)<<16. RETD delays run
 * pre-return: B += *(AR2)<<13 (frozen +0%, BK dark,
 * flagged); A = B<<6 (sfta, OVM flagged); return. OVM
 * saturation flagged throughout. A/B entry dead; out A/B.
 * EXPECT from the image.
 */
void sub41_E442(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int t;  /* T live-in (dark, flagged) */

    a = (long)*ar3 << 10;                                    /* lane 1: ld *ar3,10,a (SXM dark) */
    a += (long)*ar2++ << 14;                                 /* add *ar2+,14,a */
    b = (long)*ar3 * (long)(short)((a >> 16) & 0xFFFFL);     /* mpya *ar3 (FRCT dark, flagged) */
    *(volatile int *)0x70 = (int)((a >> 16) & 0xFFFFL);      /* sth a,0x70 (ASM dark) */
    a &= (unsigned int)*(volatile int *)0x68;                /* and 0x68,a (zero-extend) */
    *(volatile int *)0x71 = (int)(a & 0xFFFFL);              /* stl a,0x71 */
    a = a << 15;                                             /* ld a,15,a (OVM flagged) */
    a = (long)t * (long)(short)((a >> 16) & 0xFFFFL);        /* mpya a (T x A-high; FRCT dark, flagged) */
    b += (long)*(volatile int *)0x64 * (long)(short)((a >> 16) & 0xFFFFL);
    t = *(volatile int *)0x64;                                   /* (maca loads T = Smem) */ /* maca 0x64,b */
    a = b << 1;                                              /* ld b,1,a */
    a -= (long)*(volatile int *)0x6A << 16;                  /* sub 0x6a,16,a */
    a += (long)*ar2++ << 14;                                 /* lane 2 */
    b = (long)*ar3 * (long)(short)((a >> 16) & 0xFFFFL);
    *(volatile int *)0x72 = (int)((a >> 16) & 0xFFFFL);
    a &= (unsigned int)*(volatile int *)0x68;
    *(volatile int *)0x73 = (int)(a & 0xFFFFL);
    a = a << 15;
    a = (long)t * (long)(short)((a >> 16) & 0xFFFFL);        /* mpya a (T x A-high; FRCT dark, flagged) */
    b += (long)*(volatile int *)0x64 * (long)(short)((a >> 16) & 0xFFFFL);
    t = *(volatile int *)0x64;                                   /* (maca loads T = Smem) */
    a = b << 1;
    a -= (long)*(volatile int *)0x70 << 16;                  /* dsub 0x70,a */
    a += (long)*ar2++ << 14;                                 /* lane 3 */
    b = (long)*ar3 * (long)(short)((a >> 16) & 0xFFFFL);
    *(volatile int *)0x70 = (int)((a >> 16) & 0xFFFFL);
    a &= (unsigned int)*(volatile int *)0x68;
    *(volatile int *)0x71 = (int)(a & 0xFFFFL);
    a = a << 15;
    a = (long)t * (long)(short)((a >> 16) & 0xFFFFL);        /* mpya a (T x A-high; FRCT dark, flagged) */
    b += (long)*(volatile int *)0x64 * (long)(short)((a >> 16) & 0xFFFFL);
    t = *(volatile int *)0x64;                                   /* (maca loads T = Smem) */
    a = b << 1;
    a -= (long)*(volatile int *)0x72 << 16;                  /* dsub 0x72,a */
    a += (long)*ar2++ << 14;                                 /* lane 4 (no stores) */
    b = (long)*ar3 * (long)(short)((a >> 16) & 0xFFFFL);
    a &= (unsigned int)*(volatile int *)0x68;
    a = a << 15;
    a = (long)t * (long)(short)((a >> 16) & 0xFFFFL);        /* mpya a (T x A-high; FRCT dark, flagged) */
    b += (long)*(volatile int *)0x64 * (long)(short)((a >> 16) & 0xFFFFL);
    t = *(volatile int *)0x64;                                   /* (maca loads T = Smem) */
    b -= (long)*(volatile int *)0x70 << 16;                  /* dsub 0x70,b */
    /* retd: delays run, then return */
    b += (long)*ar2 << 13;                                   /* add *ar2+0%,13,b (frozen, BK dark) */
    a = b << 6;                                              /* sfta b,6,a (OVM flagged) */
    /* retd */
}
