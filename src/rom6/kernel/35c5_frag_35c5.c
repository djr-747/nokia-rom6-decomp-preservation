/* ROM6 0x35C5 FRAG_35C5 + FRAG_35CB -- 68w.
 * Verified encoding: src/rom6/kernel/35c5_leaf_35c5.asm (recombine MATCH).
 * ORIGIN 0x35C5
 * EXPECT: 71DA 0578 F074 2E2F F073 2E64 7714 263A 7713 051C 4811 F0E8 F030 1800 F845 35DB 1AF8 051F 80F8 051F F844 35EE 61F8 0011 0004 F820 35E4 6984 0200 F073 35EE 61F8 0011 0002 F820 35EC 6983 0002 FF20 6983 0001 61F8 0011 0001 F830 3608 6883 FFFC 6884 FDFF 68F8 051F E7FF 10F8 2510 F030 00F0 F010 00C0 F844 3608 76F8 2EFE 0001 76F8 0B67 0001 FC00
 *
 * Intent: Copy-head plus select-body, two entries. The 35C5
 * head (cell 0x578 = *AR2 with AR2 += AR0 -- mvdk +0%
 * source per the 351d convention: read pre-step address,
 * step by AR0, circular wrap needs caller-live BK, linear
 * modeled flagged; then runs 0x2E2F and tail-branches to
 * frag_2E64) always exits, so the 35CB body is a second
 * entry in this file (sled convention; its entry state is
 * externally driven, flagged). Body: AR4 = 9786, AR3 =
 * 1308 (entry ARs clobbered); A = AR1-value (ldm, AR1
 * live-in); A <<= 8 logical (sftl); A &= 6144 (upper
 * cleared); zero re-enters the 35DB lane (bc aeq); else
 * A |= cell 0x51F, cell 0x51F = A-low, nonzero exits to
 * the 35EE tail (bc aneq); 35DB lane: bit 2 of cell 0x11
 * clear jumps to the 35E4 lane (bc ntc); else cell AR4 |=
 * 512 and joins 35EE; 35E4 lane: bit 1 of cell 0x11 clear
 * jumps to 35EC (bc ntc); else cell AR3 |= 2, and TC clear
 * skips cell |= 1 (xc 2,ntc covers the 2-word orm); 35EC
 * lane: bit 0 of cell 0x11 set returns (bc 0x3608,tc);
 * else cell AR3 &= 0xFFFC, cell AR4 &= 0xFDFF, cell 0x51F
 * &= 0xE7FF (andm immediates zero-extended); A = cell
 * 0x2510 & 240 - 192; nonzero returns (bc aneq); else
 * cells 0x2EFE and 0x0B67 = 1, return. BITF single-bit
 * masks read TC exactly. Bound 35C5-3608.
 */
extern void sub_2E2F(void);
extern void frag_2E64(void);

void frag_35C5(int ar0_live, int *ar2_in)
{
    int *ar2 = ar2_in;
    *(volatile int *)0x578 = *ar2;               /* mvdk *ar2+0%,0x578 */
    ar2 += ar0_live;                             /* +0% (wrap flagged) */
    sub_2E2F();                                  /* call 0x2e2f */
    frag_2E64();                                  /* b 0x2e64 (tail) */
}

void frag_35CB(int ar1_live)
{
    int *ar4 = (int *)9786;                          /* stm #9786,ar4 */
    int *ar3 = (int *)1308;                          /* stm #1308,ar3 */
    long a;
    a = (long)ar1_live;                              /* ldm ar1,a */
    a <<= 8;                                         /* sftl a,8 (logical) */
    a &= 6144;                                       /* and #6144,a */
    if (a != 0) {                                    /* bc 0x35db,aeq */
        a |= (long)*(volatile int *)0x51F;           /* or *(0x51f),a */
        *(volatile int *)0x51F = (int)(a & 0xFFFF);  /* stl a,*(0x51f) */
        if (a != 0)                                  /* bc 0x35ee,aneq */
            goto tail35EE;
    }
    if ((*(volatile int *)0x11 & 4) == 0) {          /* bitf; bc ntc */
        if ((*(volatile int *)0x11 & 2) == 0)        /* bitf; bc ntc */
            goto tail35EC;
        *ar3 |= 2;                                   /* orm #2,*ar3 */
        if ((*(volatile int *)0x11 & 2) != 0)        /* xc 2,ntc (TC live) */
            *ar3 |= 1;                               /* orm #1,*ar3 */
        goto tail35EC;
    }
    *ar4 |= 512;                                     /* orm #512,*ar4 */
tail35EE:
    if ((*(volatile int *)0x11 & 1) != 0)            /* bitf; bc tc */
        return;
tail35EC:
    *ar3 &= 65532;                                   /* andm #-4 */
    *ar4 &= 65023;                                   /* andm #-513 */
    *(volatile int *)0x51F &= 59391;                 /* andm #-6145 */
    a = (long)*(volatile int *)0x2510 & 240;         /* ld; and #240,a */
    a -= 192;                                        /* sub #192,a */
    if (a != 0)                                      /* bc 0x3608,aneq */
        return;
    *(volatile int *)0x2EFE = 1;                     /* st #1 */
    *(volatile int *)0x0B67 = 1;                     /* st #1 */
    /* ret */
}
