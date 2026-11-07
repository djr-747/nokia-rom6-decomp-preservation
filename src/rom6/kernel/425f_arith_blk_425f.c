/* ROM6 0x425F ARITH_BLK_425F -- 89w.
 * Verified encoding: src/rom6/kernel/425f_arith_blk_425f.asm (recombine MATCH).
 * ORIGIN 0x425F
 * EXPECT: F074 0606 4A17 E727 6DEF 0005 4492 1A8A F000 0001 F162 0029 F340 7000 F520 F84C 4271 E800 8292 8092 E801 0082 F110 001A 8192 F495 FF4C 80E2 FFFF E801 0082 F110 0033 8192 F495 FF4C 80E2 FFFF F84C 4290 E801 0082 F110 D000 8192 F495 FF4C 80E2 FFFF E801 0087 F110 0066 8197 F495 FF4C 80E7 FFFF E801 0087 F110 0068 8197 F495 FF4C 80E7 FFFF E801 0087 F110 052E 8197 F495 FF4C 80E7 FFFF F84C 42B6 E801 0087 F110 0800 8197 F495 FF4C 80E7 FFFF 8A17 FC00
 *
 * Intent: Compare-store lane over two pointers. Runs
 * 0x606 (dark, extern); saves entry AR7 (pshm, hardware
 * state -- an ar7_saved local stands in per the 2D5E
 * precedent); AR7 = AR2 then += 5 (mvmm plus mar,
 * linear); A = *(AR2++) << 16 (ld Smem,16 per the 3EF3
 * precedent) OR *(AR2--) (or Smem,A reads the next word
 * then restores AR2 -- net AR2 unchanged, a 32-bit pair
 * load); A += 1 (add lk); B = 41 << 16 (ld lk,16);
 * B |= 28672 (or imm16); B = B - A (2-operand SUB -- only
 * the zero flag is consumed below, so the direction is
 * unobservable, noted); nonzero skips the zero-fill to
 * the 4271 lane (bc bneq; interior join). Else A = 0,
 * HIGH then LOW of A stored through AR2 (sth/stl pair,
 * both zero). Lane head (4271 and every stanza): A = 1,
 * A += *AR2 (add Smem,A, 1-word form), B = A - K (sub
 * lk), cell AR2 = B-low with AR2 post-incremented, then
 * B == 0 rewrites that same cell (AR2-1 via the -1
 * offset form) with A-low (xc 2,bneq covers the 2-word
 * stl; i.e. cell = (B == 0) ? A-low : B-low). K runs 26,
 * 51 on AR2 (the bc 0x4290,bneq skips the -12288
 * stanza to the AR7 lane), -12288 on AR2, then 102, 104,
 * 1326 on AR7 (the bc 0x42b6,bneq skips the 2048 stanza
 * to the epilogue), 2048 on AR7. Restores entry AR7
 * (popm; the stepped local dies) and returns. AR2/AR7
 * step on locals (plain +1); A/B locals, written before
 * read on every path; all dead at return (flagged).
 * Bound 425F-42B7.
 */
extern void sub_0606(void);

void arith_blk_425F(int *ar2_in, int ar7_live)
{
    int *ar2 = ar2_in;
    int *ar7;
    int ar7_saved = ar7_live;                        /* pshm ar7 */
    long a;
    long b;
    sub_0606();                                      /* call 0x606 */
    ar7 = ar2;                                       /* mvmm ar2,ar7 */
    ar7 += 5;                                        /* mar *+ar7(0x5) */
    a = (long)*ar2++ << 16;                          /* ld *ar2+,16,a */
    a |= (unsigned long)(unsigned)*ar2--;            /* or *ar2-,a */
    a += 1;                                          /* add #1,a */
    b = (long)41 << 16;                              /* ld #41,16,b */
    b |= 28672;                                      /* or #28672,b */
    if ((b - a) == 0) {                              /* bc 0x4271,bneq */
        a = 0;                                       /* ld #0,a */
        *ar2++ = (int)(((unsigned long)a >> 16) & 0xFFFF);  /* sth a,*ar2+ */
        *ar2++ = (int)(a & 0xFFFF);                  /* stl a,*ar2+ */
    }
    a = 1;                                           /* ld #1,a */
    a += (long)*ar2;                                 /* add *ar2,a */
    b = a - 26;                                      /* sub #26,a,b */
    *ar2++ = (int)(b & 0xFFFF);                      /* stl b,*ar2+ */
    /* nop */
    if (b == 0)                                      /* xc 2,bneq */
        *(ar2 - 1) = (int)(a & 0xFFFF);              /* stl a,*ar2(-1) */
    a = 1;                                           /* ld #1,a */
    a += (long)*ar2;                                 /* add *ar2,a */
    b = a - 51;                                      /* sub #51,a,b */
    *ar2++ = (int)(b & 0xFFFF);                      /* stl b,*ar2+ */
    /* nop */
    if (b == 0)                                      /* xc 2,bneq */
        *(ar2 - 1) = (int)(a & 0xFFFF);
    if (b != 0)                                      /* bc 0x4290,bneq */
        goto lane4290;
    a = 1;                                           /* ld #1,a */
    a += (long)*ar2;                                 /* add *ar2,a */
    b = a + 12288;                                   /* sub #-12288,a,b */
    *ar2++ = (int)(b & 0xFFFF);                      /* stl b,*ar2+ */
    /* nop */
    if (b == 0)                                      /* xc 2,bneq */
        *(ar2 - 1) = (int)(a & 0xFFFF);              /* stl a,*ar2(-1) */
lane4290:
    a = 1;                                           /* ld #1,a */
    a += (long)*ar7;                                 /* add *ar7,a */
    b = a - 102;                                     /* sub #102,a,b */
    *ar7++ = (int)(b & 0xFFFF);                      /* stl b,*ar7+ */
    /* nop */
    if (b == 0)                                      /* xc 2,bneq */
        *(ar7 - 1) = (int)(a & 0xFFFF);              /* stl a,*ar7(-1) */
    a = 1;                                           /* ld #1,a */
    a += (long)*ar7;                                 /* add *ar7,a */
    b = a - 104;                                     /* sub #104,a,b */
    *ar7++ = (int)(b & 0xFFFF);                      /* stl b,*ar7+ */
    /* nop */
    if (b == 0)                                      /* xc 2,bneq */
        *(ar7 - 1) = (int)(a & 0xFFFF);
    a = 1;                                           /* ld #1,a */
    a += (long)*ar7;                                 /* add *ar7,a */
    b = a - 1326;                                    /* sub #1326,a,b */
    *ar7++ = (int)(b & 0xFFFF);                      /* stl b,*ar7+ */
    /* nop */
    if (b == 0)                                      /* xc 2,bneq */
        *(ar7 - 1) = (int)(a & 0xFFFF);
    if (b != 0)                                      /* bc 0x42b6,bneq */
        goto epilogue;
    a = 1;                                           /* ld #1,a */
    a += (long)*ar7;                                 /* add *ar7,a */
    b = a - 2048;                                    /* sub #2048,a,b */
    *ar7++ = (int)(b & 0xFFFF);                      /* stl b,*ar7+ */
    /* nop */
    if (b == 0)                                      /* xc 2,bneq */
        *(ar7 - 1) = (int)(a & 0xFFFF);
epilogue:
    /* popm ar7 (restores entry AR7; stepped local dies) */
    (void)ar7_saved;
    /* ret */
}
