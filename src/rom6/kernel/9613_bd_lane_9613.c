/* ROM6 0x9613 BD_LANE_9613 -- 73w (live 9613-9628).
 * Verified encoding: src/rom6/kernel/9613_bd_lane_9613.asm (recombine MATCH).
 * ORIGIN 0x9613
 * EXPECT: 80D4 6BF8 20FD FFFE E805 11F8 20FD F310 0001 F84A 9625 6BF8 20FE 0001 E802 76F8 20FD 0000 F273 9667 7314 21FA 6FF8 0548 0D48 F330 FF00 81F8 0548 F558 F330 00FF 1BF8 0548 81F8 0548 11F8 20FE F310 01F0 FA4E 965C 6982 0080 6BF8 20FE 0001 61F8 20FF 0200 F820 964E F150 C100 F84C 964E 69F8 20FF 0020 61F8 20FF 4000 6AF8 20FF 4000 F830 965F F130 FF00 F273 9667 8184 E806
 *
 * Intent: Counter-gated delayed-branch lane. Cell AR4 = A-live low (stl a,*ar4+%; AR4/A caller-live,
 * AR0 step caller-live, +0% wrap needs BK, linear flagged); cell 0x20FD -= 2 (addm); A = 5 (ld);
 * B = cell - 1 (ld/sub); B >= 0 joins the 9625 lane (bc bgeq); else cell 0x20FE += 1 (addm), A = 2 (ld),
 * cell 0x20FD cleared (st). Lane: delayed branch into frag_9667 (bd; C-bound) with the mvmd AR4-save
 * delay running first (MEM[0x21FA] = AR4, cross-span delay abut per D581). Words 9629-965B sit past the
 * unconditional bd with no entries -- dead per 5886, preserved in asm, not modeled (ld-shift/and/stl lanes,
 * T-shift ld, or/sub, bcd + delays, orm/addm, bitf/xor/xorm lanes, and/bd + delays). A/AR4 caller-live,
 * dead after (flagged).
 */
extern void frag_9667(long a_live, int *ar2, long b_live);

void frag_9613(long a_live, int *par4, int ar0_live)
{
    long a;
    long b;
    int *ar4;
    int *ar2_unbound;  /* AR2 caller-live, never set in-span (flagged) */

    a = a_live;
    ar4 = par4;
    *ar4 = (int)(a & 0xFFFF);                              /* stl a,*ar4+% */
    ar4 += ar0_live;                                       /* +0% (wrap flagged) */
    *(volatile int *)0x20FD += -2;                         /* addm #-2 */
    a = 5;                                                 /* ld #5,a */
    b = (long)*(volatile int *)0x20FD;                     /* ld *(0x20fd),b */
    b = b - 1;                                             /* sub #1,b */
    if (b < 0) {                                           /* bc 0x9625,bgeq (fallthrough) */
        *(volatile int *)0x20FE += 1;                       /* addm #1 */
        a = 2;                                             /* ld #2,a */
        *(volatile int *)0x20FD = 0;                        /* st #0 */
    }
    *(volatile int *)0x21FA = (int)(long)ar4;              /* bd delay: mvmd (runs) */
    frag_9667(a, ar2_unbound, b);                          /* bd 0x9667 (tail) */
    /* dead 9629-965B (past unconditional bd, not modeled) */
}
