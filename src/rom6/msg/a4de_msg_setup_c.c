/* ROM6 0xA4DE MSG_SETUP_C -- 55w setup chain, one EXPECT.
 * Verified encoding: src/rom6/msg/a4de_msg_setup_c.asm (recombine MATCH).
 * ORIGIN 0xA4DE
 * EXPECT: F074 0658 7713 262F 1183 7083 262C FE4D 7714 FFFF 10F8 2615 60F8 250F 0022 F820 A4F3 F010 0E42 F073 A4F5 F010 0D48 6083 0050 7713 0001 FF43 7714 0000 E800 F820 A506 10F8 2639 F030 0100 68F8 2639 FEFF F074 463B 80F8 262E 7713 2491 E800 8093 8093 F274 ABD2 7712 2618 E901 FC00
 *
 * Intent: Cell-shaping setup into the ABD2 worker. Runs HELPER_0658
 * (call 0x658, C: helper_0658 per a4d5). AR3 = 9775 (0x262F);
 * B = *(0x262F) (ld); *(0x262F) = *(0x262C) (mvkd dmad-source per
 * ground rule: *(dst) = *(src)). RCD-if-B-zero with always-run delays
 * (rcd beq per op_rcd/a4de: AR4 = -1, A = *(0x2615), then return iff
 * B == 0). TC = (id cell 0x250F == 34) (cmpm); mismatch joins the 3400
 * lane (bc ntc to A4F3), match subtracts 3650 then joins (b to A4F5):
 * A = *(0x2615) - (TC ? 3650 : 3400). TC = (*(0x262F, post-mvkd) == 80)
 * (cmpm *ar3,#80 indirect compare). AR3 = 1; A < 0 skips AR4 = 0 and
 * A = 0 (xc 2,alt; XC skips WORDS per op_xc). TC clear skips the mask
 * pair (bc ntc to A506): else A = *(0x2639), A &= 256,
 * *(0x2639) &= -257 (and/andm: immediate zero-extended). Runs
 * ROUTINE_463B (call 0x463b, 510w asm-only; A rides through per the
 * callee-preservation convention -- no local branch forces A-out,
 * flagged); *(0x262E) = A-low (stl). AR3 = 9361; zero *(0x2491),
 * *(0x2492) (stl pair with post-inc). Runs SUB_ABD2 via calld (C:
 * sub_ABD2 per a7eb; delays stm #9752,ar2 + ld #1,b always execute;
 * AR2/B dead at RET @0xA514, noted). AR4 (-1/0) dead live-out, noted.
 * 11 callers (A27B A28F AFCA B057 B084 B0C9 B138 B161 B188 B2D2 B34B
 * per header). Bound A4DE-A514.
 */
extern void helper_0658(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void routine_463B(void); /* joins 463b_routine_463b; see docs/evidence/extern-triage.md */
extern void sub_ABD2(void); /* joins abd2_routine_abd2; see docs/evidence/extern-triage.md */

void msg_setup_C(void)
{
    long a;
    long b;
    int tc;
    int *par3;

    helper_0658();                                         /* call 0x658 */
    par3 = (int *)9775;                          /* stm #9775,ar3 */
    b = (long)*par3;                             /* ld *ar3,b */
    *par3 = *(volatile int *)0x262C;             /* mvkd 0x262c,*ar3 */
    /* rcd beq delays (always execute) */
    /* AR4 = -1 (dead live-out, noted) */
    a = (long)*(volatile int *)0x2615;           /* ld *(0x2615),a */
    if (b == 0)                                  /* rcd beq */
        return;
    tc = (*(volatile int *)0x250F == 34);        /* cmpm */
    if (tc)                                      /* bc ntc (match lane) */
        a -= 3650;                               /* sub #3650,a */
    else
        a -= 3400;                    /* A4F3 lane: sub #3400,a */
    tc = (*par3 == 80);                          /* cmpm *ar3,#80 */
    par3 = (int *)1;                             /* stm #1,ar3 */
    if (a >= 0) {                                /* xc 2,alt */
        /* AR4 = 0 (dead live-out, noted) */
        a = 0;                                   /* ld #0,a */
    }
    if (tc) {                                    /* bc 0xa506,ntc */
        a = (long)*(volatile int *)0x2639;       /* ld */
        a &= 256;                                /* and #256,a */
        *(volatile int *)0x2639 &= -257;         /* andm */
    }
    routine_463B();                              /* call 0x463b */
    *(volatile int *)0x262E = (int)(a & 0xFFFF); /* stl a */
    par3 = (int *)9361;                          /* stm #9361,ar3 */
    *par3++ = 0;                                 /* stl a,*ar3+ (A = 0) */
    *par3++ = 0;                                 /* stl a,*ar3+ */
    /* calld 0xabd2 (delays stm #9752,ar2 + ld #1,b run first) */
    sub_ABD2();
    /* ret @0xa514 (AR2 = 9752, B = 1 dead, noted) */
}
