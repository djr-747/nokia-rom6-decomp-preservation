/* ROM6 0x2D8F SUB_2D8F -- 85w (span 2D8F-2DE3, ret @2DE3/2DE4-boundary).
 * Verified encoding: src/rom6/boot/2d8f_isr_2d8f.asm (recombine MATCH).
 * ORIGIN 0x2D8F
 * EXPECT: F074 0624 11F8 0853 6FF8 0852 0E20 FC45 F300 0800 8912 F020 0300 0282 F517 F210 0851 F847 2DA4 F310 0052 F310 0800 7719 0052 81F8 054C 13D2 61F8 054D 0008 F230 00FF F3F8 FC20 4A19 4A08 4A09 4A0A 4A0B 4A0C 4A0D 4A12 F030 00FF F2A8 8810 7713 2F00 4810 7693 0400 8093 F84D 2DD2 F200 0001 F0FF F010 0001 881A F495 F495 F072 2DD1 10D2 8093 F300 0004 7712 2F00 E814 7710 00F4 F074 93CE 8A12 8A0D 8A0C 8A0B 8A0A 8A09 8A08 8A19 FC00
 *
 * Intent: HPI-word ISR worker (caller 2E94; name sub_ per the 2D5E
 * subroutine precedent). Runs dark SUB_0624 (no symbol, opaque).
 * B = *(0x853) (HPI word); A = B - *(0x852) (sub Smem,src,dst, 3
 * words); A == 0 returns (rc aeq). B += 2048 (add); AR2 = B-low
 * (stlm: computed pointer). A = 768 (ld); A += sign-extended
 * *AR2 (adds, sign-add per 4b81); B = B_old + (A >> 9 arith) (add
 * a,-9,b; SXM dark in ISR context, arith assumed, flagged). A =
 * B - 2129 (sub); A <= 0 joins L2DA4 (bc aleq, in-span label).
 * (Wave-12 correction: add a,-9,b is B_old + (A >> 9) per the
 * op_arithmetic leaf, not A + (A >> 9).)
 * Else B -= 82. L2DA4: B -= 2048; BK = 82 (stm: circular size;
 * BSA dark, linear ++ in C with wrap flagged -- local, not
 * carried); MEM[0x54C] = B-low (stl); B = MEM[*AR2++] unsigned
 * (ldu circular); TC = (*(0x54D) & 8) != 0 (bitf, 5d38 polarity);
 * A = B & 255 (and); B >>= 8 logical (sftl; B >= 0 from ldu, so
 * logical == arith, exact); TC clear returns (rc ntc). Full
 * context save pshm bk/al/ah/ag/bl/bh/bg/ar2 (balanced by the
 * 8x popm; entry values never read through the copies -- comments
 * only per 5d38). A &= 255; A = B | (A << 8) (or b,8,a). AR0 =
 * A-low (stlm); AR3 = 12032 local; A = AR0-value (ldm ar0,a, 50B2
 * scalar precedent); MEM[AR3++] = 1024 (st); MEM[AR3++] = A-low
 * (stl). A == 0 joins L2DD2 (bc beq, in-span label). Else A = B +
 * 1 (add #1,b,a); A >>= 1 logical (sftl; A >= 0 since B >= 0,
 * exact); A -= 1 (sub); BRC = A-low (stlm). Settle nops. rptb
 * 0x2dd1: single-word block [2DD1,2DD1] (RSA = word after the
 * 2-word op, RPTB non-delayed; REA = 2DD1) -- BRC+1 loads of A =
 * MEM[*AR2++] unsigned (ld circular, last wins), then one stl
 * after the loop. L2DD2: MEM[*AR3++] = A-low (stl). B += 4 (add
 * #4,b, 66e2 precedent). AR2 = 12032 reseat; A = 20; AR0 = 244
 * (stm/ld immediates; B/AR0 dead in 93ce's contract, opaque,
 * flagged). TC-result = msg_classify_by_caller(12032-ptr,
 * SP-entry, 20) (linked C; SP-entry dark ISR context, explicit
 * param; int return ignored, TC-out not carried -- flagged).
 * popm restores all 8; return. A/B dead after (void); AR2/AR3/BK
 * locals (computed/const, not carried).
 */
