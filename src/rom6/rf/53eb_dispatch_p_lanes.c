/* ROM6 0x53EB DISPATCH_P_LANES_53EB -- 53w.
 * Verified encoding: src/rom6/rf/53eb_dispatch_p_lanes.asm (recombine MATCH).
 * ORIGIN 0x53EB
 * EXPECT: F074 06E2 68F8 0537 FC97 68F8 051D FFFB 68F8 263A FDFF 70F8 057B 3F12 10F8 2477 7712 051C 6882 FF7F FF45 6982 0080 60F8 0573 AF57 F820 5409 F073 54BB F074 06E2 60F8 0573 A249 F820 5420 6882 FF7F F074 8641 F074 864E F074 B6E6 F074 C717 F074 9FA8 10F8 3FC7 F073 53CD
 *
 * Intent: P-lane pair with conditional slots (two entries, one file per 538D convention). Entry 0 (0x53EB): dark SUB_06E2, AND-masks, cell 0x57B = cell 0x3F12 (mvdk), A = cell 0x2477, AR2 = 0x51C, cell &= -129; A == 0 skips the orm-plus-cmpm slots (xc 2,aeq: slots set no flags except the cmpm's TC); the TC the trailing bc reads is the cmpm's when the slots run, else the entry TC threaded as tc_live (a_live-threading precedent; top arrival TC set by the dispatch branch). Mismatch joins entry 1 at 0x5409 (bc ntc; AR2 = 0x51C on this path); else tail-enters dark 0x54BB (b). Entry 1 (0x5409): dark SUB_06E2, cell 0x573 != -23991 runs C FRAG_5420 with entry AR2 (bc ntc, C-bound, AR2 param); else the 5420 filter chain on entry AR2 (dark SUB_8641/864E, builders, SUB_9FA8); A = cell 0x3FC7 tail-enters dark 0x53CD (b, A arg). Bound 53EB-541F, 53w; the 0x5434 span is a separate file.
 */
extern void sub_06E2(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_54BB(void);
extern void frag_5420(int *par2);
extern void sub_8641(void);
extern void sub_864E(void);
extern void param_builder_b6e6(void); /* joins b6e6_param_builder_b6e6; see docs/evidence/extern-triage.md */
extern void init_filter_c717(void); /* joins c717_init_filter_c717; see docs/evidence/extern-triage.md */
extern void sub_9FA8(void); /* joins 9fa8_sub_9fa8; see docs/evidence/extern-triage.md */
extern void frag_53CD(int a_live); /* joins 53ba_dispatch_p_lanes interior @+0x13; see docs/evidence/extern-triage.md */
extern void frag_5409(int *par2);

void frag_53EB(int tc_live)
{
    int a;
    int *ar2;
    int tc = tc_live;
    sub_06E2();                                    /* call 0x6e2 */
    *(volatile int *)0x537 &= -873;            /* andm */
    *(volatile int *)0x51D &= -5;             /* andm */
    *(volatile int *)0x263A &= -513;          /* andm */
    *(volatile int *)0x57B = *(volatile int *)0x3F12; /* mvdk */
    a = *(volatile int *)0x2477;               /* ld */
    ar2 = (int *)(long)0x51C;                      /* stm #1308,ar2 */
    *ar2 &= -129;                                  /* andm #-129,*ar2 */
    if (a != 0) {                                  /* xc 2,aeq */
        *ar2 |= 128;                               /* orm (slot 1) */
        tc = (*(volatile int *)0x573 == -20649); /* cmpm (slot 2) */
    }
    if (!tc) {                                     /* bc 0x5409,ntc */
        frag_5409(ar2);                            /* join entry 1 (AR2 = 0x51C) */
        return;
    }
    frag_54BB();                                   /* b 0x54bb tail */
}

void frag_5409(int *par2)
{
    int a;
    sub_06E2();                                    /* call 0x6e2 */
    if (*(volatile int *)0x573 != -23991) {    /* cmpm, bc ntc */
        frag_5420(par2);                           /* away, C-bound */
        return;
    }
    *par2 &= -129;                                 /* andm #-129,*ar2 */
    sub_8641();                                    /* call 0x8641 */
    sub_864E();                                    /* call 0x864e */
    param_builder_b6e6();                          /* call 0xb6e6 */
    init_filter_c717();                            /* call 0xc717 */
    sub_9FA8();                                    /* call 0x9fa8 */
    a = *(volatile int *)0x3FC7;               /* ld */
    frag_53CD(a);                                  /* b 0x53cd tail */
}
