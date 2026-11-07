/* ROM6 0x978F SUB_978F -- 78w port 0/54 strobe with poll.
 * Verified encoding: src/rom6/kernel/978f_sub_978f.asm (recombine MATCH).
 * ORIGIN 0x978F
 * EXPECT: F7BB 7482 0000 6882 FFEF F495 7582 0000 EC12 F495 68F8 20FF FFFE F845 97A2 F074 9682 F073 97DC 7482 0036 6882 FFE1 6982 801C F495 7582 0036 F495 7482 0000 6982 0010 F495 7582 0000 EC02 F495 F074 9682 7712 0060 7482 0036 6182 4000 F820 97B9 6882 7FFF F495 7582 0036 F495 7482 0000 6882 FFEF F495 7582 0000 EC12 F495 10F8 20FF F030 001E 74F8 000B 0036 F330 FFE1 F1A0 F495 75F8 000B 0036 FC00
 *
 * Intent: Disables interrupts (ssbx intm, no C form, noted). Cell *AR2 =
 * port 0 (portr, extern op); clear bit 4 (andm #-17, 0xFFEF); kick to port
 * 0 (portw, extern op); 18-nop settle. Mask cell 0x20FF &= -2 (andm). Entry
 * A == 0 runs the 0x97A2 arm (bc aeq; A entry-live, never set before the
 * test); else runs opaque ROUTINE_9682 (call; has .asm with retd, forward
 * extern void + return-note) and returns (b 0x97DC). The 0x97A2 arm: cell
 * *AR2 = port 54; clear low 5 bits (andm #-31, 0xFFE1); set bit 15 (orm
 * -32740 = 0x801C); kick to port 54; cell *AR2 = port 0; set bit 4 (orm
 * 16); kick to port 0; 2-nop settle. Runs ROUTINE_9682 again, AR2 = 96
 * (stm, absolute re-point, local only), then polls port 54 into *AR2 until
 * bit 14 sets (do/while on the bitf #16384 TC; hardware hang risk noted).
 * Clear bit 15 (andm #32767); kick to port 54; cell *AR2 = port 0; clear
 * bit 4; kick to port 0; 18-nop settle. A = cell 0x20FF & 30 (ld, and);
 * cell(DP 0x0B) = port 54 (portr, extern op); B-entry &= -31 (and, 40-bit);
 * B |= A (or); kick DP cell 0x0B to port 54 (portw, extern op); returns.
 * A/B entry-live (B 40-bit long); AR2 entry cursor, re-pointed locally.
 * Bound 978F-97DC (ret FC00@97DC).
 */
extern void routine_9682(void);
extern void portr_port0_par2(int *par2);
extern void portw_par2_port0(int *par2);
extern void portr_port54_par2(int *par2);
extern void portw_par2_port54(int *par2);
extern void portr_port54_cell0B(void);
extern void portw_cell0B_port54(void);

void frag_978F(int a_live, long b_live, int *par2)
{
    long b = b_live;

    /* ssbx st1,intm (interrupt gate, no C form) */
    portr_port0_par2(par2);                            /* portr 0,*ar2 */
    *par2 &= -17;                                      /* andm #-17 */
    /* nop */
    portw_par2_port0(par2);                            /* portw *ar2,0 */
    /* rpt #18 + nop: 18-cycle settle (timing only) */
    *(volatile int *)0x20FF &= -2;                     /* andm #-2 */
    if (a_live != 0) {                                 /* bc 0x97a2,aeq */
        routine_9682();                                /* call 0x9682 */
        return;                                        /* b 0x97dc */
    }
    /* 0x97a2 arm */
    portr_port54_par2(par2);                           /* portr 54,*ar2 */
    *par2 &= -31;                                      /* andm #-31 */
    *par2 |= -32740;                                   /* orm -32740 */
    /* nop */
    portw_par2_port54(par2);                           /* portw *ar2,54 */
    /* nop */
    portr_port0_par2(par2);                            /* portr 0,*ar2 */
    *par2 |= 16;                                       /* orm #16 */
    /* nop */
    portw_par2_port0(par2);                            /* portw *ar2,0 */
    /* rpt #2 + nop (timing only) */
    routine_9682();                                    /* call 0x9682 */
    par2 = (int *)96;                                  /* stm #96,ar2 */
    do {                                               /* 0x97b9 poll */
        portr_port54_par2(par2);                       /* portr 54,*ar2 */
    } while ((*par2 & 16384) == 0);                    /* bitf; bc ntc */
    *par2 &= 32767;                                    /* andm #32767 */
    /* nop */
    portw_par2_port54(par2);                           /* portw *ar2,54 */
    /* nop */
    portr_port0_par2(par2);                            /* portr 0,*ar2 */
    *par2 &= -17;                                      /* andm #-17 */
    /* nop */
    portw_par2_port0(par2);                            /* portw *ar2,0 */
    /* rpt #18 + nop (timing only) */
    {
        long a = (long)*(volatile int *)0x20FF;        /* ld *(0x20ff),a */
        a &= 30L;                                      /* and #30,a */
        portr_port54_cell0B();                         /* portr 54,*(0xb) */
        b &= -31L;                                     /* and #-31,b */
        b |= a;                                        /* or a,b */
        (void)b;                                       /* (B dead at ret) */
        /* nop */
        portw_cell0B_port54();                         /* portw *(0xb),54 */
    }
    /* ret */
}
