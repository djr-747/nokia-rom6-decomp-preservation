/* ROM6 0x81F2 SUB46_81F2 -- 46w.
 * Verified encoding: src/rom6/kernel/81f2_sub46_81f2.asm (recombine MATCH).
 * ORIGIN 0x81F2
 * EXPECT: F074 066E 76F8 2578 0000 7712 257F F274 8220 7713 2AA6 7713 2580 7712 2AA6 1082 F030 FF07 9593 F330 00F8 F2A0 8092 448B 1A93 F45B 9508 F030 00FF F2A0 8092 448B 1A93 F453 1182 F030 000F F2A8 8092 771A 001B F072 821E 9408 8092 FC00
 *
 * Intent: Masked three-lane store helper. Runs dark 0x66E (forward extern,
 * no symbol); cell 0x2578 = 0; AR2 = 9599, then calld 0x8220 (delay
 * AR3 = 10918 runs first; frag_8220 extern per 4c41.c precedent); AR3 = 9600,
 * AR2 = 10918. Lane 1: A = *AR2 masked with -249 (and #-249,a; 2a8a
 * precedent), B = (*AR3++ << 3) masked with 248, A |= B, *AR2++ = A-low.
 * Lane 2: A = (*AR3-- << 16), A |= zero-extended *AR3++ (OR Smem unshifted
 * per ti-c54x op_or_smem; differs from 82a5.c's sign-extended OR lane,
 * flagged for later review -- encoding unaffected), A >>= 5 arithmetic
 * (a7b7 precedent); B = (*AR2 << 8), A &= 255, A |= B, *AR2++ = A-low.
 * Lane 3: A = (*AR3-- << 16), A |= zero-extended *AR3++, A >>= 13; B = *AR2,
 * A &= 15, A |= (B << 8), *AR2++ = A-low. BRC = 27; rptb 0x821E block
 * [0x821D,0x821E] (RSA = PC+2 per 3273 precedent, inclusive per
 * repeat_block.c): 28x { A = (*AR2 << 8); *AR2++ = A-low }. Return.
 * AR2/AR3 set in-span and advanced past the store lanes; no documented
 * post-return consumer (callers @817F/819A/81A3/81B5 sit in the 810A gap
 * region, unanalyzed), flagged. A/B dead at return, flagged.
 */
extern void sub_066E(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_8220(void); /* joins 8220_caller_seq_8220; see docs/evidence/extern-triage.md */

void sub_81F2(void)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int i;

    sub_066E();                                            /* call 0x66e */
    *(volatile int *)0x2578 = 0;                           /* st #0,*(0x2578) */
    ar2 = (int *)9599;                                     /* stm #9599,ar2 */
    ar3 = (int *)10918;                                    /* calld delay (runs first) */
    frag_8220();                                           /* calld 0x8220 */
    ar3 = (int *)9600;                                     /* stm #9600,ar3 */
    ar2 = (int *)10918;                                    /* stm #10918,ar2 */
    a = *ar2;                                              /* ld *ar2,a */
    a &= -249L;                                            /* and #-249,a */
    b = (long)*ar3++ << 3;                                 /* ld *ar3+,3,b */
    b &= 248L;                                             /* and #248,b */
    a |= b;                                                /* or b,a */
    *ar2++ = (int)a;                                       /* stl a,*ar2+ */
    a = (long)*ar3-- << 16;                                /* ld *ar3-,16,a */
    a |= (unsigned)*ar3++;                                 /* or *ar3+,a */
    a = a >> 5;                                            /* ld a,-5,a */
    b = (long)*ar2 << 8;                                   /* ld *ar2,8,b */
    a &= 255L;                                             /* and #255,a */
    a |= b;                                                /* or b,a */
    *ar2++ = (int)a;                                       /* stl a,*ar2+ */
    a = (long)*ar3-- << 16;                                /* ld *ar3-,16,a */
    a |= (unsigned)*ar3++;                                 /* or *ar3+,a */
    a = a >> 13;                                           /* ld a,-13,a */
    b = *ar2;                                              /* ld *ar2,b */
    a &= 15L;                                              /* and #15,a */
    a |= b << 8;                                           /* or b,8,a */
    *ar2++ = (int)a;                                       /* stl a,*ar2+ */
    for (i = 0; i < 28; i++) {                             /* rptb 0x821e */
        a = (long)*ar2 << 8;                               /* ld *ar2,8,a */
        *ar2++ = (int)a;                                   /* stl a,*ar2+ */
    }
    /* ret */
    (void)a; (void)b;
}
