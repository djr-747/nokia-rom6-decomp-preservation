/* ROM6 ORIGIN 0x4C41 (115w): FRAG_4C41 -- staged fill with far-call pair.
 * Verified encoding: src/rom6/kernel/4c41_frag_4c41.asm (recombine MATCH).
 * EXPECT: F110 00C0 F84C 4CB4 F074 0670 7711 0038 71F8 264C 0013 F274 5B18 7712 2F80 E808 F274 4DA7 7716 0004 F981 A86A 7712 3053 7713 3447 F274 4F5F 7711 0001 4BF8 3447 4BF8 3448 7712 3052 7713 311F ECD2 E545 F274 92F4 7713 311F 7712 2F80 771A 0006 F272 4C79 7713 09C8 1292 7182 0009 F472 8093 68F8 09CE 0003 F981 A886 8BF8 09D0 8BF8 09CF 68F8 09D0 0001 69F8 051D 0004 7712 2F5C 7692 0000 7713 09C8 EC06 E598 F074 0670 7712 2F63 7713 2F56 F274 8220 7711 0006 76F8 2F57 0000 7714 2F3C E742 771A 000D ED18 F272 4CAA 7713 0009 9488 E581 8494 76F8 2F1F 00C0 F274 4F6E 7713 2F3C F073 4D9C
 *
 * Intent: B = A - 192; nonzero tail-enters FRAG_4CB4 with entry AR3
 * (bc bneq; AR3 untouched on this path). Dark call 0x670. AR1 = 56;
 * cell 0x13 = cell 0x264C; calld
 * ROUTINE_5B18 (delay AR2 = 12160: par2 = (int *)12160, par3 = entry
 * AR3, ar1_live = 56). A = 8; calld dark 0x4DA7 (delay AR6 = 4, dead);
 * far call 0x1A86A (void per the 36F0 fcall precedent). AR2 = 12371;
 * AR3 = 13383; calld dark 0x4F5F (delay AR1 = 1; forward extern).
 * Push cells 0x3447/0x3448 (pshd pair, C locals). AR2 = 12370;
 * AR3 = 12575; rpt #210: 211x *AR3-- = *AR2-- (descending mvdd).
 * calld SUB_92F4 (delay AR3 = 12575): par3 = (int *)12575, A = 8
 * assumed preserved through the dark calld + fcall (flagged, cf the
 * 92F4 file's own preserve-through-dark convention). AR2 = 12160;
 * BRC = 6; rptbd 0x4C79 (delay AR3 = 2504 once; RSA = PC+2 = 0x4C75,
 * REA = 0x4C79, block inclusive, 7 passes): A = unsigned *AR2++;
 * cell 0x9 = *AR2; A arith>>= 14 (sfta, exact: ldu zeroes high);
 * *AR3++ = A-low. cell 0x9CE &= 3 (andm). Far call 0x1A886.
 * Pop into cell 0x9D0 (younger push = 0x3448 value) then cell 0x9CF
 * (0x3447 value, LIFO). cell 0x9D0 &= 1; cell 0x51D |= 4;
 * AR2 = 12124; cell AR2 = 0 with post-inc; AR3 = 2504; rpt #6:
 * 7x *AR2++ = *AR3++. Dark call 0x670. AR2 = 12131; AR3 = 12118;
 * calld dark 0x8220 (delay AR1 = 6). cell 0x2F57 = 0. AR4 = 12092;
 * AR2 = AR4-value (mvmm). BRC = 13; ASM = -8 (ld #-8,asm);
 * rptbd 0x4CAA (delay AR3 = 9 once; RSA = 0x4CA8, REA = 0x4CAA,
 * inclusive, 14 passes): A = *AR2++ << 8 (LD-acc-shift, sign-extended
 * per the 39A4 ld-16 precedent); fixed cell 9 = *AR2++ (mvdd to
 * unstepped *AR3); *AR4++ = ASM-shifted A-low, shifted = A >> 8
 * (asm_live < 0 branch of the 4EBC form, 32-bit exact: |A| < 2^24).
 * cell 0x2F1F = 192; calld dark 0x4F6E (delay AR3 = 12092; forward
 * extern); tail-branch dark 0x4D9C (b). AR3-entry caller param;
 * AR1/AR2/AR4/ASM set in-span; AR6 preset dead; A/B internal after
 * the head test (dark A/B liveness flagged); TC untouched.
 * Bound 4C41-4CB3 (abuts 4CB4).
 */
extern void frag_4CB4(int *ar3_in);
extern void sub_0670(void);
extern void routine_5B18(int *par2, int *par3, int ar1_live);
extern void frag_4DA7(void);
extern void far_1A86A(void);
extern void frag_4F5F(void);
extern void sub_92F4(int *par3_in, long a_live);
extern void far_1A886(void);
extern void frag_8220(void);
extern void frag_4F6E(void);
extern void frag_4D9C(void);

