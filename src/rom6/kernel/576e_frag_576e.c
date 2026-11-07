/* ROM6 0x576E FRAG_576E -- 53w mode select with store-back.
 * Verified encoding: src/rom6/kernel/576e_frag_576e.asm (recombine MATCH).
 * ORIGIN 0x576E
 * EXPECT: 11F8 250F F210 0051 F845 5778 F210 0050 F844 577E 60F8 0915 0002 FC20 F073 5785 F210 0052 FC44 60F8 091B 009F FC20 11F8 250F F330 00F0 7711 245F 1081 6B81 0001 FC47 F210 0050 F845 579D F210 0010 FC44 1081 00F8 250C 8081 08F8 2654 FC47 7681 0001 69F8 2628 0040 FC00
 *
 * Intent: B = cell 0x250F sign-extended (ld). A = B - 81; A == 0 (B == 81)
 * rejoins at 0x5778 (bc aeq; the label is the cmpm below, no separate
 * block). A = B - 80; A != 0 runs 0x577E (bc aneq): A = B - 82, nonzero
 * returns (rc aneq); cell 0x91B != 159 returns (cmpm #159, TC-only; rc
 * ntc); falls into 0x5785. B == 80 falls to 0x5778: cell 0x915 != 2
 * returns (cmpm, rc ntc); else jumps to 0x5785 (b; also the chained entry
 * from ROUTINE_5755 interior, mid-span join, no separate span). At 0x5785:
 * B = cell 0x250F & 240 (ld, and #240); AR1 = 9311 (stm, local); A =
 * *AR1; cell *AR1 += 1 (addm); A <= 0 returns (rc aleq; ALEQ = A <= 0 per
 * BLEQ/AGEQ symmetry). A = B - 80; A == 0 runs 0x579D (bc aeq): *AR1 = 1
 * (st), cell 0x2628 |= 64 (orm #64), returns. Else A = B - 16; nonzero
 * returns (rc aneq). A = *AR1 + cell 0x250C (ld, add Smem sign-extended
 * under SXM = 1 per op_sub_smem.c); *AR1 = A-low (stl); A -= cell 0x2654
 * (sub Smem); A <= 0 returns (rc aleq). Else *AR1 = 1, cell 0x2628 |= 64,
 * returns. A/B/AR1 internal. Bound 576E-57A2 (exit FC00@57A2).
 */
void frag_576E(void)
{
    long a;
    long b;
    int *par1;

    b = (long)*(volatile int *)0x250F;                 /* ld *(0x250f),b */
    a = b - 81L;                                       /* sub #81,b,a */
    if (a != 0) {                                      /* bc 0x5778,aeq */
        a = b - 80L;                                   /* sub #80,b,a */
        if (a != 0) {                                  /* bc 0x577e,aneq */
            /* 0x577e: sub #82 arm */
            if (b - 82L != 0)                          /* sub; rc aneq */
                return;
            if (*(volatile int *)0x91B != 159)         /* cmpm; rc ntc */
                return;
        } else {
            /* 0x5778: B == 80 falls here (cmpm, shared) */
            if (*(volatile int *)0x915 != 2)           /* cmpm; rc ntc */
                return;
        }
    } else {
        /* 0x5778: B == 81 rejoins here */
        if (*(volatile int *)0x915 != 2)               /* cmpm; rc ntc */
            return;
    }
    /* 0x5785 join (plus chained entry from ROUTINE_5755) */
    b = (long)*(volatile int *)0x250F;                 /* ld *(0x250f),b */
    b &= 240L;                                         /* and #240,b */
    par1 = (int *)9311;                                /* stm #9311,ar1 */
    a = (long)*par1;                                   /* ld *ar1,a */
    *par1 += 1;                                        /* addm #1,*ar1 */
    if (a <= 0)                                        /* rc aleq */
        return;
    a = b - 80L;                                       /* sub #80,b,a */
    if (a == 0) {                                      /* bc 0x579d,aeq */
        *par1 = 1;                                     /* 0x579d: st */
        *(volatile int *)0x2628 |= 64;                 /* orm #64 */
        return;
    }
    a = b - 16L;                                       /* sub #16,b,a */
    if (a != 0)                                        /* rc aneq */
        return;
    a = (long)*par1;                                   /* ld *ar1,a */
    a += (long)*(volatile int *)0x250C;                /* add *(0x250c),a */
    *par1 = (int)(a & 0xFFFF);                         /* stl a,*ar1 */
    a -= (long)*(volatile int *)0x2654;                /* sub *(0x2654),a */
    if (a <= 0)                                        /* rc aleq */
        return;
    *par1 = 1;                                         /* st #1,*ar1 */
    *(volatile int *)0x2628 |= 64;                     /* orm #64,*(0x2628) */
    /* ret */
}
