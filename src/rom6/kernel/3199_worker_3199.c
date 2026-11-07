/* ROM6 0x3199 WORKER_3199 -- 205w.
 * Verified encoding: src/rom6/kernel/3199_worker_3199.asm (recombine MATCH).
 * ORIGIN 0x3199
 * EXPECT: 61F8 051D 0100 FC30 68F8 0537 FE97 61F8 3EC8 0010 F820 31BC 10DA F030 0F1F F55C F330 00F0 8911 F030 001F 80F8 058B F640 F310 0050 F84D 31BA F540 F310 0030 F84C 31BB E880 FD20 4811 7714 263B F030 00F0 6884 FF0F 1A84 8084 61F8 0011 0040 E87C 69F8 054F 0020 FF30 F020 012B F830 31D8 61F8 3EC8 0040 F495 F495 FD30 E8AE 61F8 0011 0020 68F8 051F FFF0 FF30 F020 0176 61F8 3EC8 0010 F820 31EB 60F8 0011 0030 F073 31EE 61F8 0011 0080 7713 050C 11F8 3EC8 F330 0040 7683 0001 FF4E 7683 0000 F820 3200 F020 01F2 FF4E F020 0224 61F8 3EC8 1000 F820 320C 60F8 0011 0050 F820 320C F020 01D9 61F8 3EC8 0010 F820 321B 60F8 0011 0040 F830 321E 60F8 0011 0020 F073 321E 61F8 0011 0060 F820 3223 76F8 050C 0200 80F8 050D 76F8 050E 0000 F074 05B6 61F8 058F 000F F820 3237 68F8 054F FFDF 69F8 2453 0002 F073 325D 61F8 3EC8 0040 F495 F495 7714 000B FF30 7714 0007 7713 0DE9 7693 7FFF F071 0052 8093 FF30 EC35 8093 6C8C 3245 7713 054F 7714 051E 6183 0008 6884 BFFF FF30 6984 4000 6883 FFF7 68F8 051E FFF7 61F8 3EC8 0010 F820 3266 F074 2E2F F073 2E64
 *
 * Intent: Multi-lane select with fill loop and twin tails.
 * Bit 8 of cell 0x51D set returns at once (bitf plus rc tc,
 * grounded); else cell 0x537 &= 0xFE97 (andm #-361). Bit 4
 * of cell 0x3EC8 clear skips the scale lane to 31BC
 * (bc 0x31bc,ntc). Scale lane: A = *(AR2) with AR2 += AR0
 * (ld +0% read-then-step per the 351d convention, circular
 * wrap needs caller-live BK, linear modeled flagged);
 * A &= 3871 (upper cleared); B = A >> 4 (ld a,-4,b per the
 * 5b18/3938 LD-acc-shift precedent, arithmetic, exact:
 * A >= 0); B &= 240; AR1 = B-low (stlm, dead after --
 * the only reader is the dead ldm lane below, noted);
 * A &= 31; cell 0x58B = A-low; A = B; B = A - 80 (sub lk);
 * zero runs A = 128, else B = A - 48 (the bc 0x31bb,bneq
 * is a fall-through join: taken and fall both reach 31BB,
 * so only the beq fork matters). xc 1,ntc would reload A
 * from AR1 iff TC set, but TC is still clear from the head
 * bitf (no TC-writing op between, and the rc already
 * returned on TC set) so the ldm is a dead lane (noted,
 * not modeled). AR4 = 9787; A &= 240; cell AR4 &= 0xFF0F
 * (andm #-241); A |= *AR4 (or Smem); cell AR4 = A-low.
 * Bit 6 of cell 0x11 to TC; A = 124; cell 0x54F |= 32;
 * TC set skips A = 299 (xc 2,tc covers the 2-word ld) and
 * joins the 31D8 lane (bc tc), else bit 6 of cell 0x3EC8
 * to TC and TC set skips A = 174 (xc 1,tc covers the
 * 1-word ld). 31D8 lane: bit 5 of cell 0x11 to TC; cell
 * 0x51F &= 0xFFF0; TC clear runs A = 374 else the xc
 * skips it (xc 2,tc). Bit 4 of cell 0x3EC8 clear joins the
 * 31EB lane (bc ntc); else the cmpm #48 runs with its TC
 * unused (falls into the join, noted) and branches to
 * 31EE. 31EB lane: bit 7 of cell 0x11 to TC (the fall-through
 * path instead carries the cmpm #48 equality result as its TC;
 * each path feeds the 3200-lane test with its own TC). Join 31EE:
 * AR3 = 1292; B = cell 0x3EC8 & 64; cell AR3 = 1, B <= 0
 * rewrites it to 0 (xc 2,bgt covers the 2-word st); TC
 * clear joins the 3200 lane (bc ntc), else A = 498 and
 * B <= 0 reloads A = 548 (xc 2,bgt). 3200 lane: bit 12 of
 * cell 0x3EC8 clear joins 320C (bc ntc); else TC =
 * (cell 0x11 == 80) (cmpm, oracle: TC = equality) and
 * mismatch joins 320C; else A = 473. 320C lane: bit 4 of
 * cell 0x3EC8 clear joins 321B; else TC = (cell == 64) set
 * joins 321E; else the cmpm #32 runs with its TC unused
 * (noted) and branches to 321E. 321B lane: TC = (cell 0x11
 * & 96) != 0 (bitf ANY-bit per the oracle); clear joins
 * 3223 (bc ntc), else cell 0x50C = 512. 3223/321E join:
 * cell 0x50D = A-low; cell 0x50E = 0; runs 0x5B6 (dark,
 * extern); TC = (cell 0x58F & 15) != 0; clear joins the
 * 3237 lane (bc ntc), else cell 0x54F &= 0xFFDF, cell
 * 0x2453 |= 2, and branches to the 325D tail (b 0x325d).
 * 3237 lane: bit 6 of cell 0x3EC8 to TC; AR4-count = 11,
 * TC clear reloads 7 (xc 2,tc); AR3 = 3561; cell AR3 =
 * 32767 with AR3 post-incremented. Fill loop (latch at
 * 324B): A = 0 with BRC = 82 (rptz: dst-acc zero plus RC
 * per the oracle) then 83 stores of A-low with AR3
 * post-incremented (rpt #82 + stl); TC (still the 3237
 * bitf result: no TC-writing op in the body, flagged)
 * clear runs 54 more stores (rpt #53 + stl), set skips
 * them (xc 2,tc, 351d precedent); the banz latch ALWAYS
 * decrements the count and takes iff the pre-decrement
 * value is nonzero (oracle branch-Sind helper plus CPU
 * RED tests), so the body runs up to 12 (or 8) passes.
 * Then AR3 = 1359, AR4 = 1310; bit 3 of *AR3 clear skips
 * cell AR4 |= 16384 (xc 2,tc); cell AR3 &= 0xFFF7, cell
 * 0x51E &= 0xFFF7; bit 4 of cell 0x3EC8 clear returns
 * (bc 0x3266,ntc reaches the ret); else runs 0x2E2F
 * (extern) and tail-branches to frag_2E64 (extern). 325D
 * tail: bit 4 of cell 0x3EC8 clear returns; else runs
 * 0x2E2F and tail-branches to frag_2E64. ARs/A/B/TC dead
 * at every exit (flagged). Bound 3199-3265.
 */
