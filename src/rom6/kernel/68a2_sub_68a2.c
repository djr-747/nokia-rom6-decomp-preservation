/* ROM6 0x68A2 SUB_68A2 -- 21w.
 * Verified encoding: src/rom6/kernel/68a2_sub_68a2.asm (recombine MATCH).
 * ORIGIN 0x68A2
 * EXPECT: 61F8 051E 0800 11F8 2FD9 FF20 11F8 091B F784 F300 009F F495 F495 FF4B F300 00CC FC30 0986 FE00 E800 F586
 *
 * Intent: Clamp with early bail. TC = (cell0x51E & 2048) != 0
 * (bitf, 32b4 precedent); B = cell0x2FD9, TC set reloads B from
 * cell0x91B (xc 2,ntc skips the 2-word LD only, per ti-c54x op_xc;
 * 688C-class audit); B = -B (neg, always runs), B += 159;
 * B < 0 adds 204 (xc 2,blt covers the 2-word add only, exact);
 * TC set near-returns with B dead (rc tc; TC stale-preserved
 * through the neg/add/nop chain, exact -- only BITF-class ops
 * write TC); else B -= *AR6 (AR6-step-free read); the retd delays
 * run (A = 0, then B = max(B,0) -- MAX single writes B per the
 * 6657 min precedent); return. Bound 68A2-68B6.
 */
void sub_68A2(int *par6)
{
    int tc;
    long a;
    long b;
    tc = (*(volatile int *)0x51E & 2048) != 0;       /* bitf *(0x51e),#2048 */
    b = (long)*(volatile int *)0x2FD9;               /* ld *(0x2fd9),b */
    if (tc)                                          /* xc 2,ntc (skips LD only) */
        b = (long)*(volatile int *)0x091B;           /* ld *(0x91b),b */
    b = -b;                                          /* neg b (always runs) */
    b += 159;                                        /* add #159,b */
    /* nop; nop */
    if (b < 0)                                       /* xc 2,blt (covers add only) */
        b += 204;                                    /* add #204,b */
    if (tc)                                          /* rc tc (TC stale, exact) */
        return;
    b -= (long)*par6;                                /* sub *ar6,b */
    a = 0;                                           /* retd delay: ld #0,a (always runs) */
    if (b < a)                                       /* retd delay: max b (always runs) */
        b = a;
    /* retd */
    (void)b;                                         /* B dead at return (flagged) */
}
