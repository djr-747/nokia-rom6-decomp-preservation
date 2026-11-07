/* ROM6 0x33E8 BIT_LADDER_33E8 -- 115w.
 * Verified encoding: src/rom6/kernel/33e8_bit_ladder_33e8.asm (recombine MATCH).
 * ORIGIN 0x33E8
 * EXPECT: 10DA 7713 051F 61F8 0008 0002 6883 BBF0 FF30 6983 0400 61F8 0008 0004 F820 33FA 6983 4000 7714 263B F130 00F0 6884 FF0F 1B84 8184 6184 0040 F495 E97C FF30 F120 012B 61F8 3EC8 0040 F495 F495 FD30 E9AE 6184 0020 7713 051D FF30 F120 0176 6184 0080 F495 F495 FF30 F120 01F2 61F8 3EC8 0040 F495 F495 FF30 F120 0224 81F8 2A84 61F8 0008 0001 6883 FFF7 FF20 6983 0008 6F82 0C58 80F8 2BFD 10DA F030 00FF 7714 2F00 8094 10F8 3EC8 F030 0040 EC1E E5CA FF46 EC03 E5CA F830 3454 E726 7712 2F1F FF46 6DEA 0004 7713 2A86 F074 434F 81F8 2A84 7683 7FFF E762 F074 2E2F 69F8 054F 0001 F073 2E64
 *
 * Intent: Bit-gated B-select ladder with sample move and pointer dance into a dark call. A = *AR2
 * (AR2 += AR0-live, +0% wrap flagged); AR3 = 1311; cell &= -17424 (andm); TC = cell 0x8 bit 1;
 * TC taken sets bit 10 (xc/orm). TC = bit 2; clear joins the 33FA lane (bc ntc); else bit 14 set.
 * B = A & 240 (and dual, 2D8F precedent); cell 9787 &= -241 (andm); B |= cell (or Smem); cell = B (stl).
 * Five-deep B-select: B = TC?299:124 (bitf64/xc lane), TC2 latches 174, TC3 latches 374, TC4 latches 498,
 * TC5 latches 548 (each xc 2/1,tc skips its ld when clear, B keeps prior); cell 0x2A84 = B (stl).
 * Cell 1311 &= -9 (andm); cell 0x8 bit 0 clear sets bit 3 (xc 2,ntc / orm). A = *AR2 >> 8 arithmetic
 * (ld shift, SXM = 1 flagged); cell 0x2BFD = A-low (stl, exact); A = *AR2 low byte (and #255);
 * AR4 = 12032; *AR4++ = A. A = cell 0x3EC8 & 64 (A >= 0); 31x mvdd fill (rpt #30, AR2 += AR0); A > 0 runs
 * a second 4x fill (xc 2,agt + rpt #3). TC = bit 6 (still set: xc/mvdd preserve TC, and/and/rpt do not
 * clobber); TC taken joins the 3454 tail (bc tc -- dispatcher call, orm bit 0, b-tail). Else: AR6 = AR2
 * save (mvmm); AR2 = 12063; A > 0 advances AR2 by 4 (xc 2,agt / mar); AR3 = 10886; runs dark
 * routine_434F(ar7_live: AR7 caller-live, unbound, flagged); cell 0x2A84 = B (stl); cell AR3 = 32767 (st);
 * AR2 restored (mvmm); dispatcher_entry_2E2F(); cell 0x54F bit 0 set (orm); b-tail frag_2E64().
 * AR2/AR0/AR7 caller-live, dead after (flagged).
 */
extern void routine_434F(int ar7_live);
extern void dispatcher_entry_2E2F(void);
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

void frag_33E8(int *par2, int ar0_live, int ar7_live)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int *ar4;
    int *ar6save;
    int taken;
    int tc6;
    int i;


    ar2 = par2;
    a = (long)*ar2;                                        /* ld *ar2+0%,a */
    ar2 += ar0_live;                                       /* +0% (wrap flagged) */
    ar3 = (int *)1311;                                     /* stm #1311,ar3 */
    taken = (*(volatile int *)0x8 & 2) != 0;               /* bitf *(0x8),#2 */
    *ar3 &= -17424;                                        /* andm (always runs) */
    if (taken)                                             /* xc 2,tc */
        *ar3 |= 1024;                                      /* orm #1024,*ar3 */
    taken = (*(volatile int *)0x8 & 4) != 0;               /* bitf *(0x8),#4 */
    if (!taken)                                            /* bc 0x33fa,ntc */
        goto l33fa;
    *ar3 |= 16384;                                         /* orm #16384,*ar3 */
