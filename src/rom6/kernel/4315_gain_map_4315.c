/* ROM6 0x4315 GAIN_MAP_4315 -- 51w.
 * Verified encoding: src/rom6/kernel/4315_gain_map_4315.asm (recombine MATCH).
 * ORIGIN 0x4315
 * EXPECT: F074 0606 F847 4330 F110 0020 F84B 4327 F48E E919 F48F F477 F470 09F8 000E F030 003F FD4B E900 890E F000 B09E 8813 F166 0605 F76D 3E83 61F8 3EC8 0020 F820 4343 61F8 263B 0004 F120 0474 FF20 F120 049C 0182 8912 F273 4345 4582 F495 4582 F766 F784 F500 FC00
 *
 * Intent: Gain select with twin tails. Runs 0x606 (dark,
 * extern; entry A assumed preserved through it, flagged);
 * A <= 0 skips the scale lane to the 4330 selects (bc
 * aleq). B = A - 32 (sub lk); B < 0 (A < 32) runs B = 0
 * and joins the 4327 lane (bc blt lands on the ld #0,b).
 * Scale lane: T = exponent of A (exp: redundant sign bits
 * minus 8 per op_exp; A >= 32 here so T = leading zeros,
 * exact); B = 25; A <<= T (norm, op_norm_acc; the
 * normalized bit-31 fill diverges between signed-long
 * arithmetic and hw-positive shifts but the immediate
 * AND #63 below observes only low bits, identical --
 * noted); A arith>>= 9 then >>= 16 (sfta pair); B -=
 * MMR 0xE (sub Smem direct, DP = 0 assumed, flagged);
 * A &= 63 (upper cleared); B < 0 keeps B, else B = 0
 * (xc 1,blt covers the 1-word ld). 4327 lane: T = B-low
 * (stlm b,t); A += -20322 (add lk); AR3 = A-low (stlm).
 * B = T times 1541 (mpy #1541,b per the MPY_LK row,
 * T times K16 into the selected accumulator, FRCT/OVM
 * unbound flagged); B <<= 13 arithmetic (sfta; magnitude
 * assumed small, flagged); A = B plus *(AR3) << 16
 * (add Smem<<16 per the ADD_SMEM_SH16 row: S = 1, D = 0
 * from the word, SXM-sign-extend flagged). 4330 lane:
 * TC = bit 5 of cell 0x3EC8 (bitf); clear runs the
 * 4343-entry code (bc ntc to the second ld: B =
 * *(AR2) << 16 then B <<= 6 arithmetic); set runs the
 * 4334 lane: TC = bit 2 of cell 0x263B, B = 1140 with TC
 * set reloading B = 1180 (xc 2,ntc covers the 2-word
 * ld), B += *(AR2) (add Smem; AR2 read-only), AR2 =
 * B-low through the out-pointer (stlm b,ar2 -- the
 * clobber feeds the delay load below, so it threads via
 * int** per the B110 pattern); the bd delay loads B =
 * *(AR2) << 16 with the nop delay, then always branches
 * to the 4345 tail (bd unconditional). 4345 tail: B = -B
 * (neg); B += A (add a,b); return. AR2/AR3 step on
 * locals; ARs/A/B dead at return (flagged). Bound
 * 4315-4347.
 */
extern void sub_0606(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void gain_map_4315(long a_live, int *ar2_in, int **ppar2)
{
    int *ar2 = ar2_in;
    int *ar3;
    long a = a_live;
    long b;
    int t;
    sub_0606();                                      /* call 0x606 */
    if (a <= 0)                                      /* bc 0x4330,aleq */
        goto lane4330;
    b = a - 32;                                      /* sub #32,a,b */
    if (b >= 0) {                                    /* bc 0x4327,blt (fall) */
        {                                            /* exp/norm lane */
            int lz = 0;
            unsigned long ua = (unsigned long)a;
            int k;
            for (k = 31; k >= 0; k--) {              /* op_exp mirror */
                if ((ua >> k) & 1UL)
                    break;
                lz++;
            }
            t = lz;                                  /* exp a */
            a <<= t;                                 /* norm a */
            a >>= 9;                                 /* sfta a,-9 (arith) */
            a >>= 16;                                /* sfta a,-16 (arith) */
        }
        b = 25;                                      /* ld #25,b */
        b -= (long)*(volatile int *)0xE;             /* sub *(0xe),b */
        a &= 63;                                     /* and #63,a */
        if (b >= 0)                                  /* xc 1,blt */
            b = 0;                                   /* ld #0,b */
    } else {
        b = 0;                                       /* bc-taken: ld #0,b */
    }
    t = (int)(b & 0xFFFF);                           /* stlm b,t (4327) */
    a += -20322;                                     /* add #-20322,a */
    ar3 = (int *)(a & 0xFFFF);                       /* stlm a,ar3 */
    b = (long)t * 1541;                              /* mpy #1541,b */
    b <<= 13;                                        /* sfta b,13 (arith) */
    a = b + ((long)*ar3 << 16);                      /* add *ar3,16,b,a */
lane4330:
    if ((*(volatile int *)0x3EC8 & 32) == 0) {       /* bitf; bc ntc */
        b = (long)*ar2 << 16;                        /* 4343 entry */
        b <<= 6;                                     /* sfta b,6 */
    } else {
        if ((*(volatile int *)0x263B & 4) != 0)      /* bitf #4 */
            b = 1180;                                /* xc skips (TC set) */
        else
            b = 1140;                                /* ld #1140,b */
        b += (long)*ar2;                             /* add *ar2,b */
        *ppar2 = (int *)(b & 0xFFFF);                /* stlm b,ar2 */
        ar2 = *ppar2;
        b = (long)*ar2 << 16;                        /* bd delay (always) */
        /* nop (delay) */
        /* bd 0x4345 (always taken) */
    }
    b = -b;                                          /* neg b (4345 tail) */
    b += a;                                          /* add a,b */
    /* ret */
}
