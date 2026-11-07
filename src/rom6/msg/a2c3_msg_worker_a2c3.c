/* ROM6 0xA2C3 MSG_WORKER_A2C3 -- 158w port polled worker, one EXPECT.
 * Verified encoding: src/rom6/msg/a2c3_msg_worker_a2c3.asm (recombine MATCH).
 * ORIGIN 0xA2C3
 * EXPECT: F074 0654 11F8 2628 F230 0001 F845 A2E1 61F8 022C 0001 F820 A2E1 F330 C000 F84C A2E1 F7BB 74F8 000B 0003 F330 FFFE F495 75F8 000B 0003 EC16 F495 F6BB 74F8 0008 0010 80F8 265A 69F8 2639 0200 7712 0543 768A 0000 60F8 250F 0022 F820 A319 61F8 2628 0001 F820 A2FD 76F8 37DD 0000 76F8 37DB 0000 60F8 34BF 0000 F820 A308 F062 B00F F162 B024 F073 A31D 60F8 34BF 0004 F820 A313 F062 B01C F162 B033 F073 A31D F062 B015 F162 B02B F073 A31D F062 B000 F162 B007 7713 0546 8293 8383 F074 3EE1 60F8 250F 0022 F110 1052 FF30 F110 1142 12F8 0547 8813 7682 0000 1283 F84F A337 6D93 7682 0001 1283 F495 75F8 0008 000F EC0F F495 6182 0001 F920 3986 F074 AC4C 11F8 2628 F230 0001 FC45 7713 2639 6983 0102 6883 FFF7 E800 80F8 262D 80F8 262F 60F8 250F 0022 F820 A360 80F8 34C4 80F8 34C5 80F8 34C6 80F8 34C7 FC00
 *
 * Intent: Port-3/16 polled measurement worker with a reading-indexed flag
 * table. Entry via calls F074@A269/A2AC (no live-in state: AR2/AR3 set
 * inside). Runs HELPER_0654 (call 0x654). B = cell 0x2628, A = B & 1
 * (and #1,b,a); A == 0 exits to the A2E1 converge (bc aeq); bit 0 of
 * cell 0x22C clear exits (bitf + bc ntc); B &= -16384 (keep top two
 * bits), nonzero exits (bc bneq). INTM = 1 (hardware; restored after the
 * block): B = port 3 (portr 3,*(0xb): PORTR Smem-only read), B &= -2,
 * port 3 = B, 23 idle cycles (rpt #22 + nop); INTM = 0. *(0x8) = port 16;
 * *(0x265A) = A-low (the preserved cell-0x2628 bit0 from the head).
 * *(0x2639) |= 512. AR2 = 1347; *(1347) = 0, AR2-- (st pair).
 * Four constant lanes by (id == 34, cell 0x34BF): id==34 + bit0-of-2628
 * lane zeroes 0x37DD/0x37DB then picks (A,B) = (-20465,-20444),
 * (-20452,-20429), or (-20459,-20437) << 16 by cell 0x34BF (0/4/other);
 * id!=34 lane uses (-20480,-20473) << 16 (LD #lk,16: SXM-widened << 16).
 * *(1350) = A-high, *(1351) = B-high (sth pair). A = PORT13 reading
 * (call 0x3EE1: A-OUT PROVEN by the 3EE3 loop shape, which rewrites both
 * accumulators unconditionally -- preservation is impossible; the bleq
 * chain below is live only under A-out, confirming it; the 2983.c
 * preserve-A assumption is fixed this wave). TC = (id == 34) threads
 * through the 3EE1 call (memory-op TC preservation, flagged);
 * B = A - (TC ? 4178 : 4418)
 * (xc 2,tc skips the second sub). AR3 = A-unsigned (ldu *(0x547),a;
 * reading as address -- threshold-table indexing, HYPOTHESIS class
 * above); *(1346) = 0; A = *(AR3). B <= 0 skips the over-threshold arm
 * (bc bleq to the A337 nop): else AR3++, *(1346) = 1, A = *(AR3) (dead,
 * transcribed). Port 15 = *(0x8); 16 idle cycles. Bit 0 of *(1346) clear
 * runs SUB_3986 (bitf + cc ntc, TC fresh -- no threading); then runs
 * PORTSEQ_AC4C (call 0xac4c). B = *(0x2628), A = B & 1, zero returns
 * (rc aeq). *(AR3) |= 258 then &= -9 (orm/andm: bit set/clear on the
 * reading-indexed cell). *(0x262D) = *(0x262F) = 0. id != 34 returns
 * (bc ntc to RET); else *(0x34C4..0x34C7) = 0, return.
 * Ports 3/15/16 direct-mapped (extern ops per 2ACC). Bound A2C3-A360.
 */
