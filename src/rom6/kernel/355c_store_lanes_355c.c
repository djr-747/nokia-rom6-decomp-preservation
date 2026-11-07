/* ROM6 0x355C STORE_LANES_355C -- 68w.
 * Verified encoding: src/rom6/kernel/355c_store_lanes_355c.asm (recombine MATCH).
 * ORIGIN 0x355C
 * EXPECT: 69F8 054F 0004 E723 1082 F030 0008 7714 2512 7710 2540 7715 253F 7716 34CA F845 3575 7714 2549 7710 2577 7715 2576 7716 34CB 6182 0001 6FD2 0D58 F330 00FF F820 3583 F845 3582 69F8 054F 0200 8180 6183 0004 F820 35B7 F845 358C 69F8 054F 0010 1184 6183 0002 F330 FEFF FF30 F340 0100 8184 6F82 0D58 F330 00FF 8185 11D2 F330 00FF 8186 F073 35B7
 *
 * Intent: Preset-select store lanes with masked merge and sample stores. Cell 0x54F bit 2 set (orm);
 * AR3 = AR2-live (mvmm; AR2 caller-live, unbound, flagged); A = *AR2; A &= 8; AR4/AR0/AR5/AR6 =
 * 9490/9536/9535/13514 (stm presets); A == 0 joins the 3575 lane (bc aeq); else AR4/AR0/AR5/AR6 =
 * 9545/9591/9590/13515. TC = *AR2 bit 0 (bitf); B = *AR2 >> 8 arithmetic (ld shift, SXM flagged);
 * B &= 255; TC clear joins 3583 (bc ntc); A == 0 joins 3582 (bc aeq); else cell 0x54F bit 9 set (orm).
 * MEM[AR0] = B-low (stl b,*ar0; AR0 holds the preset as pointer). TC = *AR3 bit 2 (bitf); TC clear
 * tail-joins frag_35B7 (bc ntc; 35A0 interior, forward extern); A == 0 joins 358C (bc aeq); else cell 0x54F
 * bit 4 set (orm). B = *AR4; TC = *AR3 bit 1 (bitf); B &= -257 (andm); TC taken ORs 256 (xc 2,tc);
 * cell AR4 = B-low (stl). B = *AR2 >> 8 (ld shift, no step); B &= 255; MEM[AR5] = B-low (stl).
 * B = *AR2, AR2 += AR0-live (ld +0%, wrap flagged); B &= 255; MEM[AR6] = B-low (stl); tail-join
 * frag_35B7 (b; 35A0 interior). AR2/AR0 caller-live, dead after (flagged).
 */
extern void frag_35B7(void); /* joins 35a0_frag_35a0 interior @+0x17; see docs/evidence/extern-triage.md */

void frag_355C(int *par2, int ar0_live)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int *ar4;
    int *ar0loc;
    int *ar5loc;
    int *ar6loc;
    int taken;


    ar2 = par2;
    *(volatile int *)0x54F |= 4;                           /* orm #4,*(0x54f) */
    ar3 = ar2;                                             /* mvmm ar2,ar3 */
    a = (long)*ar2;                                        /* ld *ar2,a */
    a &= 8L;                                               /* and #8,a */
    ar4 = (int *)9490;                                     /* stm presets */
    ar0loc = (int *)9536;
    ar5loc = (int *)9535;
    ar6loc = (int *)13514;
    if (a == 0)                                            /* bc 0x3575,aeq */
        goto l3575;
    ar4 = (int *)9545;                                     /* stm presets */
    ar0loc = (int *)9591;
    ar5loc = (int *)9590;
    ar6loc = (int *)13515;
l3575:
    taken = (*ar2 & 1) != 0;                               /* bitf *ar2,#1 */
    b = (long)*ar2 >> 8;                                   /* ld *ar2+%,-8,b */
    ar2 += ar0_live;                                       /* +0% (wrap flagged) */
    b &= 255L;                                             /* and #255,b */
    if (!taken)                                            /* bc 0x3583,ntc */
        goto l3583;
    if (a == 0)                                            /* bc 0x3582,aeq */
        goto l3582;
    *(volatile int *)0x54F |= 512;                         /* orm #512,*(0x54f) */
l3582:
    *ar0loc = (int)(b & 0xFFFF);                           /* stl b,*ar0 */
l3583:
    taken = (*ar3 & 4) != 0;                               /* bitf *ar3,#4 */
    if (!taken) {                                          /* bc 0x35b7,ntc */
        frag_35B7();                                       /* (35A0 interior) */
        return;
    }
    if (a == 0)                                            /* bc 0x358c,aeq */
        goto l358c;
    *(volatile int *)0x54F |= 16;                          /* orm #16,*(0x54f) */
l358c:
    b = (long)*ar4;                                        /* ld *ar4,b */
    taken = (*ar3 & 2) != 0;                               /* bitf *ar3,#2 */
    b &= -257L;                                            /* and #-257,b (always) */
    if (taken)                                             /* xc 2,tc */
        b |= 256L;                                         /* or #256,b */
    *ar4 = (int)(b & 0xFFFF);                              /* stl b,*ar4 */
    b = (long)*ar2 >> 8;                                   /* ld *ar2,-8,b (no step) */
    b &= 255L;                                             /* and #255,b */
    *ar5loc = (int)(b & 0xFFFF);                           /* stl b,*ar5 */
    b = (long)*ar2;                                        /* ld *ar2+%,b */
    ar2 += ar0_live;
    b &= 255L;                                             /* and #255,b */
    *ar6loc = (int)(b & 0xFFFF);                           /* stl b,*ar6 */
    frag_35B7();                                           /* b 0x35b7 (tail) */
}
