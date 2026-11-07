/* ROM6 0xB461 RF_MEAS_B461 -- 71w (span B461-B4A7, single entry).
 * Verified encoding: src/rom6/rf/b461_rf_meas_b461.asm (recombine MATCH).
 * ORIGIN 0xB461
 * EXPECT: F074 06B2 61F8 0007 0800 F7BB 68F8 051E DFFF F820 B46F 69F8 051E 2000 10F8 04C2 4A0B 4A0C 4A0D 4A08 4A09 4A0A 61F8 0577 0040 F820 B482 7722 C00C 7722 C0CC F073 B486 7722 C008 7722 C0C8 74F8 0008 0000 F040 000C F495 75F8 0008 0000 EC14 F495 E908 F074 4055 F040 0600 F074 4007 8A0A 8A09 8A08 8A0D 8A0C 8A0B F1A0 81F8 04C2 61F8 051E 2000 F830 B4A7 F6BB FC00
 *
 * Intent: RF measurement transaction under INTM. Entry A/B
 * unread (the dark 0x6B2 call clobbers both; no ARs in-span).
 * Runs dark SUB_06B2 (call, forward extern void; B-out
 * unbound, flagged); TC = (cell 0x7 & 2048) != 0 (bitf, 5d38
 * polarity); INTM set (ssbx, hardware); cell 0x51E &= -8193
 * (andm); TC clear skips the set bit (bc ntc). Else cell 0x51E
 * |= 8192 (orm); A = *(0x4C2) signed (ld); pshm bl/bh/bg/al/
 * ah/ag pushes the A/B halves as C locals (2ecd precedent:
 * whole-long saves with the LIFO push order noted; B holds
 * the dark 06B2-out, unbound); TC = (cell 0x577 & 64) != 0;
 * clear selects the SPC0 pair -16376/-16184, else -16372/
 * -16180 (bc ntc plus b join; SPC0 serial-port control address
 * ungrounded in the oracle, extern op per the port convention,
 * emulator fills). A = port 0 (portr, AL-alias cell write per
 * the 2867 precedent); A |= 12 (or); settle nop; port 0 = A
 * (portw); 21 settle cycles (rpt #20, 2a5f precedent); B = 8
 * (ld); runs C-bound PORT0_TXN_PHASE2 0x4055 (call, B residue);
 * A = dark-out | 1536 (or; 4055 A-out unbound, flagged); runs
 * C-bound PORT0_TXN 0x4007 (call; A-out unbound, flagged);
 * popm restores A/B to the pushed values in reverse order
 * (the dark-call clobbers do not survive: A = *(0x4C2) again,
 * B = dark 06B2-out); B |= A (or a,b); *(0x4C2) = B-low
 * (stl); TC = (cell 0x51E & 8192) != 0; set returns with INTM
 * still set (bc tc to ret). Else INTM restore (rsbx,
 * hardware); return. A/B dead after (void); outs via cells,
 * ports, SPC0.
 */
extern void sub_06B2(void);                              /* dark, no symbol */
extern void port0_txn_phase2_4055(void);                 /* C-bound, B residue */
extern void port0_txn_4007(void);                        /* C-bound, A-out unbound */
extern int port_read_0(void);                            /* port 0 (2-precedent family) */
extern void port_write_0(int v);
extern void spc0_write(int v);                           /* SPC0 addr ungrounded, flagged */

void sub_B461(void)
{
    long a;
    long b;                                              /* unbound: dark 06B2 B-out (flagged) */
    long a_saved;                                        /* pshm al/ah/ag image */
    long b_saved;                                        /* pshm bl/bh/bg image */
    long a_4055;                                         /* unbound: 4055 A-out (flagged) */
    int tc;
    int i;
    sub_06B2();                                          /* call 0x6b2 (dark) */
    tc = (*(volatile int *)0x7 & 2048) != 0;             /* bitf *(0x7),#2048 */
    /* ssbx st1,intm (hardware, no C form) */
    *(volatile int *)0x51E &= -8193;                     /* andm #-8193,*(0x51e) */
    if (!tc)                                             /* bc 0xb46f,ntc */
        goto lsave;
    *(volatile int *)0x51E |= 8192;                      /* orm #8192,*(0x51e) */
lsave:
    a = (long)*(volatile int *)0x4C2;                    /* ld *(0x4c2),a */
    a_saved = a;                                         /* pshm bl/bh/bg/al/ah/ag (LIFO) */
    b_saved = b;
    tc = (*(volatile int *)0x577 & 64) != 0;             /* bitf *(0x577),#64 */
    if (!tc) {                                           /* bc 0xb482,ntc */
        spc0_write(-16376);                              /* stm #-16376,spc0 */
        spc0_write(-16184);                              /* stm #-16184,spc0 */
    } else {
        spc0_write(-16372);                              /* stm #-16372,spc0 */
        spc0_write(-16180);                              /* stm #-16180,spc0 */
    }
    a = (long)port_read_0();                             /* portr pa0,*(0x8) */
    *(volatile int *)0x8 = (int)a;                       /* AL alias write (2867 precedent) */
    a |= 12L;                                            /* or #12,a */
    /* nop (settle) */
    port_write_0((int)a);                                /* portw *(0x8),pa0 */
    for (i = 0; i < 21; i++) {}                          /* rpt #20; nop */
    b = 8;                                               /* ld #8,b */
    port0_txn_phase2_4055();                             /* call 0x4055 */
    a = a_4055 | 1536L;                                  /* or #1536,a (4055-out unbound) */
    port0_txn_4007();                                    /* call 0x4007 (A-out unbound, dies) */
    a = a_saved;                                         /* popm ag/ah/al (LIFO restore) */
    b = b_saved;                                         /* popm bg/bh/bl */
    b |= a;                                              /* or a,b */
    *(volatile int *)0x4C2 = (int)(b & 0xFFFFL);          /* stl b,*(0x4c2) */
    tc = (*(volatile int *)0x51E & 8192) != 0;           /* bitf *(0x51e),#8192 */
    if (tc)                                              /* bc 0xb4a7,tc (INTM stays set) */
        return;
    /* rsbx st1,intm (hardware, no C form) */
    /* ret */
}
