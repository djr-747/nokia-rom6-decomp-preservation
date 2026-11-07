/* ROM6 0x7C57 CHECK_DISPATCH_7C57 -- 71w (span 7C57-7C9D, single entry).
 * Verified encoding: src/rom6/rf/7c57_check_dispatch_7c57.asm (recombine MATCH).
 * ORIGIN 0x7C57
 * EXPECT: F074 059E F94C 7D31 7713 2657 768B 2A84 E501 6082 00C0 F830 810A 6082 00B1 F830 810A 6082 00C1 F830 7D74 6082 00D9 7CF8 0008 06FB F830 80FC 6082 00D5 7CF8 0008 06FA F830 80FC 6082 00D3 7CF8 0008 06FC F830 80FC 6082 00DB 7CF8 0008 06FE F830 80FC 6082 0070 F830 7FF4 6082 00B0 F830 7CB6 6082 0080 F830 8038 6082 00E0 F830 80A3 E904 F074 4590 7683 000F FC00
 *
 * Intent: Message-code dispatch ladder on *AR2. Entry B (the cc
 * condition, tested 40-bit != 0) and AR2 (the code word, read
 * throughout, never stepped) live; entry A unread (no A ops;
 * dark calls clobber); void. Runs dark SUB_059E (call,
 * forward extern void); conditional call to dark 0x7D31 iff B
 * != 0 (cc bneq; NON-delayed per the op_cc/op_ccd split in the
 * oracle -- the following stm is ordinary code on both paths,
 * not a delay slot). AR3 = 9815 (stm); *AR3-- = 10884 (st,
 * AR3 to 9814); *AR3 = *AR2 (mvdd, no steps, 3273 shape).
 * Then the cmpm ladder, each TC = (*AR2 == K) (equality per
 * the 5362 cmpm precedent): 192/177 detour to dark 0x810A (bc
 * tc); 193 to dark 0x7D74; 217/213/211/219 each first copy
 * PROM[0x6FB/0x6FA/0x6FC/0x6FE] to cell *(0x8) (mvpd
 * program-read, prom_read_word extern per the 44bd
 * precedent) then run C-bound SUB_80FC with TC = 1 (bc tc
 * taken; sub_80FC takes int tc_live); 112 runs C-bound
 * FRAG_7FF4; 176 to dark 0x7CB6; 128 to dark 0x8038; 224 to
 * dark 0x80A3. Else B = 4 (ld); runs C-bound ROUTINE_4590
 * with B = 4 (call); *AR3 = 15 (st, AR3 still 9814); return.
 * A/B/ARs dead after (void); outs via cell 0x8, *AR3, calls.
 */
extern void sub_059E(void);                              /* dark, no symbol */
extern void frag_7D31(void);                             /* dark (cc target) */
extern void frag_810A(void);                             /* dark */
extern void frag_7D74(void);                             /* dark */
extern void sub_80FC(int tc_live);                       /* C-bound */
extern void frag_7FF4(void);                             /* C-bound */
extern void frag_7CB6(void);                             /* dark */
extern void frag_8038(void);                             /* dark */
extern void frag_80A3(void);                             /* dark */
extern void routine_4590(int b_in);                      /* C-bound */
extern int prom_read_word(int prog_addr);                /* mvpd (44bd precedent) */

void sub_7C57(long b_in, int *ar2_in)
{
    int *ar3;
    int tc;
    int *ar2 = ar2_in;
    long b = b_in;
    sub_059E();                                          /* call 0x59e (dark) */
    if (b != 0)                                          /* cc 0x7d31,bneq (non-delayed) */
        frag_7D31();
    ar3 = (int *)9815;                                   /* stm #9815,ar3 */
    *ar3-- = 10884;                                      /* st #10884,*ar3- */
    *ar3 = *ar2;                                         /* mvdd *ar2,*ar3 */
    tc = (*ar2 == 192);                                  /* cmpm *ar2,#192 */
    if (tc) {                                            /* bc 0x810a,tc */
        frag_810A();
        return;
    }
    tc = (*ar2 == 177);                                  /* cmpm *ar2,#177 */
    if (tc) {                                            /* bc 0x810a,tc */
        frag_810A();
        return;
    }
    tc = (*ar2 == 193);                                  /* cmpm *ar2,#193 */
    if (tc) {                                            /* bc 0x7d74,tc */
        frag_7D74();
        return;
    }
    tc = (*ar2 == 217);                                  /* cmpm *ar2,#217 */
    if (tc) {                                            /* bc 0x80fc,tc */
        *(volatile int *)0x8 = prom_read_word(0x6FB);    /* mvpd 0x6fb,*(0x8) */
        sub_80FC(1);
        return;
    }
    tc = (*ar2 == 213);                                  /* cmpm *ar2,#213 */
    if (tc) {                                            /* bc 0x80fc,tc */
        *(volatile int *)0x8 = prom_read_word(0x6FA);    /* mvpd 0x6fa,*(0x8) */
        sub_80FC(1);
        return;
    }
    tc = (*ar2 == 211);                                  /* cmpm *ar2,#211 */
    if (tc) {                                            /* bc 0x80fc,tc */
        *(volatile int *)0x8 = prom_read_word(0x6FC);    /* mvpd 0x6fc,*(0x8) */
        sub_80FC(1);
        return;
    }
    tc = (*ar2 == 219);                                  /* cmpm *ar2,#219 */
    if (tc) {                                            /* bc 0x80fc,tc */
        *(volatile int *)0x8 = prom_read_word(0x6FE);    /* mvpd 0x6fe,*(0x8) */
        sub_80FC(1);
        return;
    }
    tc = (*ar2 == 112);                                  /* cmpm *ar2,#112 */
    if (tc) {                                            /* bc 0x7ff4,tc */
        frag_7FF4();
        return;
    }
    tc = (*ar2 == 176);                                  /* cmpm *ar2,#176 */
    if (tc) {                                            /* bc 0x7cb6,tc */
        frag_7CB6();
        return;
    }
    tc = (*ar2 == 128);                                  /* cmpm *ar2,#128 */
    if (tc) {                                            /* bc 0x8038,tc */
        frag_8038();
        return;
    }
    tc = (*ar2 == 224);                                  /* cmpm *ar2,#224 */
    if (tc) {                                            /* bc 0x80a3,tc */
        frag_80A3();
        return;
    }
    b = 4;                                               /* ld #4,b */
    routine_4590((int)(b & 0xFFFFL));                    /* call 0x4590 */
    *ar3 = 15;                                           /* st #15,*ar3 */
    /* ret */
}
