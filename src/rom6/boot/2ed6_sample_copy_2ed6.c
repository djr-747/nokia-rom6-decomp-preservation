/* ROM6 0x2ED6 SAMPLE_COPY_2ED6 -- 123w.
 * Verified encoding: src/rom6/boot/2ed6_sample_copy_2ed6.asm (recombine MATCH).
 * ORIGIN 0x2ED6
 * EXPECT: 7713 051E 6182 0400 6883 FDFF FF30 6983 0200 7714 054F 6182 0200 6984 0008 FF20 6884 FFF7 6182 0100 F495 E800 FD30 E801 80F8 0374 7714 036B 10D2 F030 00FF 8094 E5CA 12D2 6FF8 036D 0C98 F030 00FF 80F8 036E 12D2 6FF8 036F 0C98 F030 00FF 80F8 0375 12D2 6FF8 0370 0C98 F030 00FF 80F8 0371 12D2 6FF8 0372 0C98 F030 00FF 80F8 0373 7714 0376 10F8 036B F010 0042 EC13 E5CA E906 FD45 E91E 10F8 036D 08F8 250D F843 2F2A F300 0001 81F8 0565 7713 254F 7714 2518 EC22 E59A 61F8 3EC8 0040 F495 F495 FF30 EC03 E59A 69F8 2627 0100 F074 2E2F F073 2E64 69F8 054F 0400 76F8 0545 0000 7714 038B 7694 0000 EC03 E5CA F074 2E2F F073 2E64
 *
 * Intent: Flag-gated split-sample copy with fill lanes and dispatcher tail. AR3 = 1310; TC = *AR2 bit 10;
 * cell &= -513 (andm); TC taken sets bit 9 (xc 2,tc / orm). AR4 = 1359; TC = bit 9; cell |= 8 (orm); TC
 * clear clears bit 3 (xc 2,ntc / andm). TC = bit 8; A = TC ? 1 : 0 (ld #0 + xc-skipped ld #1);
 * cell 0x374 = A (stl). AR4 = 875; A = *AR2 low byte (ld + and #255, exact); *AR4++ = A;
 * *AR4++ = *AR2, AR2 += AR0-live (mvdd +0%; wrap needs caller-live BK, linear flagged). Four ldu/stl
 * split lanes (A unsigned, high/low bytes to 0x36D-0x373, exact). AR4 = 886; A = cell 0x36B - 66 (computed,
 * dead -- reloaded below, flagged); 20x mvdd fill (rpt #19). B = (A == 0) ? 30 : 6 (ld #6 + xc-skipped
 * ld #30). A = cell 0x36D - cell 0x250D (ld/sub); A >= 0 adds 1 to B (bc alt skip). Cell 0x565 = B (stl).
 * AR3 = 9551; AR4 = 9496; 35x linear mvdd fill (rpt #34). TC = cell 0x3EC8 bit 6; TC taken runs a second 4x
 * fill (xc 2,tc + rpt #3). Cell 0x2627 bit 8 set (orm); dispatcher_entry_2E2F(); b-tail frag_2E64().
 * Second entry frag_2F41 (uploaded 0x9F5D/0x9F7E callers): cell 0x54F bit 10 set; cell 0x545 cleared;
 * AR4 = 907; cell + 4x fill; dispatcher call/b tail. AR2/AR0 caller-live, dead after (flagged).
 */
extern void dispatcher_entry_2E2F(void);
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

