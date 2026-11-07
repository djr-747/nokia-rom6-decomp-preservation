/* ROM6 0x6AE9 FRAG_6AE9 -- 61w dual-accumulate select with NORM + xc fill lanes.
 * Verified encoding: src/rom6/kernel/6ae9_frag_6ae9.asm (recombine MATCH).
 * ORIGIN 0x6AE9
 * EXPECT: 0984 770E 5555 23F8 000B F770 E803 F587 890E 5682 F48F 4E82 F066 0003 0084 8084 F074 05A2 60F8 250F 0022 F820 6B26 61F8 2639 0020 E907 19F8 3490 F200 3AD4 8813 E801 18F8 2628 FF30 7183 245C F845 6B15 7683 0000 F073 6B22 F310 0001 F830 6B22 FF4D 7083 3483 FF4B 7083 248D FF4E 7083 348B F074 712D F820 6B3F
 *
 * Intent: No own exit (falls into SPANHEAD_6B26; terminal bc-outs,
 * below). AR2/AR4 caller-live dark (params, 8b9d precedent). B -=
 * *AR4; T = 21845; B = round(cell 0xB x T)>>16 (mpyr, 22f3/8b9d
 * house form); B >>= 16 arithmetic (sfta, SXM flagged); A = 3;
 * B = min(A,B) signed (min b dst=B, 66c5 signed family);
 * T = B-low. A = 32-bit (*AR2,*AR2+1) (dld, SXM flagged on the MSW).
 * NORM shifts A by signed6(T) (op_norm_acc ground: T low 6 bits
 * signed, no T write; OVM saturation / SXM right-fill flagged).
 * Store 32-bit back (dst MSW + LSW above, no AR step). A = 3 x T
 * (mpy #3, FRCT dark flagged); A += *AR4 (add dual); *AR4 = A-low.
 * Runs dark SUB_05A2 (low-zone mini-kernel, no symbol, opaque).
 * TC = (cell 0x250F == 34) (cmpm); clear tail-calls SPANHEAD_6B26
 * (bc ntc; spanhead_6B26 asm-only forward extern). TC = (cell 0x2639
 * & 32) (bitf; survives the ld/and/add/stlms -- no TC writer --
 * so the later xc/bc-tc read it, a91c orm-neutral pattern extended).
 * B = 7 & cell 0x3490 (AND Smem sign-extended per 59dc); A = B + 15060
 * (add dual-immediate); AR3 = A-low. A = 1 & cell 0x2628. TC set runs
 * the mvdk (cell 0x245C = *AR3; xc 2 over the 2-word mvdk, then bc
 * always runs). A == 0 runs sub #1 (B--) then TC set joins the 712D
 * call (bc tc); TC clear runs the B-sign xc fill lanes (*AR3 =
 * *(0x3483/0x248D/0x348B) under beq/blt/bgt; exclusive) then the call.
 * A != 0 stores *AR3 = 0 and jumps to the call (b 0x6b22).
 * flag_gate_712D runs on all paths. TC clear (still the bitf TC)
 * tail-calls interior frag_6B3F (bc ntc; joins 6b26_spanhead_6b26
 * @+0x19, 28d6 precedent). Else falls into SPANHEAD_6B26 (shared
 * tail). T/TC/C dead after (noted); B/ARs/cells out. EXPECT from
 * the image.
 */
extern void sub_05A2(void);      /* dark, no symbol (low-zone mini-kernel) */
extern void spanhead_6B26(void); /* asm-only, joins 6b26_spanhead_6b26 */
extern void flag_gate_712D(void);
extern void frag_6B3F(void);     /* joins 6b26_spanhead_6b26 interior @+0x19 */

void frag_6AE9(int *ar2_in, int *ar4_in)
{
    long a;
    long b;
    int t;
    int tc;
    int sh;
    int *ar2 = ar2_in;
    int *ar3;
    int *ar4 = ar4_in;

    b -= (long)*ar4;                                             /* sub *ar4,b */
    t = 21845;                                                   /* stm #21845,t */
    b = ((long)*(volatile int *)0xB * (long)t + 0x4000L) >> 16;  /* mpyr *(0xb),b */
    b >>= 16;                                                    /* sfta b,-16 (arith, SXM flagged) */
    a = 3L;                                                      /* ld #3,a */
    if (a < b)                                                   /* min b (dst=B, signed) */
        b = a;
    t = (int)(b & 0xFFFFL);                                      /* stlm b,t */
    a = ((long)*ar2 << 16) | (long)(unsigned)*(ar2 + 1);        /* dld *ar2,a (SXM flagged) */
    sh = t & 63;                                                 /* norm a (op_norm_acc: signed6(T)) */
    if (sh >= 32)
        sh -= 64;
    if (sh >= 0)                                                 /* OVM saturation flagged */
        a <<= sh;
    else                                                         /* SXM right-fill flagged */
        a >>= -sh;
    *ar2 = (int)((a >> 16) & 0xFFFFL);                           /* dst a,*ar2 (MSW) */
    *(ar2 + 1) = (int)(a & 0xFFFFL);                             /* dst (LSW above) */
    a = 3L * (long)t;                                            /* mpy #3,a (FRCT flagged) */
    a += (long)*ar4;                                             /* add *ar4,a */
    *ar4 = (int)(a & 0xFFFFL);                                   /* stl a,*ar4 */
    sub_05A2();                                                  /* call 0x5a2 */
    tc = (*(volatile int *)0x250F == 34);                        /* cmpm *(0x250f),#34 */
    if (!tc) {                                                   /* bc 0x6b26,ntc */
        spanhead_6B26();
        return;
    }
    tc = ((*(volatile int *)0x2639 & 32) != 0);                  /* bitf *(0x2639),#32 */
    b = 7L;                                                      /* ld #7,b */
    b &= (long)*(volatile int *)0x3490;                          /* and *(0x3490),b (signed, 59dc) */
    a = b + 15060L;                                              /* add #15060,b,a */
    ar3 = (int *)(long)(a & 0xFFFFL);                            /* stlm a,ar3 */
    a = 1L;                                                      /* ld #1,a */
    a &= (long)*(volatile int *)0x2628;                          /* and *(0x2628),a */
    if (tc)                                                      /* xc 2,tc */
        *(volatile int *)0x245C = *ar3;                          /* mvdk *ar3,0x245c */
    if (a == 0) {                                                /* bc 0x6b15,aeq */
        b -= 1L;                                                 /* sub #1,b */
        if (tc) {                                                /* bc 0x6b22,tc */
            flag_gate_712D();                                    /* call 0x712d */
        } else {
            if (b == 0)                                          /* xc 2,beq */
                *ar3 = *(volatile int *)0x3483;                  /* mvkd 0x3483,*ar3 */
            if (b < 0)                                           /* xc 2,blt */
                *ar3 = *(volatile int *)0x248D;                  /* mvkd 0x248d,*ar3 */
            if (b > 0)                                           /* xc 2,bgt */
                *ar3 = *(volatile int *)0x348B;                  /* mvkd 0x348b,*ar3 */
            flag_gate_712D();                                    /* call 0x712d */
        }
    } else {
        *ar3 = 0;                                                /* st #0,*ar3 */
        flag_gate_712D();                                        /* b 0x6b22: call 0x712d */
    }
    if (!tc) {                                                   /* bc 0x6b3f,ntc (bitf TC) */
        frag_6B3F();
        return;
    }
    spanhead_6B26();                                             /* fall into 6B26 */
}
