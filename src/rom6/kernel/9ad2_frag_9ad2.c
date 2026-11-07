/* ROM6 0x9AD2 FRAG_9AD2 -- 34w mailbox/INTM-gated store lane.
 * Verified encoding: src/rom6/kernel/9ad2_frag_9ad2.asm (recombine MATCH).
 * ORIGIN 0x9AD2
 * EXPECT: 7312 21FB F274 2C88 7713 2F00 8A08 FA4C 9AF4 8A0B 8A12 F7BB 68F8 20FF 7FFF 61F8 0008 0001 F820 9AE9 69F8 20FF 8000 10F8 20FE F500 81F8 20FE 7312 21FB F020 FFFF F6BB FC00
 *
 * Intent: INTM-gated mailbox publish with a BNEQ sliver
 * exit. Cell 0x21FB = entry AR2 (MVMD); deferred call
 * 0x2C88 (2-word call-through span to 0x622, asm-owned, no
 * C entry -- provisional link name) with AR3 = 12032 in
 * the delay slots; AL popped at the return address; BL
 * and AR2 popped in the BCD delay slots -- if B != 0 the
 * branch transfers to the 9AF4 sliver (C entry frag_9AF4,
 * returns int; branch transfer, modeled terminal). Else:
 * INTM = 1 (ssbx, no C form -- hardware, flagged); cell
 * 0x20FF &= 0x7FFF; TC = bit0 of cell 0x08 (BITF); TC
 * clear skips to the LD leg at 9AE9 (interior join,
 * byte-verified); else cell 0x20FF |= 0x8000; LD leg: A =
 * cell 0x20FE, A += B, cell 0x20FE = BL (A computed then
 * dead -- stored value is B-low, flagged); cell 0x21FB =
 * AR2; A = -1; INTM = 0 (rsbx); return. Entries F073
 * @9ABD/@9ACB per asm header.
 * (Wave-13: CALLD/BCD delay-vs-return-address order per
 * the 2-delay-word rule; EXPECT from the image.)
 */
extern void sub_2C88(void); /* 2-word call-through span to 0x622, asm-verified, no C entry yet */
extern int frag_9AF4(void);

void frag_9AD2(void)
{
    long a;
    long b;  /* popm bl (bcd delay 1; caller B, dark, flagged) */
    int *ar2;  /* popm ar2 (bcd delay 2; caller handoff, dark, flagged) */
    int *ar3;
    int al;  /* popm al (return address: entry AL, dark, flagged) */
    int tc;

    *(volatile int *)0x21FB = (int)ar2;                        /* mvmd ar2,0x21fb (entry AR2; overwritten by popm below) */
    ar3 = (int *)12032;                                        /* calld delay: stm #12032,ar3 (fills both delay words) */
    sub_2C88();                                                /* calld 0x2c88 */
    /* (return address: popm al above in decl) */
    /* (bcd delays: popm bl / popm ar2 run here) */
    if (b != 0) {                                              /* bcd 0x9af4,bneq (issue-time B; delay pops run either way) */
        frag_9AF4();                                           /* (branch transfer to 9AF4 sliver, not a call) */
        return;
    }
    /* ssbx st1,intm (INTM = 1, no C form, flagged) */
    *(volatile int *)0x20FF &= 32767;                          /* andm #32767,*(0x20ff) */
    tc = (*(volatile int *)0x08 & 1) != 0;                     /* bitf *(0x8),#1 */
    if (!tc)                                                   /* bc 0x9ae9,ntc */
        goto lld;
    *(volatile int *)0x20FF |= -32768;                         /* orm #-32768,*(0x20ff) */
lld:
    a = (long)*(volatile int *)0x20FE;                         /* ld *(0x20fe),a (9AE9 join) */
    a += b;                                                    /* add a,b (A dead after, flagged) */
    *(volatile int *)0x20FE = (int)(b & 0xFFFFL);             /* stl b,*(0x20fe) */
    *(volatile int *)0x21FB = (int)ar2;                        /* mvmd ar2,0x21fb */
    a = -1;                                                    /* ld #-1,a */
    /* rsbx st1,intm (INTM = 0) */
    /* ret */
    (void)al;
}
