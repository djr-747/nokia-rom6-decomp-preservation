/* ROM6 0x4057 PORT0_PHASE_4057 -- 74w.
 * Verified encoding: src/rom6/kernel/4057_port0_phase_4057.asm (recombine MATCH).
 * ORIGIN 0x4057
 * EXPECT: 4A0B 4A0C 4A0D 61F8 0007 0800 F7BB 74F8 0008 0000 F040 000C F495 75F8 0008 0000 EC16 F495 10F8 3EB5 F030 0002 F844 4073 F074 40A1 F073 4095 4A0B 4A0C 4A0D E90D F074 40A1 F030 0003 F844 4076 8A0D 8A0C 8A0B F495 4A0B 4A0C 4A0D F074 40A1 E90D F074 40A1 F030 000C F495 F010 000C F844 4086 8A0D 8A0C 8A0B F074 40A1 F130 0800 F84D 409B F040 F000 8A0D 8A0C 8A0B FC30 F6BB FC00
 *
 * Intent: Port-0 transaction phase with three 40A1 poll lanes and B-select tail. B-save (pshm bl/bh/bg,
 * balanced); TC = cell 0x7 bit 11 (bitf); INTM guard (ssbx, hardware); A = port 0 (portr); A |= 12 (or);
 * settle; port 0 = cell 0x8 (portw); 23x settle. A = cell 0x3EB5 & 2; nonzero joins the 4073 lane
 * (bc aneq); else B = 13, port45_poll_40A1(B) (call, C-bound), tail-joins 4095 (b). 4073 lane: B-save;
 * B = 13; port45_poll_40A1(B); A &= 3; nonzero retries the poll (bc aneq, whole-poll retry). B-restore;
 * settle. 4081 lane: B-save; port45_poll_40A1(B) (B dark-clobbered from prior lane, flagged); B = 13;
 * port45_poll_40A1(B); A &= 12; settle; A -= 12 (sub); nonzero retries the second poll (bc aneq).
 * B-restore; port45_poll_40A1(B) (B dark, flagged); B = A & 2048 (and dual); zero joins 409B (bc beq);
 * else A |= high-bit-4 (or #-4096, i.e. A |= 0xF000, low-16 only, upper preserved). B-restore (popm);
 * TC dark-callee-live (poll clobbers; unbound, flagged) taken returns (rc); INTM restore (rsbx); return.
 * B/TC caller-live, dead after (flagged).
 */
extern void port45_poll_40A1(int b_live);
extern int port_read_0(void);                                         /* HW port 0 (codec/RF control per 938c homology); no ROM definition */
extern void port_write_0(int v);                                      /* HW port 0 (codec/RF control per 938c homology); no ROM definition */

void frag_4057(long b_live)
{
    long a;
    long b;
    long a_out;  /* poll A-out (I/O-live, unbound, flagged) */
    long b_out;  /* poll B-out (clobbered, unbound, flagged) */
    int tc_dark;  /* TC dark-callee-live (unbound, flagged) */
    int i;


    b = b_live;                                            /* B caller-live (unbound) */
    /* pshm bl/bh/bg (balanced by popm; caller-live, comments only) */
    /* ssbx st1,intm (hardware, no C form) */
    a = (long)port_read_0();                               /* portr 0,*(0x8) */
    *(volatile int *)0x8 = (int)a;
    a |= 12L;                                              /* or #12,a */
    /* nop (settle) */
    port_write_0(*(volatile int *)0x8);                    /* portw *(0x8),0 */
    for (i = 0; i < 23; i++) {}                            /* rpt #22 nop */
    a = (long)*(volatile int *)0x3EB5 & 2L;                /* ld; and #2,a */
    if (a != 0)                                            /* bc 0x4073,aneq */
        goto l4073;
    b = 13;                                                /* ld #13,b */
    port45_poll_40A1(13);                                  /* call 0x40a1 */
    goto l4095;                                            /* b 0x4095 */
l4073:
    /* pshm bl/bh/bg (balanced; caller-live, comments only) */
    b = 13;                                                /* ld #13,b (loop preset) */
    do {                                                 /* bc 0x4076,aneq */
        port45_poll_40A1(13);                              /* call 0x40a1 */
        a = a_out & 3L;                                    /* and #3,a */
    } while (a != 0);
    b = b_out;                                               /* poll B-out (unbound) */
    /* popm bg/bh/bl (restore entry state) */
    /* nop (settle) */
    /* pshm bl/bh/bg (balanced; caller-live, comments only) */
    port45_poll_40A1((int)(b & 0xFFFF));                   /* call 0x40a1 (B dark) */
    b = 13;                                                /* ld #13,b */
    do {                                                 /* bc 0x4086,aneq */
        port45_poll_40A1(13);                              /* call 0x40a1 */
        a = a_out & 12L;                                   /* and #12,a */
        /* nop (settle) */
        a = a - 12;                                        /* sub #12,a */
    } while (a != 0);
    b = b_out;                                               /* poll B-out (unbound) */
    /* popm bg/bh/bl (restore entry state) */
    port45_poll_40A1((int)(b & 0xFFFF));                   /* call 0x40a1 (B dark) */
l4095:
    b = a & 2048L;                                         /* and #2048,a,b */
    if (b == 0)                                            /* bc 0x409b,beq */
        goto l409b;
    a |= 0xF000L;                                          /* or #-4096,a (low-16) */
l409b:
    /* popm bg/bh/bl (restore entry state) */
    if (tc_dark)                                           /* rc tc (unbound, flagged) */
        return;
    /* rsbx st1,intm (hardware, no C form) */
    /* ret @40A0 */
    (void)a_out; (void)b_out; (void)tc_dark;
}