void frag_4C41(long a_live_in, int *ar3_in)
{
    long a = a_live_in;
    long b;
    long shifted;
    int asm_live;
    int i;
    int *ar2;
    int *ar3;
    int *ar4;
    int save3447;
    int save3448;

    b = a - 192L;                                      /* sub #192,a,b */
    if (b != 0) {                                      /* bc 0x4cb4,bneq */
        frag_4CB4(ar3_in);                             /* tail (AR3 untouched) */
        return;
    }
    sub_0670();                                        /* call 0x670 (dark) */
    /* AR1 = 56 (stm; consumed by the 5B18 call) */
    *(volatile int *)0x13 = *(volatile int *)0x264C;   /* mvdk */
    /* calld 0x5b18 (delay stm #12160,ar2 runs first) */
    routine_5B18((int *)12160, ar3_in, 56);
    a = 8L;                                            /* ld #8,a */
    /* calld 0x4da7 (delay stm #4,ar6 runs first; dark, AR6 dead) */
    frag_4DA7();
    far_1A86A();                                       /* fcall 0x1a86a */
    ar2 = (int *)12371;                                /* stm #12371,ar2 */
    ar3 = (int *)13383;                                /* stm #13383,ar3 */
    /* calld 0x4f5f (delay stm #1,ar1 runs first; forward extern) */
    frag_4F5F();
    save3447 = *(volatile int *)0x3447;                 /* pshd *(0x3447) */
    save3448 = *(volatile int *)0x3448;                /* pshd *(0x3448) */
    ar2 = (int *)12370;                                /* stm #12370,ar2 */
    ar3 = (int *)12575;                                /* stm #12575,ar3 */
    for (i = 0; i < 211; i++)                          /* rpt #210 */
        *ar3-- = *ar2--;                               /* mvdd *ar2-,*ar3- */
    /* calld 0x92f4 (delay stm #12575,ar3 runs first) */
    sub_92F4((int *)12575, 8L);
    ar2 = (int *)12160;                                /* stm #12160,ar2 */
    /* stm #6,brc; rptbd 0x4c79 (delay stm #2504,ar3 runs once) */
    ar3 = (int *)2504;
    for (i = 0; i < 7; i++) {                          /* [0x4c75,0x4c79] */
        a = (unsigned long)(unsigned)*ar2++;           /* ldu *ar2+,a */
        *(volatile int *)0x9 = *ar2;                   /* mvdk *ar2,0x9 */
        a >>= 14;                                      /* sfta a,-14 (exact) */
        *ar3++ = (int)(a & 0xFFFF);                    /* stl a,*ar3+ */
    }
    *(volatile int *)0x9CE &= 3;                       /* andm #3 */
    far_1A886();                                       /* fcall 0x1a886 */
    *(volatile int *)0x9D0 = save3448;                 /* popd (LIFO) */
    *(volatile int *)0x9CF = save3447;                 /* popd (LIFO) */
    *(volatile int *)0x9D0 &= 1;                       /* andm #1 */
    *(volatile int *)0x51D |= 4;                       /* orm #4 */
    ar2 = (int *)12124;                                /* stm #12124,ar2 */
    *ar2++ = 0;                                        /* st #0,*ar2+ */
    ar3 = (int *)2504;                                 /* stm #2504,ar3 */
    for (i = 0; i < 7; i++)                            /* rpt #6 */
        *ar2++ = *ar3++;                               /* mvdd *ar3+,*ar2+ */
    sub_0670();                                        /* call 0x670 (dark) */
    ar2 = (int *)12131;                                /* stm #12131,ar2 */
    ar3 = (int *)12118;                                /* stm #12118,ar3 */
    /* calld 0x8220 (delay stm #6,ar1 runs first; dark, flagged) */
    frag_8220();
    *(volatile int *)0x2F57 = 0;                       /* st #0,*(0x2f57) */
    ar4 = (int *)12092;                                /* stm #12092,ar4 */
    ar2 = ar4;                                         /* mvmm ar4,ar2 */
    /* stm #13,brc */
    asm_live = -8;                                     /* ld #-8,asm */
    /* rptbd 0x4caa (delay stm #9,ar3 runs once: fixed dest cell 9) */
    for (i = 0; i < 14; i++) {                         /* [0x4ca8,0x4caa] */
        a = (long)*ar2++ << 8;                         /* ld *ar2+,8,a */
        *(volatile int *)0x9 = *ar2++;                 /* mvdd *ar2+,*ar3 */
        shifted = (asm_live >= 0) ? (a << asm_live) : (a >> -asm_live);
                                                       /* stl a,asm (4EBC) */
        *ar4++ = (int)(shifted & 0xFFFF);              /* stl a,asm,*ar4+ */
    }
    *(volatile int *)0x2F1F = 192;                     /* st #192 */
    /* calld 0x4f6e (delay stm #12092,ar3 runs first; forward extern) */
    frag_4F6E();
    frag_4D9C();                                       /* b 0x4d9c tail */
}