extern void sub_05B6(void);
extern void sub_2E2F(void);
extern void frag_2E64(void);

void worker_3199(int ar0_live, int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar3;
    int *ar4;
    int ar1v;
    int ar4cnt;
    long a;
    long b;
    int i;
    if ((*(volatile int *)0x51D & 256) != 0)         /* bitf; rc tc */
        return;
    *(volatile int *)0x537 &= 65175;                 /* andm #-361 */
    if ((*(volatile int *)0x3EC8 & 16) == 0)         /* bc 0x31bc,ntc */
        goto lane31BC;
    a = (long)*ar2;                                  /* ld *ar2+0%,a */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    a &= 3871;                                       /* and #3871,a */
    b = a >> 4;                                      /* ld a,-4,b (arith) */
    b &= 240;                                        /* and #240,b */
    ar1v = (int)(b & 0xFFFF);                        /* stlm b,ar1 (dead) */
    a &= 31;                                         /* and #31,a */
    *(volatile int *)0x58B = (int)(a & 0xFFFF);      /* stl a */
    a = b;                                           /* ld b,a */
    b = a - 80;                                      /* sub #80,b */
    if (b == 0)                                      /* bc 0x31ba,beq */
        a = 128;                                     /* ld #128,a */
    else {
        b = a;                                       /* ld a,b */
        b -= 48;                                     /* sub #48,b */
    }
    /* bc 0x31bb,bneq: join, no effect */
    /* xc 1,ntc: TC clear here always (head rc), ldm dead */
lane31BC:
    ar4 = (int *)9787;                               /* stm #9787,ar4 */
    a &= 240;                                        /* and #240,a */
    *ar4 &= 65295;                                   /* andm #-241 */
    a |= (long)*ar4;                                 /* or *ar4,a */
    *ar4 = (int)(a & 0xFFFF);                        /* stl a,*ar4 */
    if ((*(volatile int *)0x11 & 64) != 0) {         /* bitf #64 */
        a = 124;                                     /* ld #124,a */
        *(volatile int *)0x54F |= 32;                /* orm #32 */
        goto lane31D8;                               /* bc 0x31d8,tc (xc skips) */
    }
    a = 124;                                         /* ld #124,a */
    *(volatile int *)0x54F |= 32;                    /* orm #32 */
    a = 299;                                         /* xc 2,tc clear: ld runs */
    if ((*(volatile int *)0x3EC8 & 64) == 0)         /* bitf #64; xc 1,tc */
        a = 174;                                     /* ld #174,a */
lane31D8:
    if ((*(volatile int *)0x11 & 32) == 0)           /* bitf #32; xc 2,tc */
        a = 374;                                     /* ld runs on TC clear */
    if ((*(volatile int *)0x3EC8 & 16) == 0) {        /* bc 0x31eb,ntc */
        if ((*(volatile int *)0x11 & 128) != 0)      /* bitf #128 (31EB path) */
            goto join31EEtcSet;
        goto join31EEtcClear;
    }
    if (*(volatile int *)0x11 != 48)                 /* cmpm #48 (join path) */
        goto join31EEtcClear;
join31EEtcSet:
    b = (long)*(volatile int *)0x3EC8;               /* ld *(0x3ec8),b */
    b &= 64;                                         /* and #64,b */
    ar3 = (int *)1292;                               /* stm #1292,ar3 */
    *ar3 = 1;                                        /* st #1,*ar3 */
    if (b <= 0)                                      /* xc 2,bgt */
        *ar3 = 0;                                    /* st #0,*ar3 */
    goto lane498;
join31EEtcClear:
    b = (long)*(volatile int *)0x3EC8;               /* ld *(0x3ec8),b */
    b &= 64;                                         /* and #64,b */
    ar3 = (int *)1292;                               /* stm #1292,ar3 */
    *ar3 = 1;                                        /* st #1,*ar3 */
    if (b <= 0)                                      /* xc 2,bgt */
        *ar3 = 0;                                    /* st #0,*ar3 */
    goto lane3200;
lane498:
    a = 498;                                         /* ld #498,a */
    if (b <= 0)                                      /* xc 2,bgt */
        a = 548;                                     /* ld #548,a */
lane3200:
    if ((*(volatile int *)0x3EC8 & 4096) == 0)       /* bc 0x320c,ntc */
        goto lane320C;
    if (*(volatile int *)0x11 != 80)                 /* cmpm #80; bc ntc */
        goto lane320C;
    a = 473;                                         /* ld #473,a */
lane320C:
    if ((*(volatile int *)0x3EC8 & 16) == 0)         /* bc 0x321b,ntc */
        goto lane321B;
    if (*(volatile int *)0x11 == 64)                 /* cmpm #64; bc tc */
        goto lane321E;
    goto lane321E;                                   /* cmpm #32 (TC unused) */
lane321B:
    if ((*(volatile int *)0x11 & 96) == 0)           /* bc 0x3223,ntc */
        goto lane3223;
    *(volatile int *)0x50C = 512;                    /* st #512 */
lane321E:
lane3223:
    *(volatile int *)0x50D = (int)(a & 0xFFFF);      /* stl a */
    *(volatile int *)0x50E = 0;                      /* st #0 */
    sub_05B6();                                      /* call 0x5b6 */
    if ((*(volatile int *)0x58F & 15) == 0)          /* bc 0x3237,ntc */
        goto lane3237;
    *(volatile int *)0x54F &= 65503;                 /* andm #-33 */
    *(volatile int *)0x2453 |= 2;                    /* orm #2 */
    goto tail325D;                                   /* b 0x325d */
lane3237:
    {
        int tc = (*(volatile int *)0x3EC8 & 64) != 0;  /* bitf #64 */
        ar4cnt = 11;                                 /* stm #11,ar4 */
        if (!tc)                                     /* xc 2,tc */
            ar4cnt = 7;                              /* stm #7,ar4 */
        ar3 = (int *)3561;                           /* stm #3561,ar3 */
        *ar3++ = 32767;                              /* st #32767,*ar3+ */
        for (;;) {                                   /* latch 324B */
            a = 0;                                   /* rptz a,#82 */
            for (i = 0; i < 83; i++)                 /* rpt #82 + stl */
                *ar3++ = 0;
            if (!tc) {                               /* xc 2,tc */
                for (i = 0; i < 54; i++)             /* rpt #53 + stl */
                    *ar3++ = 0;
            }
            {                                        /* banz (always decs) */
                int taken = (ar4cnt != 0);
                ar4cnt--;
                if (!taken)
                    break;
            }
        }
    }
    ar3 = (int *)1359;                               /* stm #1359,ar3 */
    ar4 = (int *)1310;                               /* stm #1310,ar4 */
    *ar4 &= 49151;                                   /* andm #-16385,*ar4 */
    if ((*ar3 & 8) != 0)                             /* bitf *ar3,#8; xc 2,tc */
        *ar4 |= 16384;                               /* orm #16384,*ar4 */
    *ar3 &= 65527;                                   /* andm #-9,*ar3 */
    *(volatile int *)0x51E &= 65527;                 /* andm #-9 */
    if ((*(volatile int *)0x3EC8 & 16) == 0)         /* bc 0x3266,ntc */
        return;
    sub_2E2F();                                      /* call 0x2e2f */
    frag_2E64();                                      /* b 0x2e64 (tail) */
    return;
tail325D:
    if ((*(volatile int *)0x3EC8 & 16) == 0)         /* bc 0x3266,ntc */
        return;
    sub_2E2F();                                      /* call 0x2e2f */
    frag_2E64();                                      /* b 0x2e64 (tail) */
}
