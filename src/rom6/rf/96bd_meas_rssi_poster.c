/* ROM6 0x96BD MEAS_RSSI_POSTER -- 67w.
 * Verified encoding: src/rom6/rf/96bd_meas_rssi_poster.asm (recombine MATCH).
 * ORIGIN 0x96BD
 * EXPECT: F074 05C6 7714 20FF 6184 0001 FA20 970B 7712 0060 7482 0002 6182 0100 FC20 6184 0002 F820 96EC 12F8 20FB 08F8 0587 F843 9700 10F8 20FD F845 96DC F073 9704 F7BB 7482 0036 6982 0001 F495 7582 0036 F495 7482 0002 6982 0200 F495 7582 0002 F7BB 7682 0100 F495 7582 0001 EC14 F495 6884 F7FF 7482 0002 6882 FEFF F495 7582 0002 F074 97DD F4EB
 *
 * Intent: COBBA RSSI measurement poster, interrupt context (rete).
 * Helper call, then status-gated port reads: if bit 0 of 0x20FF is
 * clear, chain to stage 0x970B (the two delay slots -- AR2 load and
 * port-2 read -- execute regardless). Port bit 8 clear, or status
 * bit 1 clear past the rc ntc conditional prefix, chains to 0x96EC
 * (exact skip semantics in the .asm; outcome-equivalent here).
 * Cell 0x20FB below cell 0x587 chains to 0x9700. Cell 0x20FD zero
 * takes the INTM-locked port-program path below; nonzero chains to
 * 0x9704. The port path ends calling 0x97DD and returns from
 * interrupt.
 */
extern void helper_05C6(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void stage_970B(void); /* joins 970b_frag_970b; see docs/evidence/extern-triage.md */
extern void stage_96EC(void); /* joins 96bd_meas_rssi_poster interior @+0x2F; see docs/evidence/extern-triage.md */
extern void stage_9700(void); /* joins 9700_frag_9700; see docs/evidence/extern-triage.md */
extern void stage_9704(void); /* joins 9700_frag_9700 interior @+0x4; see docs/evidence/extern-triage.md */
extern void sub_97DD(void); /* joins 97dd_wrap_97dd; see docs/evidence/extern-triage.md */

void meas_rssi_poster_96BD(void)        /* interrupt context (rete) */
{
    int st, portv, v;
    int *ar2;
    helper_05C6();                               /* call 0x5c6 */
    st = *(volatile int *)0x20FF;                /* stm #8447,ar4 */
    ar2 = (int *)96;                             /* delay slot 1 */
    portv = *ar2;                                /* delay slot 2: portr 2 */
    if (!(st & 1)) {                             /* bitf, bcd 970B ntc */
        stage_970B();
        return;
    }
    if (!(portv & 256)) {                        /* bitf, rc ntc gate */
        stage_96EC();
        return;
    }
    if (!(st & 2)) {                             /* bitf, bc 96EC ntc */
        stage_96EC();
        return;
    }
    if ((*(volatile int *)0x20FB -
         *(volatile int *)0x587) < 0) {          /* ldu, sub, bc alt */
        stage_9700();
        return;
    }
    v = *(volatile int *)0x20FD;                 /* ld */
    if (v != 0) {                                /* bc 96DC aeq falls */
        stage_9704();                            /* b 0x9704 */
        return;
    }
    /* 0x96DC: INTM-locked COBBA port program path, then rete. */
    *ar2 |= 1;                                   /* portr 54, orm #1 */
    *ar2 |= 512;                                 /* portr 2, orm #512 */
    *ar2 = 256;                                  /* st #256 (port 1 sel) */
    { int i; for (i = 0; i < 21; i++) {} }       /* rpt #20, nop */
    *(volatile int *)0x20FF &= ~2048;            /* andm #-2049: bit11 off */
    *ar2 &= ~256;                                /* andm #-257 */
    sub_97DD();                                  /* call 0x97dd */
    /* rete */
}
