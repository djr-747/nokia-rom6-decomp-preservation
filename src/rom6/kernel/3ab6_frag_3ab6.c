/* ROM6 0x3AB6 FRAG_3AB6 -- 40w.
 * Verified encoding: src/rom6/kernel/3ab6_frag_3ab6.asm (recombine MATCH).
 * ORIGIN 0x3AB6
 * EXPECT: F074 0632 F074 3ADE F7BB 74F8 0008 0000 F030 FF9F F495 75F8 0008 0000 EC14 F495 F6BB E803 F495 75F8 0008 003C E807 F495 75F8 0008 003C 771A 0002 F072 3AD7 7492 0039 F495 E802 F495 75F8 0008 003C FC00
 *
 * Intent: RF port strobe with polled fill. Runs 0x632
 * (dark, extern) then the 3ADE poll (call, C:
 * pa56_poll_loop_3ADE, int out discarded -- A dead before
 * the portr reload, noted); INTM = 1 (ssbx, hardware
 * state; the 39F0 bitf/conditional-rsbx pair is absent
 * here -- rsbx below is unconditional); A = port 0 with
 * AL-alias write (portr); A &= 0xFF9F (and #-97);
 * port 0 = A; 21 settle cycles (rpt #20 nop); INTM = 0
 * (rsbx, notional); A = 3, port 60 = A; A = 7,
 * port 60 = A. BRC = 2; 3 passes (rptb 0x3ad7: cell AR2
 * = port 57 with AR2 post-incremented, then nop; REA
 * 0x3ad7); A = 2, port 60 = A; return. AR2 steps on a
 * local (plain +1); ARs/A dead at return (flagged).
 * Bound 3AB6-3ADD (40w).
 */
extern void sub_0632(void);
extern int pa56_poll_loop_3ADE(void);
extern void port_write_60(int v);
extern int port_read_0(void);
extern void port_write_0(int v);
extern int port_read_57(void);

void frag_3AB6(int *ar2_in)
{
    int *ar2 = ar2_in;
    long a;
    int i;
    sub_0632();                                      /* call 0x632 */
    pa56_poll_loop_3ADE();                           /* call 0x3ade (out dead) */
    /* ssbx st1,intm (hardware state) */
    a = port_read_0();                               /* portr 0,*(0x8) */
    *(volatile int *)0x8 = (int)(a & 0xFFFF);        /* AL alias write */
    a &= 65439;                                      /* and #-97,a */
    /* nop */
    port_write_0((int)(a & 0xFFFF));                 /* portw *(0x8),0 */
    /* rpt #20 nop: 21 settle cycles */
    /* nop */
    /* rsbx st1,intm (hardware state, unconditional) */
    a = 3;                                           /* ld #3,a */
    /* nop */
    port_write_60((int)(a & 0xFFFF));                /* portw *(0x8),60 */
    a = 7;                                           /* ld #7,a */
    /* nop */
    port_write_60((int)(a & 0xFFFF));                /* portw *(0x8),60 */
    /* stm #2,brc */
    for (i = 0; i < 3; i++) {                        /* rptb 0x3ad7 */
        *ar2++ = port_read_57();                     /* portr 57,*ar2+ */
        /* nop */
    }
    a = 2;                                           /* ld #2,a */
    /* nop */
    port_write_60((int)(a & 0xFFFF));                /* portw *(0x8),60 */
    /* ret */
}
