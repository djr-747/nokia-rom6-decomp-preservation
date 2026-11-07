/* ROM6 0x39A4 ROUTINE_PA60_57 -- 76w.
 * Verified encoding: src/rom6/kernel/39a4_routine_pa60_57.asm (recombine MATCH).
 * ORIGIN 0x39A4
 * EXPECT: F074 0630 E803 F495 75F8 0008 003C E805 F495 75F8 0008 003C 771A 0003 F072 39B7 F495 7593 0039 F495 4492 F47B 3C82 F47A 3CE2 0005 F47B F495 75F8 0008 0039 F495 F495 75F8 0009 0039 F020 FFFC F495 75F8 0008 003C E802 F495 75F8 0008 003C 61F8 0007 0800 F7BB 74F8 0008 0000 F040 0060 F495 75F8 0008 0000 EC15 F495 FD20 F6BB 74F8 0008 0038 F030 0010 F040 0009 F495 75F8 0008 0038 FC00
 *
 * Intent: RF port strobe with accumulate lane. Runs 0x630
 * (dark, extern); A = 3 then port 60 = A (portw *(0x8),60
 * reads the AL alias cell, modeled port_write_60(a) per
 * the 2867 precedent); A = 5, port 60 = A. BRC = 3;
 * 4 passes (rptb 0x39b7: nop, port 57 = *(AR3++) via
 * portw *ar3+,57 modeled port_write_57(*ar3++), nop;
 * REA 0x39b7) of A = *(AR2++) << 16 (ld Smem,16 per the
 * 3EF3 precedent a = 1L << 16, AR2 post-increments, no
 * AR0 involved) arith>>= 5 (sfta) plus *(AR2) << 16
 * (add Smem,16: same <<16 family, no AR step) arith>>= 6
 * (sfta) plus *(AR2+5) << 16 (no step) arith>>= 5
 * (sfta); the three <<16 terms fit long with the running
 * sum bounded near 2^27 (signed-shift overflow beyond
 * long is unmodelable in the dialect, flagged);
 * then port 57 = A, two nops, port 57 (ah alias cell)
 * = A. A = -4, port 60 = A; A = 2, port 60 = A. TC =
 * bit 11 of cell 0x7 (bitf single-bit); INTM = 1 (ssbx,
 * hardware state, no C form); A = port 0 with AL-alias
 * write (portr 0,*(0x8) per the 40a1 read-plus-alias
 * pattern); A |= 96; port 0 = A; 22 settle cycles
 * (rpt #21 nop per the 3EF3 precedent); TC still the
 * bit-11 result (no TC-writing op between, flagged)
 * clear skips the INTM = 0 (xc 1,ntc covers the 1-word
 * rsbx; the decision is structure, the state unmodeled);
 * A = port 56 with alias write; A &= 16; A |= 9;
 * port 56 = A; return. AR2/AR3 step on locals (plain
 * +1, no AR0); ARs/A dead at return (flagged). Bound
 * 39A4-39EF.
 */
extern void sub_0630(void);
extern void port_write_60(int v);
extern void port_write_57(int v);
extern int port_read_0(void);
extern void port_write_0(int v);
extern int port_read_56(void);
extern void port_write_56(int v);

void routine_pa60_57(int *ar2_in, int *ar3_in)
{
    int *ar2 = ar2_in;
    int *ar3 = ar3_in;
    long a;
    int i;
    sub_0630();                                      /* call 0x630 */
    a = 3;                                           /* ld #3,a */
    /* nop */
    port_write_60((int)(a & 0xFFFF));                /* portw *(0x8),60 */
    a = 5;                                           /* ld #5,a */
    /* nop */
    port_write_60((int)(a & 0xFFFF));                /* portw *(0x8),60 */
    /* stm #3,brc */
    for (i = 0; i < 4; i++) {                        /* rptb 0x39b7 */
        /* nop */
        port_write_57(*ar3++);                       /* portw *ar3+,57 */
        /* nop */
        a = (long)*ar2++ << 16;                      /* ld *ar2+,16,a */
        a >>= 5;                                     /* sfta a,-5 (arith) */
        a += (long)*ar2 << 16;                       /* add *ar2,16,a */
        a >>= 6;                                     /* sfta a,-6 (arith) */
        a += (long)*(ar2 + 5) << 16;                 /* add *ar2(0x5),16,a */
        a >>= 5;                                     /* sfta a,-5 (arith) */
    }
    /* nop */
    port_write_57((int)(a & 0xFFFF));                /* portw *(0x8),57 */
    /* nop; nop */
    port_write_57((int)(a & 0xFFFF));                /* portw *(0x9),57 */
    a = -4;                                          /* ld #-4,a */
    /* nop */
    port_write_60((int)(a & 0xFFFF));                /* portw *(0x8),60 */
    a = 2;                                           /* ld #2,a */
    /* nop */
    port_write_60((int)(a & 0xFFFF));                /* portw *(0x8),60 */
    {                                                    /* bitf *(0x7),#2048 */
        int tc = (*(volatile int *)0x7 & 2048) != 0;
        /* ssbx st1,intm (hardware state, always runs) */
        a = port_read_0();                           /* portr 0,*(0x8) */
        *(volatile int *)0x8 = (int)(a & 0xFFFF);    /* AL alias write */
        a |= 96;                                     /* or #96,a */
        /* nop */
        port_write_0((int)(a & 0xFFFF));             /* portw *(0x8),0 */
        /* rpt #21 nop: 22 settle cycles */
        /* nop */
        if (!tc) {                                   /* xc 1,ntc */
            /* rsbx st1,intm (hardware state) */
        }
    }
    a = port_read_56();                              /* portr 56,*(0x8) */
    *(volatile int *)0x8 = (int)(a & 0xFFFF);        /* AL alias write */
    a &= 16;                                         /* and #16,a */
    a |= 9;                                          /* or #9,a */
    /* nop */
    port_write_56((int)(a & 0xFFFF));                /* portw *(0x8),56 */
    /* ret */
}
