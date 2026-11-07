/* ROM6 0x9760 SUB_9760 -- 47w port-strobe gate with poll tail.
 * Verified encoding: src/rom6/kernel/9760_sub_9760.asm (recombine MATCH).
 * ORIGIN 0x9760
 * EXPECT: F074 05C2 10F8 2200 FE44 7712 0060 74F8 0008 0036 F130 1000 FC4D F030 0800 F074 978F 7712 0060 7682 0400 F495 7582 0001 EC16 F495 7482 0002 6982 0300 6882 FBFF F495 7582 0002 F6BB 61F8 20FF 0002 FE20 7712 0095 F274 2D5E 7713 086D FC00
 *
 * Intent: Runs sub_05C2 (low-zone mini-kernel, unsourced;
 * TRACE-evidenced hot routine, flagged). A = cell
 * 0x2200; rcd delay sets AR2 = 96 always, then returns
 * if A != 0 (rcd aneq, oracle branch cond). Cell 0x8 =
 * port 54 (portr, 3 words: the 0036 is the port-address
 * extension word, 0x36 = 54; extern op). B = A & 4096
 * (and #4096,a,b: B = A & (lk<<0) per oracle
 * AND_IMMEDIATE_SHIFT, src A dst B shift 0); returns if
 * B == 0 (rc beq, oracle COND_BEQ = B zero). A &= 2048;
 * runs frag_978F with live A-low/B/AR2 (signature
 * intake, flagged). *(AR2) = 1024; port 1 = *(AR2)
 * (portw, extern op); 23-nop settle (rpt #22, timing
 * only). *(AR2) = port 2 (portr, extern op); *(AR2) |=
 * 768 (orm); *(AR2) &= -1025 (andm, clears bit 10);
 * port 2 = *(AR2) (portw, extern op). INTM clear
 * (rsbx, hardware, no C form). TC = bit 1 of cell
 * 0x20FF (bitf); rcd delay sets AR2 = 149 always,
 * then returns if TC clear (rcd ntc). Calld delay
 * sets AR3 = 2157 first, then runs sub_2D5E(AR2, AR3)
 * (C-bound passthrough); return.
 * EXPECT from the image.
 */
extern void sub_05C2(void); /* low-zone mini-kernel, unsourced, trace-evidenced, flagged */
extern void frag_978F(int a_live, long b_live, int *par2);
extern void sub_2D5E(int *par2, int *par3);
extern void portr_port54_cell08(void); /* HW port alias, emulator-provided */
extern void portw_par2_port1(int *par2); /* HW port alias, emulator-provided */
extern void portr_port2_par2(int *par2); /* HW port alias, emulator-provided */
extern void portw_par2_port2(int *par2); /* HW port alias, emulator-provided */

void sub_9760(void)
{
    long a;
    long b;
    int *ar2;
    int *ar3;

    sub_05C2();                                            /* call 0x5c2 */
    a = (long)*(volatile int *)0x2200;                     /* ld *(0x2200),a */
    /* rcd aneq (delay runs before the return decision) */
    ar2 = (int *)(long)96;                                 /* delay: stm #96,ar2 */
    if (a != 0L)                                           /* rcd aneq */
        return;
    portr_port54_cell08();                                 /* portr 54,*(0x8) */
    b = a & 4096L;                                         /* and #4096,a,b */
    if (b == 0L)                                           /* rc beq */
        return;
    a &= 2048L;                                            /* and #2048,a */
    frag_978F((int)(a & 0xFFFFL), b, ar2);                 /* call 0x978f */
    ar2 = (int *)(long)96;                                 /* stm #96,ar2 */
    *ar2 = 1024;                                           /* st #1024,*ar2 */
    /* nop */
    portw_par2_port1(ar2);                                 /* portw *ar2,1 */
    /* rpt #22 + nop: 23-cycle settle (timing only) */
    portr_port2_par2(ar2);                                 /* portr 2,*ar2 */
    *ar2 |= 768;                                           /* orm #768,*ar2 */
    *ar2 &= -1025;                                         /* andm #-1025,*ar2 */
    /* nop */
    portw_par2_port2(ar2);                                 /* portw *ar2,2 */
    /* rsbx st1,intm (hardware, no C form) */
    /* rcd ntc (delay runs before the return decision) */
    ar2 = (int *)(long)149;                                /* delay: stm #149,ar2 */
    if ((*(volatile int *)0x20FF & 2) == 0)                /* bitf *(0x20ff),#2; rcd ntc */
        return;
    /* calld 0x2d5e (delay stm #2157,ar3 runs first) */
    ar3 = (int *)(long)2157;
    sub_2D5E(ar2, ar3);
    /* ret */
}
