/* ROM6 0x51D8 DISPATCH_HEAD_51D8 -- 52w (span 51D8-520B, two entries).
 * Verified encoding: src/rom6/rf/51d8_dispatch_head_51d8.asm (recombine MATCH).
 * ORIGIN 0x51D8
 * EXPECT: F074 059C 61F8 2F5C FF00 FA20 51E6 7712 050F 1082 F010 0002 E901 FC42 F830 51F1 4A0B 4A0C 4A0D E902 F074 070A 8A0D 8A0C 8A0B FE00 E900 8182 F274 425F 7712 0912 F074 57FE F074 52C4 F074 573B F074 520C 10F8 250F F030 00F0 60F8 0008 0020 F920 5755 F074 57A3 FC00
 *
 * Intent: RF dispatch head (caller 4BC9; two entry lanes -- the
 * retd@51F2 always returns, so the post-retd calld lane is a
 * separate exterior-entry routine per the 2917 mesh precedent,
 * flagged hypothesis). Head entry frag_51D8: runs dark SUB_059C
 * (no symbol, opaque). TC = (*(0x2F5C) & 0xFF00) != 0 (bitf with
 * mask #-256 = 0xFF00, 5d38 polarity). bcd 0x51e6,ntc: the 2-word
 * window (stm AR2 = 1295 local + ld A = MEM[AR2]) always runs
 * (520C word-count rule); NTC-taken joins L51E6. Fall: A -= 2
 * (sub); B = 1 (ld). rc ageq: A >= 0 returns (retd-less early
 * return; A-out flagged unbound). Else bc 0x51f1,tc (TC preserved
 * through ld/sub/rc): taken joins L51F1 mid-pop. Fall: pshm
 * bl/bh/bg (B save; balanced by popm on this path -- comments),
 * B = 2, runs dark SUB_070A (no symbol, opaque), popm restores B.
 * L51F1: popm bl -- fall path completes the restore; bc-taken
 * path pops unbalanced (B dead via the retd delay, SP unmodeled
 * in C intent -- comment-only, stack puzzle flagged for trace).
 * retd with delays B = 0 + MEM[AR2=1295] = 0 always runs, then
 * returns (both head paths end here; void). Mid entry frag_51F5
 * (hypothesis, flagged): calld 0x425f with delay stm AR2 = 2322
 * first; runs linked ARITH_BLK_425F (C: arith_blk_425F(ar2-ptr,
 * AR7-entry); AR7 dark entry-live, explicit param). Then linked
 * SUB_57FE, pooled DISPATCH_P_ENTRY (forward extern void
 * dispatch_p_entry), linked SUB_573B, linked FLAGLANE_COPY_520C
 * (C: flaglane_copy_520C(AR7-entry)). A = *(0x250F) & 240 (ld/
 * and); TC = (*(cell 0x8) == 32) (cmpm); TC clear calls linked
 * ROUTINE_5755 (cc 5755,ntc; C: routine_5755). Then pooled
 * SUB_57A3 (forward extern void sub_57A3); return. No entry
 * live-ins on the head (A/B recomputed, ARs untouched/set); the
 * mid lane takes entry AR7 only. Void throughout; dark outs
 * flagged.
 */
extern void sub_059C(void);                          /* dark, no symbol */
extern void sub_070A(void);                          /* dark, no symbol */
extern void arith_blk_425F(int *ar2_in, int ar7_live); /* linked C */
extern void sub_57FE(void);                          /* linked C */
extern void dispatch_p_entry(void);                  /* asm-only, forward extern */
extern void sub_573B(void);                          /* linked C */
extern void flaglane_copy_520C(int ar7_in);          /* linked C */
extern void routine_5755(void);                      /* linked C */
extern void sub_57A3(void);                          /* asm-only, forward extern */

void frag_51D8(void)
{
    long a;
    long b;
    int *ar2;
    int tc;
    sub_059C();                                      /* call 0x59c */
    tc = (*(volatile int *)0x2F5C & 0xFF00) != 0;    /* bitf *(0x2f5c),#-256 */
    ar2 = (int *)(long)1295;                         /* bcd delay 1 (always) */
    a = (long)*ar2;                                  /* bcd delay 2 (always) */
    if (!tc)                                         /* bcd 0x51e6,ntc taken */
        goto l51e6;
    a -= 2;                                          /* sub #2,a */
    b = 1;                                           /* ld #1,b */
l51e6:
    if (a >= 0)                                      /* rc ageq (A-out flagged) */
        return;
    if (tc)                                          /* bc 0x51f1,tc */
        goto l51f1;
    /* pshm bl/bh/bg (B save; balanced on this path, comments only) */
    b = 2;                                           /* ld #2,b */
    sub_070A();                                      /* call 0x70a */
    /* popm bg/bh (fall-path restore) */
l51f1:
    /* popm bl: fall completes the restore; taken pops unbalanced (comment-only, flagged) */
    b = 0;                                           /* retd delay 1: ld #0,b */
    *ar2 = 0;                                        /* retd delay 2: stl b,*ar2 */
    (void)b;
}

void frag_51F5(int ar7_in)
{
    long a;
    int *ar2;
    int tc;
    ar2 = (int *)(long)2322;                         /* calld delay: stm (always runs) */
    arith_blk_425F(ar2, ar7_in);                     /* calld 0x425f */
    sub_57FE();                                      /* call 0x57fe */
    dispatch_p_entry();                              /* call 0x52c4 */
    sub_573B();                                      /* call 0x573b */
    flaglane_copy_520C(ar7_in);                      /* call 0x520c */
    a = (long)*(volatile int *)0x250F;               /* ld *(0x250f),a */
    a &= 240L;                                       /* and #240,a */
    (void)a;
    tc = (*(volatile int *)0x8 == 32);               /* cmpm *(0x8),#32 */
    if (!tc)                                         /* cc 0x5755,ntc */
        routine_5755();
    sub_57A3();                                      /* call 0x57a3 */
}
