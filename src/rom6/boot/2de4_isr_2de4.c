/* ROM6 0x2DE4 ISR_2DE4 -- 75w.
 * Verified encoding: src/rom6/boot/2de4_isr_2de4.asm (recombine MATCH).
 * ORIGIN 0x2DE4
 * EXPECT: F074 0628 12F8 0872 F845 2DF2 F074 2289 69F8 0029 0008 68F8 0029 FFF7 12F8 0870 F845 2E02 8811 F074 B4F8 69F8 0029 0008 68F8 0029 FFF7 76F8 0870 0000 61F8 054D 0008 12F8 086E F845 2E2E F820 2E21 7713 2F00 7693 0400 F130 00FF F340 0100 8193 F030 FF00 8083 E905 7712 2F00 E814 7710 00F4 F074 93CE 12F8 086E F578 8911 F030 00FF 69F8 0029 0008 68F8 0029 FFF7 76F8 086E 0000 FC00
 *
 * Intent: HPI word-drain plus classify-post worker. Runs dark SUB_0628 (call, forward extern); A = *(0x872) unsigned (ldu zero-extends, A non-negative), zero skips to the in-span join at 0x2DF2 (bc aeq, rejoins). Runs dark SUB_2289; strokes cell 0x29 bit 3 set then clear (orm/andm pair, net nop, both verified). A = *(0x870) unsigned, zero skips to the in-span TC test at 0x2E02 (bc aeq, rejoins). AR1 = A (stlm, local; live into dark SUB_B4F8, noted); runs SUB_B4F8; strokes again; clears *(0x870). TC = bit 3 of cell 0x54D (bitf); A = *(0x86E) unsigned; A == 0 returns (bc aeq to the in-span ret at 0x2E2E); TC clear skips the block build to the in-span reload at 0x2E21 (bc ntc, rejoins). Block build mirrors SUB_2D5E at 0x2F00 with header 1024: low byte of A OR 256, high byte of A, A = 20, B = 5, AR0 = 244 preset, calls MSG_CLASSIFY_BY_CALLER 0x93CE (forward extern void: entry regs overwritten inside per its head, 0x2F00 block shared via volatile cells, caller-stack read unmodelable). Reloads A = *(0x86E); B = A sfta -8 (arithmetic; exact: A non-negative from ldu); AR1 = B; A &= 255; strokes again; clears *(0x86E); returns. Bound 2DE4-2E2E.
 */
extern void sub_0628(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_2289(void); /* unowned @0x2289; see docs/evidence/extern-triage.md */
extern void sub_B4F8(void); /* joins b4f8_cobba_worker; see docs/evidence/extern-triage.md */
extern void frag_93CE(void); /* joins 93ce_msg_classify_by_caller; see docs/evidence/extern-triage.md */

void isr_2DE4(void)
{
    int a, b;
    int *ar1;
    int *ar2, *ar3;
    sub_0628();                                    /* call 0x628 */
    a = (unsigned)*(volatile int *)0x872;      /* ldu */
    if (a == 0) {
        goto l2df2;                                /* bc 0x2df2,aeq */
    }
    sub_2289();                                    /* call 0x2289 */
    *(volatile int *)0x29 |= 8;                /* orm #8 */
    *(volatile int *)0x29 &= -9;               /* andm #-9 */
l2df2:
    a = (unsigned)*(volatile int *)0x870;      /* ldu */
    if (a == 0) {
        goto l2e02;                                /* bc 0x2e02,aeq */
    }
    ar1 = (int *)(long)(a & 0xFFFF);               /* stlm a,ar1 */
    (void)ar1;                                     /* live into sub_B4F8 */
    sub_B4F8();                                    /* call 0xb4f8 */
    *(volatile int *)0x29 |= 8;
    *(volatile int *)0x29 &= -9;
    *(volatile int *)0x870 = 0;                /* st #0 */
l2e02:
    {
        int tc = (*(volatile int *)0x54D & 8) != 0; /* bitf */
        a = (unsigned)*(volatile int *)0x86E;  /* ldu */
        if (a == 0) {
            return;                                /* bc 0x2e2e,aeq (ret) */
        }
        if (!tc) {
            goto l2e21;                            /* bc 0x2e21,ntc */
        }
    }
    ar3 = (int *)(long)0x2F00;                     /* stm #12032,ar3 */
    *ar3++ = 1024;                                 /* st #1024,*ar3+ */
    b = a & 255;                                   /* and #255,a,b */
    b |= 256;                                      /* or #256,b */
    *ar3++ = b;                                    /* stl b,*ar3+ */
    a &= 0xFF00;                                   /* and #-256,a */
    *ar3 = a;                                      /* stl a,*ar3 */
    b = 5;                                         /* ld #5,b */
    ar2 = (int *)(long)0x2F00;                     /* stm #12032,ar2 */
    (void)ar2;
    a = 20;                                        /* ld #20,a */
    /* stm #244,ar0: loop preset for the classify call, noted */
    frag_93CE();                                   /* call 0x93ce */
l2e21:
    a = (unsigned)*(volatile int *)0x86E;      /* ldu reload */
    b = a >> 8;                                    /* sfta a,-8,b (exact: a >= 0) */
    ar1 = (int *)(long)(b & 0xFFFF);               /* stlm b,ar1 */
    (void)ar1;
    a &= 255;                                      /* and #255,a */
    *(volatile int *)0x29 |= 8;
    *(volatile int *)0x29 &= -9;
    *(volatile int *)0x86E = 0;                /* st #0 */
}
