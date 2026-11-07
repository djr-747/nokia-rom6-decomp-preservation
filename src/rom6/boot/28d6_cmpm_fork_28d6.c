/* ROM6 0x28D6 CMPM_FORK_28D6 -- 65w.
 * Verified encoding: src/rom6/boot/28d6_cmpm_fork_28d6.asm (recombine MATCH).
 * ORIGIN 0x28D6
 * EXPECT: 60F8 34BF 0001 F830 2910 60F8 34BF 0004 F830 2910 60F8 34BF 0003 F820 2909 60F8 366F 0000 E800 F495 FF30 F040 0001 60F8 37B0 0000 F495 F495 FF30 F040 0002 F845 291C F010 0002 F843 2902 F846 291E 69F8 3490 0200 F073 291C 7712 0492 69F8 3490 0100 F073 291C 60F8 366F 0000 F830 291E F073 291C 60F8 37B0 0000 F830 291E F073 291C
 *
 * Intent: Triple-compare fork with xc-or lanes into the 291C join. TC = (cell 0x34BF == K) per cmpm (28CF
 * precedent); 1 or 4 joins the 2910 lane; 3 falls through, else joins the 2909 lane. Lane: TC = (cell 0x366F
 * == 0); A = 0; TC taken ORs 1 (xc 2,tc skips or+pad when clear); TC = (cell 0x37B0 == 0); TC taken ORs 2;
 * A == 0 tail-joins frag_291C (bc aeq; 2917 interior, forward extern); A -= 2; A < 0 joins the 2902 lane
 * (bc alt); A > 0 tail-joins frag_291E (bc agt; 2917 interior, forward extern); A == 0 sets cell 0x3490
 * bit 9 (orm) and tail-joins frag_291C. 2902 lane: AR2 = 1170, cell 0x3490 bit 8, tail-join. 2909/2910 lanes:
 * re-compare and join frag_291E when equal, else tail-join frag_291C. Mappings by convention (unverified).
 */
extern void frag_291C(void); /* joins 2917_sub_2917 interior @+0x5; see docs/evidence/extern-triage.md */
extern void frag_291E(void); /* joins 2917_sub_2917 interior @+0x7; see docs/evidence/extern-triage.md */

void frag_28D6(void)
{
    long a;
    int *ar2;


    if (*(volatile int *)0x34BF == 1)                       /* cmpm; bc 0x2910,tc */
        goto l2910;
    if (*(volatile int *)0x34BF == 4)                       /* cmpm; bc 0x2910,tc */
        goto l2910;
    if (*(volatile int *)0x34BF != 3)                       /* cmpm; bc 0x2909,ntc */
        goto l2909;
    a = 0;                                                 /* ld #0,a */
    /* nop (settle) */
    if (*(volatile int *)0x366F == 0)                       /* cmpm; xc 2,tc */
        a |= 1;                                            /* or #1,a */
    /* nop; nop (settles) */
    if (*(volatile int *)0x37B0 == 0)                       /* cmpm; xc 2,tc */
        a |= 2;                                            /* or #2,a */
    if (a == 0) {                                          /* bc 0x291c,aeq */
        frag_291C();                                       /* (2917 interior) */
        return;
    }
    a -= 2;                                                /* sub #2,a */
    if (a < 0)                                             /* bc 0x2902,alt */
        goto l2902;
    /* bc 0x291e,agt falls through only when A == 0 */
    if (a > 0) {
        frag_291E();                                       /* (2917 interior) */
        return;
    }
    *(volatile int *)0x3490 |= 512;                        /* orm #512 */
    frag_291C();                                           /* b 0x291c (tail) */
    return;
l2902:
    ar2 = (int *)1170;                                     /* stm #1170,ar2 */
    *(volatile int *)0x3490 |= 256;                        /* orm #256 */
    frag_291C();                                           /* b 0x291c (tail) */
    return;
l2909:
    if (*(volatile int *)0x366F == 0) {                     /* cmpm; bc 0x291e,tc */
        frag_291E();
        return;
    }
    frag_291C();                                           /* b 0x291c (tail) */
    return;
l2910:
    if (*(volatile int *)0x37B0 == 0) {                     /* cmpm; bc 0x291e,tc */
        frag_291E();
        return;
    }
    frag_291C();                                           /* b 0x291c (tail) */
    /* return via join */
    (void)ar2;
}
