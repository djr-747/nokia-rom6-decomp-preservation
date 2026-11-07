/* ROM6 0x39F0 PA60_57_WRITER_A -- 54w.
 * Verified encoding: src/rom6/kernel/39f0_pa60_57_writer_a.asm (recombine MATCH).
 * ORIGIN 0x39F0
 * EXPECT: F074 0630 60F8 250F 0022 F830 39F9 F074 3ADE 61F8 0007 0800 F7BB 74F8 0008 0000 F030 FF9F F495 75F8 0008 0000 EC14 F495 FD20 F6BB E803 F495 75F8 0008 003C E807 F495 75F8 0008 003C 771A 000D F072 3A1A 7492 0039 F495 7482 0039 E802 F495 75F8 0008 003C 1082 FE00 F474 8082
 *
 * Intent: RF port strobe with delayed-return tail. Runs
 * 0x630 (dark, extern); TC = (cell 0x250F == 34) (cmpm,
 * oracle: TC = equality); set skips the 3ADE poll (bc
 * 0x39f9,tc lands past the call), clear runs it (call,
 * C: pa56_poll_loop_3ADE, int out discarded -- A dead
 * before the portr reload, noted); TC = bit 11 of cell
 * 0x7 (bitf); INTM = 1 (ssbx, hardware state); A = port
 * 0 with AL-alias write (portr); A &= 0xFF9F (and #-97,
 * imm16 zero-extended so upper cleared); port 0 = A;
 * 21 settle cycles (rpt #20 nop); TC still the bit-11
 * result (no TC-writing op between, flagged) clear runs
 * INTM = 0 (xc 1,ntc covers the 1-word rsbx); A = 3,
 * port 60 = A; A = 7, port 60 = A. BRC = 13; 14 passes
 * (rptb 0x3a1a: port 57 = *(AR2++) then nop; REA 0x3a1a)
 * then port 57 = *(AR3++) once; A = 2, port 60 = A;
 * A = *(AR2) (ld, no step); retd with both delays always
 * running (sfta a,-12 arithmetic, then cell AR2 = A-low)
 * then returns. AR2/AR3 step on locals (plain +1);
 * ARs/A dead at return (flagged). Bound 39F0-3A25,
 * exit retd@3A23 with delays 3A24-3A25.
 */
extern void sub_0630(void);
extern int pa56_poll_loop_3ADE(void);
extern void port_write_60(int v);
extern void port_write_57(int v);
extern int port_read_0(void);
extern void port_write_0(int v);

void pa60_57_writer_a(int *ar2_in, int *ar3_in)
{
    int *ar2 = ar2_in;
    int *ar3 = ar3_in;
    long a;
    int i;
    sub_0630();                                      /* call 0x630 */
    if (*(volatile int *)0x250F != 34)               /* cmpm; bc tc */
        pa56_poll_loop_3ADE();                       /* call 0x3ade (out dead) */
    {                                                /* bitf *(0x7),#2048 */
        int tc = (*(volatile int *)0x7 & 2048) != 0;
        /* ssbx st1,intm (hardware state, always runs) */
        a = port_read_0();                           /* portr 0,*(0x8) */
        *(volatile int *)0x8 = (int)(a & 0xFFFF);    /* AL alias write */
        a &= 65439;                                  /* and #-97,a */
        /* nop */
        port_write_0((int)(a & 0xFFFF));             /* portw *(0x8),0 */
        /* rpt #20 nop: 21 settle cycles */
        /* nop */
        if (!tc) {                                   /* xc 1,ntc */
            /* rsbx st1,intm (hardware state) */
        }
    }
    a = 3;                                           /* ld #3,a */
    /* nop */
    port_write_60((int)(a & 0xFFFF));                /* portw *(0x8),60 */
    a = 7;                                           /* ld #7,a */
    /* nop */
    port_write_60((int)(a & 0xFFFF));                /* portw *(0x8),60 */
    /* stm #13,brc */
    for (i = 0; i < 14; i++) {                       /* rptb 0x3a1a */
        port_write_57(*ar2++);                       /* portw *ar2+,57 */
        /* nop */
    }
    port_write_57(*ar3++);                           /* portw *ar3+,57 */
    a = 2;                                           /* ld #2,a */
    /* nop */
    port_write_60((int)(a & 0xFFFF));                /* portw *(0x8),60 */
    a = (long)*ar2;                                  /* ld *ar2,a */
    a >>= 12;                                        /* retd delay-1 (arith) */
    *ar2 = (int)(a & 0xFFFF);                        /* retd delay-2 (runs) */
    /* retd */
}
