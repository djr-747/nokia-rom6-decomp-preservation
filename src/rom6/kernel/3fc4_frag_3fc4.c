/* ROM6 0x3FC4 FRAG_3FC4 -- 54w RF-program prologue with three 0x4007 calls.
 * Verified encoding: src/rom6/kernel/3fc4_frag_3fc4.asm (recombine MATCH).
 * ORIGIN 0x3FC4
 * EXPECT: 7682 0280 F495 7582 002B E90B F020 0280 F074 4007 E800 E90A F074 4007 F020 0800 E90D F074 4007 7713 3E8E F495 7583 0025 7713 3E8F F495 7583 0026 7682 01FE F495 7582 0011 EC10 F495 F020 0980 61F8 3EC8 0800 F830 3FBA 74F8 000B 000C 1BF8 3ECC F495 75F8 000B 000C F073 3FBA
 *
 * Intent: *AR2-entry = 640 (st); kicked to port 43 (portw *ar2,43, extern
 * op). Three SUB_4007 transactions (call, C: sub_4007(a_in,b_in), A-results
 * dead: overwritten before any read): (640,11), (0,10), (2048,13). Cells
 * 16014/16015 kicked to ports 37/38 (portw, extern ops; nop settles).
 * *AR2-entry = 510, kicked to port 17, 16-nop settle (rpt #16 timing only).
 * A = 2432; bit 11 of cell 0x3EC8 set tail-enters dark 0x3FBA (bc tc,
 * forward extern, void per 283D precedent; numerically backward into the
 * bounded 3EBE-3FC3 region). Else cell(DP 0x0B) = port 12 (portr, extern
 * op); B = cell | cell 0x3ECC (or); kicked back to port 12 (portw, extern
 * op); tail-enters 0x3FBA (b). AR2 the only entry-live register.
 * Bound 3FC4-3FF9 (exit F073@3FF8->3FBA + operand 3FF9).
 */
extern int sub_4007(int a_in, int b_in); /* joins 4007_port0_txn; see docs/evidence/extern-triage.md */
extern void portw_par2_port43(int *par2); /* HW port alias, emulator-provided */
extern void portw_cell16014_port37(void); /* HW port alias, emulator-provided */
extern void portw_cell16015_port38(void); /* HW port alias, emulator-provided */
extern void portw_par2_port17(int *par2); /* HW port alias, emulator-provided */
extern void portr_port12_cell0B(void); /* HW port alias, emulator-provided */
extern void portw_cell0B_port12(void); /* HW port alias, emulator-provided */
extern void frag_3FBA(void); /* joins 3ef3_port_config_3ef3 interior @+0xC7; see docs/evidence/extern-triage.md */

void frag_3FC4(int *par2)
{
    long b;

    *par2 = 640;                                   /* st #640,*ar2 */
    /* nop */
    portw_par2_port43(par2);                       /* portw *ar2,43 */
    (void)sub_4007(640, 11);                       /* call 0x4007 (dead) */
    (void)sub_4007(0, 10);                         /* call 0x4007 (dead) */
    (void)sub_4007(2048, 13);                      /* call 0x4007 (dead) */
    /* stm #16014,ar3; nop */
    portw_cell16014_port37();                      /* portw *ar3,37 */
    /* stm #16015,ar3; nop */
    portw_cell16015_port38();                      /* portw *ar3,38 */
    *par2 = 510;                                   /* st #510,*ar2 */
    /* nop */
    portw_par2_port17(par2);                       /* portw *ar2,17 */
    /* rpt #16 + nop: 16-cycle settle (timing only) */
    /* ld #2432,a (A dead at both tails, not modeled) */
    if (*(volatile int *)0x3EC8 & 2048) {          /* bitf; bc 0x3fba,tc */
        frag_3FBA();
        return;
    }
    portr_port12_cell0B();                         /* portr 12,*(0xb) */
    b = (long)*(volatile int *)0xB;                /* or *(0x3ecc),b */
    b |= (long)*(volatile int *)0x3ECC;            /* (B dead at tail) */
    (void)b;
    /* nop */
    portw_cell0B_port12();                         /* portw *(0xb),12 */
    frag_3FBA();                                   /* b 0x3fba tail */
}