void frag_2ED6(int *par2, int ar0_live)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int *ar4;
    int taken;
    int i;


    ar2 = par2;
    ar3 = (int *)1310;                                     /* stm #1310,ar3 */
    taken = (*ar2 & 1024) != 0;                            /* bitf *ar2,#1024 */
    *ar3 &= -513;                                          /* andm (always runs) */
    if (taken)                                             /* xc 2,tc */
        *ar3 |= 512;                                       /* orm #512,*ar3 */
    ar4 = (int *)1359;                                     /* stm #1359,ar4 */
    taken = (*ar2 & 512) != 0;                             /* bitf *ar2,#512 */
    *ar4 |= 8;                                             /* orm (always runs) */
    if (!taken)                                            /* xc 2,ntc */
        *ar4 &= -9;                                        /* andm #-9,*ar4 */
    taken = (*ar2 & 256) != 0;                            /* bitf *ar2,#256 */
    /* nop (settle) */
    a = 0;                                                 /* ld #0,a */
    if (taken)                                             /* xc 1,tc (skips ld) */
        a = 1;                                             /* ld #1,a */
    *(volatile int *)0x374 = (int)a;                       /* stl a,*(0x374) */
    ar4 = (int *)875;                                      /* stm #875,ar4 */
    a = (long)*ar2;                                        /* ld *ar2+%,a */
    ar2 += ar0_live;                                       /* +0% (wrap flagged) */
    a &= 255L;                                             /* and #255,a (exact) */
    *ar4++ = (int)a;                                       /* stl a,*ar4+ */
    *ar4++ = *ar2;                                         /* mvdd *ar2+0%,*ar4+ */
    ar2 += ar0_live;                                       /* +0% (wrap flagged) */
    a = (long)(unsigned)*ar2;                            /* ldu *ar2+%,a (A>=0) */
    ar2 += ar0_live;
    *(volatile int *)0x36D = (int)((a >> 8) & 0xFFFF);    /* stl a,-8 (exact) */
    a &= 255L;                                           /* and #255,a */
    *(volatile int *)0x36E = (int)a;                     /* stl a */
    a = (long)(unsigned)*ar2;                            /* ldu (A>=0) */
    ar2 += ar0_live;
    *(volatile int *)0x36F = (int)((a >> 8) & 0xFFFF);    /* stl a,-8 */
    a &= 255L;
    *(volatile int *)0x375 = (int)a;
    a = (long)(unsigned)*ar2;                            /* ldu (A>=0) */
    ar2 += ar0_live;
    *(volatile int *)0x370 = (int)((a >> 8) & 0xFFFF);    /* stl a,-8 */
    a &= 255L;
    *(volatile int *)0x371 = (int)a;
    a = (long)(unsigned)*ar2;                            /* ldu (A>=0) */
    ar2 += ar0_live;
    *(volatile int *)0x372 = (int)((a >> 8) & 0xFFFF);    /* stl a,-8 */
    a &= 255L;
    *(volatile int *)0x373 = (int)a;
    ar4 = (int *)886;                                    /* stm #886,ar4 */
    a = (long)*(volatile int *)0x36B - 66;               /* ld; sub (dead, reloaded below) */
    for (i = 0; i < 20; i++) {                           /* rpt #19 */
        *ar4++ = *ar2;                                   /* mvdd *ar2+0%,*ar4+ */
        ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    }
    b = 6;                                                 /* ld #6,b */
    if (a == 0)                                            /* xc 1,aeq (skips ld) */
        b = 30;                                            /* ld #30,b */
    a = (long)*(volatile int *)0x36D;                    /* ld *(0x36d),a */
    a = a - (long)*(volatile int *)0x250D;               /* sub *(0x250d),a */
    if (a >= 0)                                            /* bc 0x2f2a,alt (skip when <0) */
        b = b + 1;                                         /* add #1,b */
    *(volatile int *)0x565 = (int)(b & 0xFFFF);           /* stl b,*(0x565) */
    ar3 = (int *)9551;                                     /* stm #9551,ar3 */
    ar4 = (int *)9496;                                     /* stm #9496,ar4 */
    for (i = 0; i < 35; i++)                             /* rpt #34 */
        *ar4++ = *ar3++;                                   /* mvdd *ar3+,*ar4+ (linear) */
    taken = (*(volatile int *)0x3EC8 & 64) != 0;          /* bitf *(0x3ec8),#64 */
    /* nop; nop (settles) */
    if (taken) {                                           /* xc 2,tc */
        for (i = 0; i < 4; i++)                           /* rpt #3 */
            *ar4++ = *ar3++;
    }
    *(volatile int *)0x2627 |= 256;                        /* orm #256 */
    dispatcher_entry_2E2F();                               /* call 0x2e2f */
    frag_2E64();                                           /* b 0x2e64 (tail) */
}

void frag_2F41(int *par2, int ar0_live)
{
    int *ar2;
    int *ar4;
    int i;

    ar2 = par2;
    *(volatile int *)0x54F |= 1024;                        /* orm #1024,*(0x54f) */
    *(volatile int *)0x545 = 0;                            /* st #0,*(0x545) */
    ar4 = (int *)907;                                      /* stm #907,ar4 */
    *ar4++ = 0;                                            /* st #0,*ar4+ */
    for (i = 0; i < 4; i++) {                             /* rpt #3 */
        *ar4++ = *ar2;                                     /* mvdd *ar2+0%,*ar4+ */
        ar2 += ar0_live;                                   /* +0% (wrap flagged) */
    }
    dispatcher_entry_2E2F();                               /* call 0x2e2f */
    frag_2E64();                                           /* b 0x2e64 (tail) */
}
