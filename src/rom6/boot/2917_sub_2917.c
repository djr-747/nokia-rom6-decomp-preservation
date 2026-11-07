/* ROM6 0x2917 SUB_2917 -- 54w (span 2917-294C; the header's 38w is stale).
 * Verified encoding: src/rom6/boot/2917_sub_2917.asm (recombine MATCH).
 * ORIGIN 0x2917
 * EXPECT: 60F8 2656 0000 F830 291E F074 3AED 60F8 250F 0022 F820 2929 76F8 366F 0000 76F8 37B0 0000 76F8 2656 0000 F073 294B F074 A5F2 F073 294B F074 A615 F074 A639 F073 294B F073 294B F273 2940 7711 3492 7711 3491 4481 61F8 3EC8 0020 F920 3CD2 F073 294B 68F8 2639 FDFF F073 283D
 *
 * Intent: Boot clear/dispatch mesh (TRACE shows heads at 2917 plus
 * a rare 291C lane; the 2917-294B range carries further heads per
 * the header). Head: TC = (*(0x2656) == 0) (cmpm); set joins L291E
 * (bc tc). Else runs pooled PORT0_TXN_CALLER (forward extern void
 * port0_txn_caller; file 3aed_port0_txn_caller; 291C is both the
 * fall-through and the rare TRACE entry). L291E: TC =
 * (*(0x250F) == 34) (cmpm); clear joins L2929 (bc ntc). Else zero
 * cells 0x366F/0x37B0/0x2656 (3x st #0) then tail to L294B (b).
 * Exterior-entry hypothesis lanes (no fall-through reaches them;
 * TRACE range-heads support, flagged): L292E runs pooled SUB_A5F2
 * then tails to L294B; L2932 runs pooled SUB_A615 then SUB_A639
 * (linked C: sub_A639) then tails to L294B; L2938 tails to L294B.
 * L293A (hypothesis entry): bd 0x2940 unconditional delayed
 * branch -- the 2-word stm #13458,ar1 delay always runs, then
 * jumps; the 293E stm #13457,ar1 is dead under bd-always-taken
 * (no branch sources, omitted with bytes verified, flagged).
 * L2940: A = *(AR1=13458) << 16 (ld *ar1,16,a); TC = (*(0x3EC8)
 * & 32) != 0 (bitf); TC clear calls pooled PORT4850_SEQ (cc
 * 0x3cd2,ntc; forward extern void port4850_seq; file
 * 3cd2_port4850_seq) then joins L294B (b). The 2948 andm is dead
 * (2946-b jumps over it, no branch sources, omitted with bytes
 * verified, flagged). L294B: tail to dark 0x283D (b; forward
 * extern void frag_283D per the 2867 precedent). A/B dead after
 * (void); AR1 local (stm-created 13458, not carried).
 */
extern void port0_txn_caller(void);                  /* pooled */
extern void sub_A5F2(void);                          /* asm-only, forward extern */
extern void sub_A615(void);                          /* asm-only, forward extern */
extern void sub_A639(void);                          /* linked C */
extern void port4850_seq(void);                      /* asm-only, forward extern */
extern void frag_283D(void);                         /* dark tail (2867 precedent) */

void sub_2917(void)
{
    long a;
    int *ar1;
    int tc;
    if (*(volatile int *)0x2656 == 0)                /* cmpm; bc 0x291e,tc */
        goto l291e;
    port0_txn_caller();                              /* call 0x3aed (291C lane) */
l291e:
    if (*(volatile int *)0x250F != 34)               /* cmpm; bc 0x2929,ntc */
        goto l2929;
    *(volatile int *)0x366F = 0;                      /* st #0,*(0x366f) */
    *(volatile int *)0x37B0 = 0;                      /* st #0,*(0x37b0) */
    *(volatile int *)0x2656 = 0;                      /* st #0,*(0x2656) */
    goto l294b;                                      /* b 0x294b */
l292e:                                               /* exterior entry (hypothesis, flagged) */
    sub_A5F2();                                      /* call 0xa5f2 */
    goto l294b;
l2932:                                               /* exterior entry (hypothesis, flagged) */
    sub_A615();                                      /* call 0xa615 */
    sub_A639();                                      /* call 0xa639 */
    goto l294b;                                      /* (2936 b, same target) */
l2938:                                               /* exterior entry (hypothesis, flagged) */
    goto l294b;                                      /* b 0x294b */
l293a:                                               /* exterior entry (hypothesis, flagged) */
    ar1 = (int *)(long)13458;                        /* bd delay: stm (always runs) */
    (void)ar1;
    goto l2940;                                      /* bd 0x2940 */
    /* 293E stm #13457,ar1: dead under bd-always-taken (flagged) */
l2940:
    a = (long)*ar1 << 16;                            /* ld *ar1,16,a */
    (void)a;
    tc = (*(volatile int *)0x3EC8 & 32) != 0;         /* bitf *(0x3ec8),#32 */
    if (!tc)                                         /* cc 0x3cd2,ntc */
        port4850_seq();
    goto l294b;                                      /* b 0x294b */
    /* 2948 andm #-513: dead (2946-b jumps over; flagged) */
l294b:
    frag_283D();                                     /* b 0x283d */
}
