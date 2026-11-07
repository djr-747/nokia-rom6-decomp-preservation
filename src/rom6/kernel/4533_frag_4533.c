/* ROM6 0x4533 FRAG_4533 -- 28w.
 * Verified encoding: src/rom6/kernel/4533_frag_4533.asm (recombine MATCH).
 * ORIGIN 0x4533
 * EXPECT: F074 0594 7714 2F00 1094 F030 000F 7194 0013 1394 F3F8 6FF8 0015 0D81 F310 0001 8916 6DED 0006 F074 454F 7713 2F00 F274 2C88 7714 0074 FC00
 *
 * Intent: Nibble route into 454F. Runs dark SUB_0594; AR4 = 12032;
 * A = *AR4++ & 15 (imm positive, exact); cell0x13 = *AR4++;
 * B = unsigned *AR4++ >> 8 logical (ldu + SFTL per 381b, A/B
 * non-negative exact); cell0x15 = (B<<1) & 0xFFFF (STL-shift
 * single-word form, grounded per ti-c54x op_stl_shft_xmem:
 * logical left, store low, exact; B < 2^8, no overflow); B -= 1;
 * AR6 = B-low; AR5 += 6 (caller-live, dead after); calls SUB_454F
 * with (A, B, AR6) values (C: sub_454F); AR3 = 12032; dark
 * SUB_2C88 (calld, delay AR4 = 116); return. DP = 0 assumed for
 * the direct cells (flagged). Bound 4533-454E.
 */
extern void sub_0594(void);
extern void sub_454F(int a_in, int b_in, int ar6_in);
extern void sub_2C88(void);

void frag_4533(int ar5_live)
{
    int *ar4;
    int *ar3;
    int ar5 = ar5_live;
    int ar6;
    long a;
    long b;
    sub_0594();                                      /* call 0x594 (dark) */
    ar4 = (int *)12032;                              /* stm #12032,ar4 */
    a = (long)*ar4++;                                /* ld *ar4+,a */
    a &= 15;                                         /* and #15,a */
    *(volatile int *)0x13 = *ar4++;                  /* mvdk *ar4+,0x13 */
    b = (unsigned long)(unsigned)*ar4++;             /* ldu *ar4+,b */
    b = (unsigned long)b >> 8;                       /* sftl b,-8 (logical) */
    *(volatile int *)0x15 = (int)(((unsigned long)b << 1) & 0xFFFF); /* stl b,1,*(0x15) */
    b -= 1;                                          /* sub #1,b */
    ar6 = (int)(b & 0xFFFF);                         /* stlm b,ar6 */
    ar5 += 6;                                        /* mar *+ar5(0x6) */
    sub_454F((int)a, (int)b, ar6);                   /* call 0x454f */
    ar3 = (int *)12032;                              /* stm #12032,ar3 */
    /* calld delay: AR4 = 116 */
    sub_2C88();                                      /* calld 0x2c88 (dark) */
    /* ret */
    (void)ar3; (void)ar5;                            /* ARs dead at return (flagged) */
}
