/* ROM6 0xE4DD PSHM_POPM_GATE -- 46w lattice post-filter gate.
 * Verified encoding: src/rom6/kernel/e4dd_pshm_popm_gate.asm (recombine MATCH).
 * ORIGIN 0xE4DD
 * EXPECT: 4A13 4A12 F274 E46B 7713 1100 8A12 F274 E46B F495 6D92 8A13 F020 1000 8093 8063 7714 1100 7715 110C E732 771A 0003 ED13 F272 E500 6DEB 0009 5695 5885 5194 5384 0363 8592 F521 858B 5695 5885 5194 5384 0363 8592 F521 FE00 858B ED00
 *
 * Intent: AR2/AR3-save gate (pshm/popm balanced, caller-live)
 * around two calls of pooled SUB39_E46B (no C entry; callee
 * AR effects dark, flagged). Post-call: A = 0x1000; *(AR3
 * entry) = 0x1000; cell 0x63 = 0x1000. AR4 = 4352, AR5 =
 * 4364, AR2 = AR3 entry + 1, ASM = -13. RPTBD block
 * E4F9-E500 x4 (BRC = 3): A = LONG32 @AR5 (MSW@AR5,
 * LSW above, AR5 += 2 per oracle indirect_single LONG32);
 * A = LONG32 @AR5 - A (drsub); B = A + LONG32 @AR4
 * (AR4 += 2); B += LONG32 @AR4; B += zeroext(cell 0x63)
 * (adds, OVM-sat flagged); *(AR2++) = low16(B >> 13)
 * (stl, ASM = -13); B -= A << 1 (sub a,1,b: dst -= src
 * << SHIFT per oracle SUB_ACC_SHIFT); *(AR3--) = low16
 * (B >> 13). Tail (once): same lane on the next pairs;
 * retd delays store *(AR3--) then ASM = 0. SXM/OVM/FRCT
 * and guard bits dark, flagged. Out: *(AR2++) x5,
 * *(AR3--) x5 streams, cell 0x63; AR2/AR3 restored.
 * EXPECT from the image.
 */
void pshm_popm_gate_E4DD(int *ar2_in, int *ar3_in)
{
    long a;
    long b;
    int *ar2 = ar2_in;   /* entry AR2 (pshm/popm balanced, caller-live) */
    int *ar3 = ar3_in;   /* entry AR3 (pshm/popm balanced, caller-live) */
    int *ar4;
    int *ar5;
    int i;

    /* pshm ar3; pshm ar2 (balanced by the popms; comment only) */
    ar3 = (int *)4352;                                         /* calld delay: stm #4352,ar3 */
    /* calld 0xe46b (SUB39_E46B, pooled, no C entry; AR effects dark) */
    ar2 = ar2_in;                                              /* popm ar2 (restore entry) */
    ar2++;                                                     /* calld delay: mar *ar2+ */
    /* calld 0xe46b (pooled; AR effects dark, flagged) */
    ar3 = ar3_in;                                              /* popm ar3 (restore entry) */
    a = 4096L;                                                 /* ld #4096,a */
    *ar3++ = 4096;                                             /* stl a,*ar3+ */
    *(volatile int *)0x63 = 4096;                              /* stl a,0x63 */
    ar4 = (int *)4352;                                         /* stm #4352,ar4 */
    ar5 = (int *)4364;                                         /* stm #4364,ar5 */
    ar2 = ar3;                                                 /* mvmm ar3,ar2 */
    /* stm #3,brc */
    /* ld #-13,asm (ASM = -13) */
    ar3 += 9;                                                  /* rptbd delay: mar *+ar3(0x9) */
    for (i = 0; i < 4; i++) {                                  /* rptbd 0xe500 (BRC = 3) */
        a = ((long)*ar5 << 16) | (unsigned)*(ar5 + 1);          /* dld *ar5+,a (SXM dark) */
        ar5 += 2;
        a = (((long)*ar5 << 16) | (unsigned)*(ar5 + 1)) - a;   /* drsub *ar5,a (C16 = 0) */
        b = a + (((long)*ar4 << 16) | (unsigned)*(ar4 + 1));   /* dadd *ar4+,a,b */
        ar4 += 2;
        b += ((long)*ar4 << 16) | (unsigned)*(ar4 + 1);        /* dadd *ar4,b */
        b += (long)(unsigned)*(volatile int *)0x63;            /* adds 0x63,b (OVM flagged) */
        *ar2++ = (int)((b >> 13) & 0xFFFFL);                   /* stl b,asm,*ar2+ */
        b -= a << 1;                                           /* sub a,1,b (oracle SUB_ACC_SHIFT) */
        *ar3-- = (int)((b >> 13) & 0xFFFFL);                   /* stl b,asm,*ar3- */
    }
    a = ((long)*ar5 << 16) | (unsigned)*(ar5 + 1);             /* dld *ar5+,a (tail) */
    ar5 += 2;
    a = (((long)*ar5 << 16) | (unsigned)*(ar5 + 1)) - a;       /* drsub *ar5,a */
    b = a + (((long)*ar4 << 16) | (unsigned)*(ar4 + 1));       /* dadd *ar4+,a,b */
    ar4 += 2;
    b += ((long)*ar4 << 16) | (unsigned)*(ar4 + 1);           /* dadd *ar4,b */
    b += (long)(unsigned)*(volatile int *)0x63;               /* adds 0x63,b */
    *ar2++ = (int)((b >> 13) & 0xFFFFL);                      /* stl b,asm,*ar2+ */
    b -= a << 1;                                              /* sub a,1,b */
    /* retd (delays run before the return) */
    *ar3-- = (int)((b >> 13) & 0xFFFFL);                      /* delay 1: stl b,asm,*ar3- */
    /* delay 2: ld #0,asm (ASM = 0) */
}
