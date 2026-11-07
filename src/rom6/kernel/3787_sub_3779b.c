/* ROM6 0x3787 SUB_3787 -- 24w (interior of SUB_3779).
 * Verified encoding: src/rom6/kernel/3787_sub_3779b.asm (recombine MATCH).
 * ORIGIN 0x3787
 * EXPECT: 10DA 68F8 051F FFF0 7714 263B 6884 FF0F F134 00F0 F3FC 1B84 8184 F030 001F 80F8 058B 69F8 0589 0001 F074 2E2F F073 2E64
 *
 * Intent: Nibble pack plus flag set. A = *AR2, AR2 += AR0-live
 * (circular +0%, modulo wrap needs caller-live BK, linear modeled
 * flagged); cell0x51F &= -16; AR4 = 9787, cell &= -241; B =
 * A & (240 << 4) (AND imm-shift: imm zero-extended at shift, per
 * ti-c54x op_logical_immediate); B >>= 4 logical (SFTL, 381b
 * precedent; B non-negative here, exact); B |= cell; cell = B-low;
 * A &= 31 (upper already zero from the 16-bit load, exact);
 * cell0x58B = A-low; cell0x589 |= 1; dark call 0x2E2F then dark tail
 * 0x2E64 (AR liveness through the dark call flagged). Cells absolute
 * per the da40 precedent (DP = 0 assumed, flagged). Bound 3787-379E.
 */
extern void sub_2E2F(void);
extern void frag_2E64(void);

void sub_3787(int *ar2, int ar0_live)
{
    int *ar4;
    long a;
    long b;
    a = (long)*ar2;                                  /* ld *ar2+0%,a */
    ar2 += ar0_live;                                 /* +0% advance (wrap flagged) */
    *(volatile int *)0x51F &= -16;                   /* andm #-16,*(0x51f) */
    ar4 = (int *)9787;                               /* stm #9787,ar4 */
    *ar4 &= -241;                                    /* andm #-241,*ar4 */
    b = a & (240L << 4);                             /* and #240,4,a,b */
    b = (long)((unsigned long)b >> 4);               /* sftl b,-4 (logical) */
    b |= (long)*ar4;                                 /* or *ar4,b */
    *ar4 = (int)(b & 0xFFFF);                        /* stl b,*ar4 */
    a &= 31;                                         /* and #31,a */
    *(volatile int *)0x58B = (int)(a & 0xFFFF);      /* stl a,*(0x58b) */
    *(volatile int *)0x589 |= 1;                     /* orm #1,*(0x589) */
    sub_2E2F();                                      /* call 0x2e2f (dark) */
    frag_2E64();                                     /* b 0x2e64 (dark tail) */
}