extern void helper_0654(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern int port13_stable_read(void);
extern void sub_3986(void);
extern void portseq_AC4C(void); /* joins ac4c_portseq_ac4c; see docs/evidence/extern-triage.md */
extern int port_read_3(void);                                         /* HW port 3 (supervisor cell per 2088 span); no ROM definition */
extern void port_write_3(int v);                                      /* HW port 3 (supervisor cell per 2088 span); no ROM definition */
extern int port_read_16(void);
extern void port_write_15(int v);

void msg_worker_A2C3(void)
{
    long a;
    long b;
    int tc;
    int *par2 = (int *)1347;
    int *par3;
    int ar3addr;

    helper_0654();                                         /* call 0x654 */
    b = (long)*(volatile int *)0x2628;                   /* ld */
    a = b & 1L;                                          /* and #1,b,a */
    if (a != 0) {                                        /* bc aeq lane */
        tc = (*(volatile int *)0x22C & 1) != 0;          /* bitf */
        if (tc) {                                        /* bc ntc */
            b &= -16384L;                                /* and #-16384 */
            if (b == 0) {                                /* bc bneq */
                /* ssbx intm (hardware, no C form) */
                b = (long)port_read_3();          /* portr 3,*(0xb) */
                *(volatile int *)0xB = (int)(b & 0xFFFF);
                b &= -2;                             /* and #-2,b */
                /* nop */
                port_write_3((int)(b & 0xFFFF));  /* portw *(0xb),3 */
                /* rpt #22 + nop: 23 idle cycles */
                /* rsbx intm (hardware, no C form) */
            }
        }
    }
    /* A2E1 converge (A = cell-0x2628 bit0 preserved above) */
    *(volatile int *)0x8 = port_read_16();        /* portr 16,*(0x8) */
    *(volatile int *)0x265A = (int)(a & 0xFFFF);         /* stl a */
    *(volatile int *)0x2639 |= 512;                      /* orm */
    *par2-- = 0;                           /* st #0,*ar2- (AR2=1346) */
    tc = (*(volatile int *)0x250F == 34);                /* cmpm */
    if (!tc) {                                           /* bc ntc */
        a = -20480L << 16;                        /* A319: ld,16 */
        b = -20473L << 16;
    } else {
        tc = (*(volatile int *)0x2628 & 1) != 0;         /* bitf */
        if (tc) {                                        /* bc ntc */
            *(volatile int *)0x37DD = 0;                  /* st */
            *(volatile int *)0x37DB = 0;                 /* st */
            tc = (*(volatile int *)0x34BF == 0);          /* cmpm */
            if (!tc) {                                   /* bc ntc */
                tc = (*(volatile int *)0x34BF == 4);      /* cmpm */
                if (!tc) {                               /* bc ntc */
                    a = -20459L << 16;              /* A313 lane */
                    b = -20437L << 16;
                } else {
                    a = -20452L << 16;              /* A308 lane */
                    b = -20429L << 16;
                }
            } else {
                a = -20465L << 16;                  /* A2FD lane */
                b = -20444L << 16;
            }
        } else {
            a = -20480L << 16;                    /* A2FD-ntc: as A319 */
            b = -20473L << 16;
        }
    }
    /* A31D converge */
    par3 = (int *)1350;                          /* stm #1350,ar3 */
    *par3++ = (int)((a >> 16) & 0xFFFF);         /* sth a,*ar3+ */
    *par3 = (int)((b >> 16) & 0xFFFF);           /* sth b,*ar3 */
    a = (long)port13_stable_read();     /* call 0x3ee1 (A-out, proven) */
    tc = (*(volatile int *)0x250F == 34);                /* cmpm */
    b = a - 4178L;                               /* sub #4178,a,b */
    if (!tc)                                     /* xc 2,tc */
        b = a - 4418L;                           /* sub #4418,a,b */
    a = (unsigned long)(unsigned)*(volatile int *)0x547; /* ldu */
    ar3addr = (int)(a & 0xFFFF);                 /* stlm a,ar3 */
    *par2 = 0;                                   /* st #0,*ar2 (=1346) */
    a = (unsigned long)(unsigned)*(volatile int *)ar3addr; /* ldu */
    if (b > 0) {                                 /* bc bleq (B = above) */
        ar3addr++;                               /* mar *ar3+ */
        *par2 = 1;                               /* st #1,*ar2 */
        a = (unsigned long)(unsigned)*(volatile int *)ar3addr; /* ldu */
    }
    /* A337: nop */
    port_write_15(*(volatile int *)0x8);          /* portw *(0x8),15 */
    /* rpt #15 + nop: 16 idle cycles */
    tc = (*par2 & 1) != 0;                       /* bitf *ar2,#1 */
    if (!tc)                                     /* cc 0x3986,ntc */
        sub_3986();
    portseq_AC4C();                              /* call 0xac4c */
    b = (long)*(volatile int *)0x2628;           /* ld */
    a = b & 1L;                                  /* and #1,b,a */
    if (a == 0)                                  /* rc aeq */
        return;
    *(volatile int *)ar3addr |= 258;             /* orm #258,*ar3 */
    *(volatile int *)ar3addr &= -9;              /* andm #-9,*ar3 */
    *(volatile int *)0x262D = 0;                         /* stl */
    *(volatile int *)0x262F = 0;                         /* stl */
    if (*(volatile int *)0x250F != 34)           /* cmpm; bc ntc */
        return;
    *(volatile int *)0x34C4 = 0;                         /* stl */
    *(volatile int *)0x34C5 = 0;                         /* stl */
    *(volatile int *)0x34C6 = 0;                         /* stl */
    *(volatile int *)0x34C7 = 0;                         /* stl */
    /* ret @0xa360 */
}
