/* ROM6 0x3475 DISPATCH_FAN_3475 -- 139w.
 * Verified encoding: src/rom6/kernel/3475_dispatch_fan_3475.asm (recombine MATCH).
 * ORIGIN 0x3475
 * EXPECT: 4813 7714 357B FF20 F073 348D FF46 7714 36BC F073 349B 4813 7714 25E6 FF20 F073 34B0 7714 358B FF46 7714 36CC F073 34B0 7714 25D6 F073 349B F074 34B4 7714 25E6 F073 349B F074 34B4 7714 25C1 10DA F130 00FF 8194 771A 000A F072 34A6 4482 1ADA 6F94 0C98 6FDA 0C58 F030 00FF 8094 F074 2E2F F073 2E64 F074 34B4 F073 349B F074 06EA 6FE2 0002 0C5A F030 0008 61F8 0866 0008 11F8 0866 F330 0007 F2A0 80F8 0866 FC30 60F8 04FA 0007 4A12 F820 3500 10F2 0003 F030 BFFE 60F8 0008 1908 F820 34FE 10F2 0001 F030 0600 60F8 0008 0200 F820 34FE 7713 2F00 7716 04EF 771A 0005 F072 34E9 1096 F050 A5A5 8093 7715 2F01 F074 350C F074 350C F074 350C 1082 F030 F0F0 9508 F330 0F00 F2A0 1C95 F030 FF00 F844 3500 8A12 FC00
 *
 * Intent: AR-select dispatch fan with shift-merge sample loop and a compare-guarded subroutine.
 * Entry frag_3475 (fall-through from 3460 + exterior): A = AR3-live (ldm); AR4 = 13691;
 * TC-live clear joins the 348D lane (xc 2,ntc; TC caller-live, unbound, flagged); else A > 0 selects
 * AR4 = 14012 (xc 2,agt); join 349B. Entry frag_3480 (prev-span 346D + exterior 0x6DCD/0x75C3): same
 * shape selecting AR4 = 9702/13707/14028, then the 34B0 lane (call frag_34B4, join 349B). Entries
 * frag_3491 (prev-span 3471 + exterior 0x3DED/0x3DEF/0x756C) and frag_3497 (prev-span 3473): call
 * frag_34B4 with caller-live AR4 (par4_in), set AR4 = 9702/9665, join 349B. 349B body (duplicated per
 * 44FD): A = *AR2 low byte, B = A & 255, *AR4++ = B; 11x rptb block merging *AR2<<16 | *AR2 (same word,
 * +0% step) storing (A>>8)-low (exact); A = *AR2>>8 arith + step, low byte stored; dispatcher call,
 * b-tail. Subroutine frag_34B4 (interior callers + exterior 0x6A96): dark SUB_06EA; A = *(AR2+2)>>6
 * arith; A &= 8; TC = cell 0x866 bit 3; B = cell & 7; A |= B; cell = A; TC taken returns (rc). TC =
 * (cell 0x4FA == 7, cmpm); clear hangs in routine_3500 idle (bc 3500,ntc). AR2-save (pshm, balanced);
 * masked-compare guards (cmpm/and, bc 34FE joins) select a 6x rptb xor-fold (A ^= 42405) into lane 12032;
 * AR5 = 12033; three frag_350C calls (callee steps AR2 += AR0, AR5 += 1 each -- applied between calls);
 * nibble-merge with checksum over *AR5 (xor/and); nonzero hangs in routine_3500 (bc 3500,aneq); popm, ret.
 * AR2/AR0 caller-live (+0% wrap needs BK, linear flagged); AR3/TC/AR4/AR7 caller-live, flagged.
 */
