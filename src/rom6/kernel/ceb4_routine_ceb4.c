/* ROM6 0xCEB4 ROUTINE_CEB4 -- 34w masked-merge lane.
 * Verified encoding: src/rom6/kernel/ceb4_routine_ceb4.asm (recombine MATCH).
 * ORIGIN 0xCEB4
 * EXPECT: 7212 0ECD 771A 0004 F272 CEC3 7711 FEF2 E807 1882 0211 8813 E808 1882 1A83 8092 771A 0003 E907 E724 1092 F280 F272 CED2 0211 8813 1092 F280 E51A 0211 8813 FE00 F495 E512
 *
 * Intent: Masked-merge lane with two sequential RPTBD
 * blocks. AR2 = cell 0xECD (MVMD); BRC = 4; outer RPTBD
 * block CEB9-CEC3 x5 {AR1 = -270; A = 7; A &= Smem(*AR2)
 * (zero-extended, upper cleared, per op_and_smem);
 * A = sat(A + mem(0x11) << 16) (ADDS); AR3 = AL; A = 8;
 * A &= Smem; A |= Smem(*AR3) (zero-extended per
 * op_or_smem); *(AR2++) = AL}. Then BRC = 3; B = 7;
 * AR4 = AR2; A = *AR2++; A &= B (acc-acc, full-width);
 * inner RPTBD block CECC-CED2 x4 {A = sat(A + mem(0x11)
 * << 16); AR3 = AL; A = *AR2++; A &= B; *(AR4++) = *AR3;
 * A = sat(A + mem(0x11) << 16); AR3 = AL}; return with
 * NOP + *(AR4) = *AR3 (MVDD) in the delay slots. Masked
 * table-merge shape: AR2 source, AR4 sink (both dark,
 * flagged); AR1/AR3 cursors.
 * (Wave-13: Smem-logical zero-extension per the oracle
 * logical leaves; RPTBD blocks end at REA with the head
 * words inside the block; EXPECT from the image.)
 */
void routine_CEB4(void)
{
    long a;
    long b;
    int *ar1;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;
    int *ar4;
    int i;

    ar2 = (int)*(volatile int *)0x0ECD;                         /* mvdm 0xecd,ar2 */
    /* stm #4,brc */
    for (i = 0; i < 5; i++) {                                  /* rptbd 0xcec3 */
        ar1 = (int *)-270;                                     /* stm #-270,ar1 */
        a = 7;                                                 /* ld #7,a */
        a &= (long)(*ar2 & 0xFFFF);                            /* and *ar2,a */
        { long na = a + ((long)*(volatile int *)0x11 << 16);   /* adds 0x11,a */
          if (na > 0x7FFFFFFFL) na = 0x7FFFFFFFL;
          if (na < -0x80000000L) na = -0x80000000L;
          a = na; }
        ar3 = (int)(a & 0xFFFFL);                              /* stlm a,ar3 */
        a = 8;                                                 /* ld #8,a */
        a &= (long)(*ar2 & 0xFFFF);                            /* and *ar2,a */
        a |= (long)(*ar3 & 0xFFFF);                            /* or *ar3,a */
        *ar2++ = (int)(a & 0xFFFFL);                           /* stl a,*ar2+ */
    }
    /* stm #3,brc */
    b = 7;                                                     /* ld #7,b */
    ar4 = ar2;                                                 /* mvmm ar2,ar4 */
    a = (long)*ar2++;                                          /* ld *ar2+,a */
    a &= b;                                                    /* and b,a */
    for (i = 0; i < 4; i++) {                                  /* rptbd 0xced2 */
        { long na = a + ((long)*(volatile int *)0x11 << 16);   /* adds 0x11,a */
          if (na > 0x7FFFFFFFL) na = 0x7FFFFFFFL;
          if (na < -0x80000000L) na = -0x80000000L;
          a = na; }
        ar3 = (int)(a & 0xFFFFL);                              /* stlm a,ar3 */
        a = (long)*ar2++;                                      /* ld *ar2+,a */
        a &= b;                                                /* and b,a */
        *ar4++ = *ar3;                                         /* mvdd *ar3,*ar4+ */
        { long na = a + ((long)*(volatile int *)0x11 << 16);   /* adds 0x11,a */
          if (na > 0x7FFFFFFFL) na = 0x7FFFFFFFL;
          if (na < -0x80000000L) na = -0x80000000L;
          a = na; }
        ar3 = (int)(a & 0xFFFFL);                              /* stlm a,ar3 */
    }
    /* retd (delay words run, then return): */
    /* nop */
    *ar4 = *ar3;                                               /* mvdd *ar3,*ar4 */
    /* retd */
}
