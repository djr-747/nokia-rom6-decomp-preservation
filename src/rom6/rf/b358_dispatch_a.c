/* ROM6 0xB358 DISPATCH_A -- 70w (span B358-B39D, single entry).
 * Verified encoding: src/rom6/rf/b358_dispatch_a.asm (recombine MATCH).
 * ORIGIN 0xB358
 * EXPECT: F074 05A8 F074 A3D5 FC45 7712 3490 1082 F030 FF8F 8082 7710 0004 7712 2514 7713 3A7E 771A 0003 F072 B371 1092 EC02 80B3 6DEB FFF5 6DEB FFFE 7712 2F00 7082 250D 771A 0002 F072 B382 1083 1C82 80B3 6B82 0001 6882 0007 F7BB 74F8 0008 0002 F030 F7FF F495 75F8 0008 0002 F495 F020 0800 F495 75F8 0008 0001 EC16 F495 F6BB 7712 0914 F274 39A4 7713 3A7E FC00
 *
 * Intent: RF dispatch worker with mask/XOR lanes and a delayed
 * call exit. Entry A/B unread (dark 0x5A8 call clobbers; A
 * recomputed, B untouched in-span); no ARs in-span (all set
 * locally); void. Runs dark SUB_05A8 (call, forward extern
 * void); A = routine_A3D5() (C-bound, A-out carried as int
 * return); A == 0 returns (rc aeq). Else AR2 = 13456 (stm);
 * A = *AR2 signed (ld, 71a3/28a5 precedent); A &= -113 (and,
 * 2baa shape); *AR2 = A-low (stl); AR0 = 4, AR2 = 9492,
 * AR3 = 14974, BRC = 3 (stm immediates). First rptb block
 * [B36D,B371], 4 passes (RPTB non-delayed RSA = word after the
 * 2-word op, inclusive REA per repeat_block; REA lands on the
 * first mar's operand so the mar completes in-block): A =
 * *AR2++ signed; stl a to *AR3+0 three times (rpt #2 repeats
 * the single word, 2a5f precedent, no AR3 step); AR3 -= 11
 * (mar offset 0xFFF5). Second mar AR3 -= 2 runs once after the
 * loop. AR2 = 12032 (stm); MEM[12032] = *(0x250D) (mvdk).
 * BRC = 2; second rptb block [B37C,B382], 3 passes (REA on the
 * andm operand, same inclusive rule): A = *AR3 signed (no
 * step); A ^= *AR2 signed (xor Smem, sign-extended); *AR3 =
 * A-low (stl, +0 step: the XOR accumulates into the same cell
 * while the counter below advances); MEM[AR2] += 1 (addm);
 * MEM[AR2] &= 7 (andm: 3-bit counter). Port 2 dance under
 * INTM (ssbx, hardware): A = port 2 (portr, AL-alias cell
 * write per the 2867 precedent); A &= -2049 (and); settle
 * nop; port 2 = A (portw); settle nop; A = 2048 (ld); settle
 * nop; port 1 = cell *(0x8) (portw reads the stale AL-alias
 * cell, 5362 shape, not A); 23 settle cycles (rpt #22);
 * INTM restore (rsbx, hardware). AR2 = 2324 (stm); delayed
 * call to C-bound routine_pa60_57 (calld 0x39a4) with the
 * 2-word delay stm AR3 = 14974 running first (WORD-count
 * clean), passing AR2/AR3; return (the reseated ARs die with
 * the span). A/B dead after (void); outs via cells, ports.
 */
extern void sub_05A8(void);                              /* dark, no symbol */
extern int routine_A3D5(void);                           /* C-bound, A-out as return */
extern void routine_pa60_57(int *ar2_in, int *ar3_in);   /* C-bound */
extern int port_read_2(void);
extern void port_write_2(int v);
extern void port_write_1(int v);

void sub_B358(void)
{
    long a;
    int *ar0;
    int *ar2;
    int *ar3;
    int i;
    int j;
    sub_05A8();                                          /* call 0x5a8 (dark) */
    if (routine_A3D5() == 0)                             /* call 0xa3d5; rc aeq */
        return;
    ar2 = (int *)13456;                                 /* stm #13456,ar2 */
    a = (long)*ar2;                                     /* ld *ar2,a */
    a &= -113L;                                          /* and #-113,a */
    *ar2 = (int)(a & 0xFFFFL);                           /* stl a,*ar2 */
    ar0 = (int *)4;                                      /* stm #4,ar0 (dead, kept) */
    (void)ar0;
    ar2 = (int *)9492;                                   /* stm #9492,ar2 */
    ar3 = (int *)14974;                                  /* stm #14974,ar3 */
    for (i = 0; i <= 3; i++) {                           /* rptb 0xb371, BRC = 3 */
        a = (long)*ar2++;                                /* ld *ar2+,a */
        for (j = 0; j < 3; j++)                          /* rpt #2; stl (x3, no step) */
            *ar3 = (int)(a & 0xFFFFL);                    /* stl a,*ar3+0 */
        ar3 -= 11;                                       /* mar *+ar3(0xfff5) */
    }
    ar3 -= 2;                                            /* mar *+ar3(0xfffe) (post-loop) */
    ar2 = (int *)12032;                                  /* stm #12032,ar2 */
    *ar2 = *(volatile int *)0x250D;                       /* mvdk 0x250d,*ar2 */
    for (i = 0; i <= 2; i++) {                           /* rptb 0xb382, BRC = 2 */
        a = (long)*ar3;                                  /* ld *ar3,a (no step) */
        a ^= (long)*ar2;                                 /* xor *ar2,a (sign-extended) */
        *ar3 = (int)(a & 0xFFFFL);                        /* stl a,*ar3+0 */
        *ar2 += 1;                                       /* addm #1,*ar2 */
        *ar2 &= 7;                                       /* andm #7,*ar2 */
    }
    /* ssbx st1,intm (hardware, no C form) */
    a = (long)port_read_2();                             /* portr pa2,*(0x8) */
    *(volatile int *)0x8 = (int)a;                       /* AL alias write (2867 precedent) */
    a &= -2049L;                                         /* and #-2049,a */
    /* nop (settle) */
    port_write_2((int)a);                                /* portw *(0x8),pa2 */
    /* nop (settle) */
    a = 2048;                                            /* ld #2048,a */
    /* nop (settle) */
    port_write_1(*(volatile int *)0x8);                   /* portw *(0x8),pa1 (stale cell) */
    for (i = 0; i < 23; i++) {}                          /* rpt #22; nop */
    /* rsbx st1,intm (hardware, no C form) */
    ar2 = (int *)2324;                                   /* stm #2324,ar2 */
    ar3 = (int *)14974;                                  /* calld delay: stm #14974,ar3 */
    routine_pa60_57(ar2, ar3);                           /* calld 0x39a4 */
    /* ret */
}