l33fa:
    ar4 = (int *)9787;                                     /* stm #9787,ar4 */
    b = a & 240L;                                          /* and #240,a,b */
    *ar4 &= -241;                                          /* andm #-241,*ar4 */
    b |= (long)*ar4;                                       /* or *ar4,b */
    *ar4 = (int)(b & 0xFFFF);                              /* stl b,*ar4 */
    taken = (*ar4 & 64) != 0;                              /* bitf *ar4,#64 */
    /* nop (settle) */
    b = 124;                                               /* ld #124,b */
    if (taken)                                             /* xc 2,tc (skips ld) */
        b = 299;                                           /* ld #299,b */
    taken = (*(volatile int *)0x3EC8 & 64) != 0;          /* bitf */
    /* nop; nop */
    if (taken)                                             /* xc 1,tc */
        b = 174;                                           /* ld #174,b */
    taken = (*ar4 & 32) != 0;                              /* bitf *ar4,#32 */
    ar3 = (int *)1309;                                     /* stm #1309,ar3 */
    if (taken)                                             /* xc 2,tc */
        b = 374;                                           /* ld #374,b */
    taken = (*ar4 & 128) != 0;                             /* bitf *ar4,#128 */
    /* nop; nop */
    if (taken)                                             /* xc 2,tc */
        b = 498;                                           /* ld #498,b */
    tc6 = (*(volatile int *)0x3EC8 & 64) != 0;            /* bitf (TC held to bc) */
    taken = tc6;
    /* nop; nop */
    if (taken)                                             /* xc 2,tc */
        b = 548;                                           /* ld #548,b */
    *(volatile int *)0x2A84 = (int)(b & 0xFFFF);           /* stl b,*(0x2a84) */
    taken = (*(volatile int *)0x8 & 1) != 0;               /* bitf *(0x8),#1 */
    *ar3 &= -9;                                            /* andm (always runs) */
    if (!taken)                                            /* xc 2,ntc */
        *ar3 |= 8;                                         /* orm #8,*ar3 */
    a = (long)*ar2 >> 8;                                   /* ld *ar2,-8,a (arith) */
    *(volatile int *)0x2BFD = (int)(a & 0xFFFF);           /* stl a (low-16, exact) */
    a = (long)*ar2;                                        /* ld *ar2+0%,a */
    ar2 += ar0_live;
    a &= 255L;                                             /* and #255,a */
    ar4 = (int *)12032;                                    /* stm #12032,ar4 */
    *ar4++ = (int)a;                                       /* stl a,*ar4+ */
    a = (long)*(volatile int *)0x3EC8 & 64L;               /* ld; and #64,a (A>=0) */
    for (i = 0; i < 31; i++) {                             /* rpt #30 */
        *ar4++ = *ar2;                                     /* mvdd *ar2+0%,*ar4+ */
        ar2 += ar0_live;
    }
    if (a > 0) {                                           /* xc 2,agt */
        for (i = 0; i < 4; i++) {                           /* rpt #3 */
            *ar4++ = *ar2;
            ar2 += ar0_live;
        }
    }
    if (tc6) {                                               /* bc 0x3454,tc (TC held) */
        dispatcher_entry_2E2F();
        *(volatile int *)0x54F |= 1;                        /* orm #1 */
        frag_2E64();                                       /* b 0x2e64 (tail) */
        return;
    }
    ar6save = ar2;                                         /* mvmm ar2,ar6 */
    ar2 = (int *)12063;                                    /* stm #12063,ar2 */
    if (a > 0)                                             /* xc 2,agt */
        ar2 += 4;                                          /* mar *+ar2(0x4) */
    ar3 = (int *)10886;                                    /* stm #10886,ar3 */
    routine_434F(ar7_live);                                /* call 0x434f (dark) */
    *(volatile int *)0x2A84 = (int)(b & 0xFFFF);           /* stl b */
    *ar3 = 32767;                                          /* st #32767,*ar3 */
    ar2 = ar6save;                                         /* mvmm ar6,ar2 */
    dispatcher_entry_2E2F();                               /* call 0x2e2f */
    *(volatile int *)0x54F |= 1;                           /* orm #1,*(0x54f) */
    frag_2E64();                                           /* b 0x2e64 (tail) */
}