extern void sub_06EA(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void dispatcher_entry_2E2F(void);
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */
extern void routine_3500(void);
extern void frag_350C(int *ar2_in, int *ar5_in, int ar0_live);
void frag_34B4(int *par2, int *par4, int ar0_live);

void frag_3475(int ar3_live, int tc_live, int *par2, int ar0_live)
{
    long a;
    long b;
    int w;
    int *ar2;
    int *ar4;
    int i;

    a = (long)ar3_live;                                    /* ldm ar3,a */
    ar4 = (int *)13691;                                    /* stm #13691,ar4 */
    if (!tc_live)                                          /* xc 2,ntc (skips b) */
        goto l348d;
    if (a > 0)                                             /* xc 2,agt */
        ar4 = (int *)14012;                                /* stm #14012,ar4 */
    goto l349b;                                            /* b 0x349b */
l348d:
    ar4 = (int *)9686;                                     /* stm #9686,ar4 */
    /* b 0x349b */
l349b:
    /* ---- 349B body (shared tail, duplicated per 44FD) ---- */
    ar2 = par2;
    a = (long)*ar2;                                        /* ld *ar2+0%,a */
    ar2 += ar0_live;                                       /* +0% (wrap flagged) */
    b = a & 255L;                                          /* and #255,a,b */
    *ar4++ = (int)(b & 0xFFFF);                            /* stl b,*ar4+ */
    /* stm #10,brc; rptb 0x34a6 (11 iters) */
    for (i = 0; i < 11; i++) {
        w = *ar2;                                          /* ld *ar2,16,a (same word) */
        a = (long)w << 16;
        a |= (long)(unsigned)w;                            /* or *ar2+0%,a */
        ar2 += ar0_live;
        *ar4++ = (int)((a >> 8) & 0xFFFF);                 /* stl a,-8 (low-16 exact) */
    }
    a = (long)*ar2 >> 8;                                   /* ld *ar2+0%,-8,a (arith) */
    ar2 += ar0_live;
    a &= 255L;                                             /* and #255,a */
    *ar4++ = (int)a;                                       /* stl a,*ar4+ */
    dispatcher_entry_2E2F();                               /* call 0x2e2f */
    frag_2E64();                                           /* b 0x2e64 (tail) */
}

void frag_3480(int ar3_live, int tc_live, int *par2, int ar0_live)
{
    long a;
    long b;
    int w;
    int *ar2;
    int *ar4;
    int i;

    a = (long)ar3_live;                                    /* ldm ar3,a */
    ar4 = (int *)9702;                                     /* stm #9702,ar4 */
    if (!tc_live)                                          /* xc 2,ntc */
        goto l34b0;
    ar4 = (int *)13707;                                    /* stm #13707,ar4 */
    if (a > 0)                                             /* xc 2,agt */
        ar4 = (int *)14028;                                /* stm #14028,ar4 */
    /* b 0x34b0 */
l34b0:
    frag_34B4(par2, ar4, ar0_live);                        /* call 0x34b4 */
    /* b 0x349b */
    ar2 = par2;
    a = (long)*ar2;                                        /* (349B body) */
    ar2 += ar0_live;
    b = a & 255L;
    *ar4++ = (int)(b & 0xFFFF);
    for (i = 0; i < 11; i++) {
        w = *ar2;
        a = (long)w << 16;
        a |= (long)(unsigned)w;
        ar2 += ar0_live;
        *ar4++ = (int)((a >> 8) & 0xFFFF);
    }
    a = (long)*ar2 >> 8;
    ar2 += ar0_live;
    a &= 255L;
    *ar4++ = (int)a;
    dispatcher_entry_2E2F();
    frag_2E64();
}

void frag_3491(int *par2, int *par4_in, int ar0_live)
{
    long a;
    long b;
    int w;
    int *ar2;
    int *ar4;
    int i;

    frag_34B4(par2, par4_in, ar0_live);                    /* call 0x34b4 */
    ar4 = (int *)9702;                                     /* stm #9702,ar4 */
    /* b 0x349b */
    ar2 = par2;
    a = (long)*ar2;
    ar2 += ar0_live;
    b = a & 255L;
    *ar4++ = (int)(b & 0xFFFF);
    for (i = 0; i < 11; i++) {
        w = *ar2;
        a = (long)w << 16;
        a |= (long)(unsigned)w;
        ar2 += ar0_live;
        *ar4++ = (int)((a >> 8) & 0xFFFF);
    }
    a = (long)*ar2 >> 8;
    ar2 += ar0_live;
    a &= 255L;
    *ar4++ = (int)a;
    dispatcher_entry_2E2F();
    frag_2E64();
}

void frag_3497(int *par2, int *par4_in, int ar0_live)
{
    long a;
    long b;
    int w;
    int *ar2;
    int *ar4;
    int i;

    frag_34B4(par2, par4_in, ar0_live);                    /* call 0x34b4 */
    ar4 = (int *)9665;                                     /* stm #9665,ar4 */
    ar2 = par2;                                            /* (falls into 349B) */
    a = (long)*ar2;
    ar2 += ar0_live;
    b = a & 255L;
    *ar4++ = (int)(b & 0xFFFF);
    for (i = 0; i < 11; i++) {
        w = *ar2;
        a = (long)w << 16;
        a |= (long)(unsigned)w;
        ar2 += ar0_live;
        *ar4++ = (int)((a >> 8) & 0xFFFF);
    }
    a = (long)*ar2 >> 8;
    ar2 += ar0_live;
    a &= 255L;
    *ar4++ = (int)a;
    dispatcher_entry_2E2F();
    frag_2E64();
}

void frag_34B4(int *par2, int *par4, int ar0_live)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int *ar4;
    int *ar5;
    int *ar6;
    int taken;
    int i;

    ar2 = par2;
    ar4 = par4;
    sub_06EA();                                            /* call 0x6ea (dark) */
    a = (long)*(ar2 + 2) >> 6;                             /* ld *ar2(0x2),-6,a (arith) */
    a &= 8L;                                               /* and #8,a */
    taken = (*(volatile int *)0x866 & 8) != 0;             /* bitf *(0x866),#8 */
    b = (long)*(volatile int *)0x866 & 7L;                 /* ld; and #7,b */
    a |= b;                                                /* or b,a */
    *(volatile int *)0x866 = (int)(a & 0xFFFF);            /* stl a,*(0x866) */
    if (taken)                                             /* rc tc */
        return;
    /* pshm ar2 (balanced by popm; caller-live, comment only) */
    if (*(volatile int *)0x4FA != 7) {                     /* cmpm; bc 0x3500,ntc */
        routine_3500();                                    /* idle hang */
        return;
    }
    a = (long)*(ar2 + 3);                                  /* ld *+ar2(0x3)%,a */
    ar2 += ar0_live;                                       /* +0% (wrap flagged) */
    a &= 0xBFFEL;                                          /* and #-16386,a */
    if (*(volatile int *)0x8 != 6408)                      /* cmpm; bc 0x34fe,ntc */
        goto l34fe;
    a = (long)*(ar2 + 1);                                  /* ld *+ar2(0x1)%,a */
    ar2 += ar0_live;
    a &= 1536L;                                            /* and #1536,a */
    if (*(volatile int *)0x8 != 512)                       /* cmpm; bc 0x34fe,ntc */
        goto l34fe;
    ar3 = (int *)12032;                                    /* stm #12032,ar3 */
    ar6 = (int *)1263;                                     /* stm #1263,ar6 */
    /* stm #5,brc; rptb 0x34e9 (6 iters) */
    for (i = 0; i < 6; i++) {
        a = (long)*ar6++;                                   /* ld *ar6+,a */
        a ^= 42405L;                                        /* xor #42405,a */
        *ar3++ = (int)(a & 0xFFFF);                         /* stl a,*ar3+ */
    }
    ar5 = (int *)12033;                                    /* stm #12033,ar5 */
    frag_350C(ar2, ar5, ar0_live);                         /* call 0x350c */
    ar2 += ar0_live;                                       /* callee +0% step */
    ar5 += 1;                                              /* callee *ar5++ step */
    frag_350C(ar2, ar5, ar0_live);                         /* call 0x350c */
    ar2 += ar0_live;
    ar5 += 1;
    frag_350C(ar2, ar5, ar0_live);                         /* call 0x350c */
    ar2 += ar0_live;
    ar5 += 1;
    a = (long)*ar2;                                        /* ld *ar2,a */
    a &= 0xF0F0L;                                          /* and #-3856,a */
    b = (long)*ar2 << 8;                                   /* ld *ar2,8,b */
    b &= 3840L;                                            /* and #3840,b */
    a |= b;                                                /* or b,a */
    a ^= (long)*ar5++;                                     /* xor *ar5+,a */
    a &= 0xFF00L;                                          /* and #-256,a */
    if (a != 0) {                                          /* bc 0x3500,aneq */
        routine_3500();                                    /* checksum hang */
        return;
    }
l34fe:
    /* popm ar2 (restore entry state) */
}
