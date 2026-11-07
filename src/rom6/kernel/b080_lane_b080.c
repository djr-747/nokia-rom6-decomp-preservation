/* ROM6 0xB080 LANE_B080 -- 33w dispatcher gate chain.
 * Verified encoding: src/rom6/kernel/b080_lane_b080.asm (recombine MATCH).
 * ORIGIN 0xB080
 * EXPECT: F074 067A F074 A2C3 F074 A4DE F84C B0A9 F074 A8BF 60F8 2510 00C0 F820 B0A9 F981 A839 F981 A425 61F8 051F 1800 F830 B09D 61F8 051C 0003 F820 B0A1 F074 A87F F073 B0A9
 *
 * Intent: Sequential gate chain dispatching to the B0A9
 * join, the B09D tail, or the B0A1 span. Call 0x67A (low-
 * region RAM: zero in mask dump); run msg worker A2C3 and
 * msg setup C (C entries exist); BC exits to the B0A9 join
 * when A != 0; run wrap A8BF (B live-in dark); CMPM TC =
 * (cell 0x2510 == 192), BC exits to B0A9 when TC clear;
 * far calls to uploaded pages 0x1A839/0x1A425 (XPC,
 * permanently extern); BITF any-bit TC on cell 0x51F mask
 * 6144, BC joins the A87F tail at B09D (which is exactly
 * the call-a87f word per the image map) when TC set; BITF
 * cell 0x51C mask 3, BC transfers to the B0A1 span head
 * (C entry frag_B0A1 -- branch transfer, modeled
 * terminal); else run wrap A87F and tail-branch to B0A9.
 * B0A9 joins the B0A1 span at B0A1+8, past its 5-word C
 * head (asm-owned tail, no C entry -- provisional join
 * extern). All three B0A9 paths converge there.
 * (Wave-13: EXPECT taken from the image word map, not
 * hand-composed.)
 */
extern void sub_067A(void); /* low-region: zero in mask dump (verified); see docs/evidence/extern-triage.md */
extern void msg_worker_A2C3(void);
extern void msg_setup_C(void);
extern void wrap_A8BF(int b_live);
extern void far_1A839(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */
extern void far_1A425(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */
extern void wrap_A87F(void);
extern void frag_B0A1(void);
extern void frag_B0A1_tail(void); /* joins B0A1 span at B0A9 (past the 5w C head), asm-verified, no C entry yet */

void lane_B080(void)
{
    long a;  /* live-in (dark, flagged) */
    long b;  /* live-in for wrap_A8BF (dark, flagged) */
    int tc;

    sub_067A();                                                /* call 0x67a (RAM) */
    msg_worker_A2C3();                                         /* call 0xa2c3 */
    msg_setup_C();                                             /* call 0xa4de */
    if (a != 0)                                                /* bc 0xb0a9,bneq */
        goto lb0a9;
    wrap_A8BF((int)(b & 0xFFFFL));                             /* call 0xa8bf (B-value in, dark) */
    tc = (*(volatile int *)0x2510 == 192);                     /* cmpm *(0x2510),#192 */
    if (!tc)                                                   /* bc 0xb0a9,ntc */
        goto lb0a9;
    far_1A839();                                               /* fcall 0x1a839 (uploaded) */
    far_1A425();                                               /* fcall 0x1a425 (uploaded) */
    tc = ((*(volatile int *)0x51F & 6144) != 0);               /* bitf *(0x51f),#6144 (any-bit) */
    if (tc)                                                    /* bc 0xb09d,tc (-> call a87f word) */
        goto la87f;
    tc = ((*(volatile int *)0x51C & 3) != 0);                  /* bitf *(0x51c),#3 */
    if (!tc) {                                                 /* bc 0xb0a1,ntc */
        frag_B0A1();                                           /* (branch transfer to B0A1 head, not a call) */
        return;
    }
la87f:
    wrap_A87F();                                               /* call 0xa87f */
lb0a9:
    frag_B0A1_tail();                                          /* b 0xb0a9 (tail join) */
    /* (transfer, no return) */
}
