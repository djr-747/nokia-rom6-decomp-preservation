/* ROM6 ORIGIN 0x4EF3 (71w): FRAG_4EF3 -- OR-fold with u16 expand loop.
 * Verified encoding: src/rom6/kernel/4ef3_frag_4ef3.asm (recombine MATCH).
 * EXPECT: 7713 2456 7714 2616 11F8 2618 1A84 8092 6FF8 2F20 0C48 1A93 60F8 250F 0022 F820 4F0E 60F8 2F1F 0070 F830 4F11 60F8 2F1F 00B0 F830 4F11 8092 F073 4F1D 4A0B 4A0C 4A0D 11F8 3490 F330 0007 F2A9 8092 8A0D 8A0C 8A0B 61F8 3EB5 0200 F820 4F2C 61F8 0586 0001 F820 4F2C E510 6B92 0002 F073 4F2D E518 8192 7092 2615 F272 4F38 7714 2F80 1294 F1F8 F0E8 F1A0 8192 FC00
 *
 * Intent: AR3 = 9302, AR4 = 9750; B = cell 0x2618; A = A-live-in OR
 * cell 0x2618 (or Smem zeroes-extends per op_or_smem); *AR2++ = A-low
 * (AR2 caller pointer, walked). A = (cell 0x2F20 << 8) | *AR3++
 * (LD-acc-shift, OR Smem). Marker != 34 stores A and joins the bitf
 * pair (bc ntc); cell 0x2F1F == 112 or == 176 takes the pshm arm,
 * other values store A and join. Pshm arm: B triple pushed (pshm),
 * B = cell 0x3490 & 7, A |= B << 9 (or b,9,a: OR_ACC_SHIFT leaf,
 * signed-5-bit shift = +9, 40-bit masked, exact in 32-bit C),
 * *AR2++ = A-low, B triple popped (B preserved: scratch modeled on
 * a local so the save/restore is exact by construction). Bitf pair:
 * bit 9 of 0x3EB5 clear or bit 0 of 0x586 clear stores *AR3 to *AR2++
 * (mvdd, no steps) and joins; else *AR2 = *AR3 (no step), cell[AR2] +=
 * 2 with post-inc (addm #2,*ar2+: 4B06 direct-cell precedent plus the
 * post-inc). Join: *AR2++ = B-low (B = head value, preserved);
 * cell[AR2++] = cell 0x2615 (mvkd). Rptbd 0x4F38 (delay AR4 = 12160
 * once; RSA = 0x4F34, REA = 0x4F38, inclusive, BRC+1 passes with
 * caller-live BRC): A = unsigned *AR4++; B = A >> 8 logical (sftl,
 * exact: ldu zeroes high); A <<= 8 (exact: < 2^24); B |= A
 * (or a,b = OR_ACC_SHIFT shift 0 per the S/D-bit decode, cf 8433
 * F0B0 note); *AR2++ = B-low. Ret. A-live-in read once (or *ar4,a);
 * B internal; AR3/AR4 set in-span (AR3 +1 live-out, AR4 walked
 * locally); TC recomputed per test. Bound 4EF3-4F39.
 */
void frag_4EF3(long a_live_in, int *ar2_in, int brc_live_in)
{
    long a = a_live_in;
    long b;
    long b2;
    int i;
    int *ar2 = ar2_in;
    int *ar3;
    int *ar4;
    int tc;

    ar3 = (int *)9302;                                 /* stm #9302,ar3 */
    ar4 = (int *)9750;                                 /* stm #9750,ar4 */
    b = (long)*(volatile int *)0x2618;                 /* ld *(0x2618),b */
    a |= (long)(unsigned)*ar4;                         /* or *ar4,a */
    *ar2++ = (int)(a & 0xFFFF);                        /* stl a,*ar2+ */
    a = (long)*(volatile int *)0x2F20 << 8;            /* ld *(0x2f20),8,a */
    a |= (long)(unsigned)*ar3++;                       /* or *ar3+,a */
    tc = (*(volatile int *)0x250F == 34);               /* cmpm */
    if (!tc) {                                         /* bc 0x4f0e,ntc */
        *ar2++ = (int)(a & 0xFFFF);                    /* stl a,*ar2+ */
        goto bitf;                                     /* b 0x4f1d */
    }
    if (*(volatile int *)0x2F1F == 112 ||               /* cmpm pair */
            *(volatile int *)0x2F1F == 176) {
        /* 0x4f11 pshm arm (B preserved via scratch local) */
        b2 = (long)*(volatile int *)0x3490;            /* ld *(0x3490),b */
        b2 &= 7L;                                      /* and #7,b */
        a |= b2 << 9;                                  /* or b,9,a */
        *ar2++ = (int)(a & 0xFFFF);                    /* stl a,*ar2+ */
        /* popm bg/bh/bl (B restored: scratch used instead) */
    } else {
        *ar2++ = (int)(a & 0xFFFF);                    /* stl a,*ar2+ */
    }
    /* 0x4f1d join */
bitf:
    tc = (*(volatile int *)0x3EB5 & 512) != 0;          /* bitf */
    if (tc) {
        tc = (*(volatile int *)0x586 & 1) != 0;        /* bitf */
        if (tc) {
            *ar2 = *ar3;                               /* mvdd *ar3,*ar2 */
            *ar2 += 2;                                 /* addm #2,*ar2+ */
            ar2++;
            goto join;                                 /* b 0x4f2d */
        }
    }
    /* 0x4f2c */
    *ar2++ = *ar3;                                     /* mvdd *ar3,*ar2+ */
    /* 0x4f2d join */
join:
    *ar2++ = (int)(b & 0xFFFF);                        /* stl b,*ar2+ */
    *ar2++ = *(volatile int *)0x2615;                  /* mvkd 0x2615,*ar2+ */
    /* rptbd 0x4f38 (delay stm #12160,ar4 runs once) */
    ar4 = (int *)12160;
    for (i = 0; i < brc_live_in + 1; i++) {            /* [0x4f34,0x4f38] */
        a = (unsigned long)(unsigned)*ar4++;           /* ldu *ar4+,a */
        b = (long)((unsigned long)a >> 8);             /* sftl a,-8,b */
        a = (long)((unsigned long)a << 8);             /* sftl a,8 */
        b |= a;                                        /* or a,b (shift 0) */
        *ar2++ = (int)(b & 0xFFFF);                    /* stl b,*ar2+ */
    }
    /* ret */
}