extern void sub_0624(void);                          /* dark, no symbol */
extern int msg_classify_by_caller(int *par2, int *sp_live, long a_live);

void sub_2D8F(int *sp_in)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int *ar0;
    int bk;
    int brc;
    int tc;
    int tc_result;
    int i;
    sub_0624();                                      /* call 0x624 */
    b = (long)*(volatile int *)0x853;                /* ld *(0x853),b */
    a = b - (long)*(volatile int *)0x852;            /* sub *(0x852),b,a */
    if (a == 0)                                      /* rc aeq */
        return;
    b += 2048L;                                      /* add #2048,b */
    ar2 = (int *)(long)(b & 0xFFFF);                 /* stlm b,ar2 */
    a = 768L;                                        /* ld #768,a */
    a += (long)*ar2;                                 /* adds *ar2,a */
    b = b + (a >> 9);                                /* add a,-9,b: dst_old + src>>9 per op_arithmetic (corrected wave-12; SXM/arith flagged) */
    a = b - 2129L;                                   /* sub #2129,b,a */
    if (a > 0)                                       /* bc 0x2da4,aleq fall */
        b -= 82L;                                    /* sub #82,b */
    /* l2da4: */
    b -= 2048L;                                      /* sub #2048,b */
    bk = 82;                                         /* stm #82,bk (not carried) */
    (void)bk;
    *(volatile int *)0x54C = (int)(b & 0xFFFF);      /* stl b,*(0x54c) */
    b = (long)(unsigned)*ar2++;                      /* ldu *ar2+%,b (wrap flagged) */
    tc = (*(volatile int *)0x54D & 8) != 0;          /* bitf *(0x54d),#8 */
    a = b & 255L;                                    /* and #255,b,a */
    b = (long)((unsigned long)b >> 8);               /* sftl b,-8 (B>=0, exact) */
    if (!tc)                                         /* rc ntc */
        return;
    /* pshm bk/al/ah/ag/bl/bh/bg/ar2 (balanced by popm; comments only) */
    a &= 255L;                                       /* and #255,a */
    a = b | (a << 8);                                /* or b,8,a */
    ar0 = (int *)(long)(a & 0xFFFF);                 /* stlm a,ar0 */
    ar3 = (int *)(long)12032;                        /* stm #12032,ar3 */
    a = (long)ar0;                                   /* ldm ar0,a */
    *ar3++ = 1024;                                   /* st #1024,*ar3+ */
    *ar3++ = (int)(a & 0xFFFF);                      /* stl a,*ar3+ */
    if (a == 0)                                      /* bc 0x2dd2,beq */
        goto l2dd2;
    a = b + 1;                                       /* add #1,b,a */
    a = (long)((unsigned long)a >> 1);               /* sftl a,-1 (A>=0, exact) */
    a -= 1;                                          /* sub #1,a */
    brc = (int)(a & 0xFFFF);                         /* stlm a,brc */
    /* nop; nop (settles) */
    for (i = 0; i <= brc; i++)                       /* rptb 0x2dd1, BRC+1 loads */
        a = (long)(unsigned)*ar2++;                  /* ld *ar2+%,a (last wins) */
l2dd2:
    *ar3++ = (int)(a & 0xFFFF);                      /* stl a,*ar3+ */
    b += 4;                                          /* add #4,b */
    tc_result = msg_classify_by_caller((int *)(long)12032, sp_in, 20L);
    (void)tc_result;                                 /* TC result ignored in-span */
    /* popm ar2/bg/bh/bl/ag/ah/al/bk (restore entry state) */
}
