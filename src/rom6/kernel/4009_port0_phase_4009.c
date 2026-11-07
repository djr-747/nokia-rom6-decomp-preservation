/* ROM6 0x4009 PORT0_PHASE_4009 -- 76w.
 * Verified encoding: src/rom6/kernel/4009_port0_phase_4009.asm (recombine MATCH).
 * ORIGIN 0x4009
 * EXPECT: 4A08 4A09 4A0A 61F8 0007 0800 F7BB 74F8 0008 0000 F040 000C F495 75F8 0008 0000 EC16 F495 10F8 3EB5 F030 0002 F845 403D F210 0007 F844 4030 8A0A 8A09 8A08 F495 F495 75F8 0008 0028 4A08 4A09 4A0A 4A0B 4A0C 4A0D E90D F074 40A1 F030 0003 F844 4033 8A0D 8A0C 8A0B 74F8 0009 002D F063 1000 F844 403D 8A0A 8A09 8A08 F495 F495 75F8 0008 002D F330 FFEF F495 75F8 000B 002C FC30 F6BB FC00
 *
 * Intent: Port-0 transaction phase with 40A1 poll loop and pa45 retry. A-save (pshm al/ah/ag, balanced);
 * TC = cell 0x7 bit 11 (bitf); INTM guard (ssbx, hardware, no C form); A = port 0 (portr); A |= 12 (or);
 * settle; port 0 = cell 0x8 (portw); 23x settle (rpt #22). A = cell 0x3EB5 & 2; zero joins the 403D lane
 * (bc aeq). A = B-live - 7 (sub dual; B caller-live, unbound, flagged); nonzero joins the 4030 lane
 * (bc aneq). B == 7 lane: A-restore (popm), settles, port 40 = cell 0x8 (portw), falls into 4030. Lane:
 * B-save (pshm bl/bh/bg, balanced); B = 13; port45_poll_40A1(B) (call, C-bound); A &= 3; nonzero retries
 * the poll (bc aneq). B-restore (popm). 403D lane: port 45 read to cell 9 (portr); A &= high-bit-12;
 * nonzero retries the read (bc aneq). A-restore (popm); settles; port 45 = cell 0x8 (portw); B &= -17
 * (and; B dark-clobbered by the poll, flagged); settle; port 44 = cell 0xB (portw); TC
 * dark-callee-live (40A1 clobbers; unbound, flagged) taken returns (rc); INTM restore (rsbx); return.
 * B/TC caller-live, dead after (flagged).
 */
extern void port45_poll_40A1(int b_live);
extern int port_read_0(void);                                         /* HW port 0 (codec/RF control per 938c homology); no ROM definition */
extern void port_write_0(int v);                                      /* HW port 0 (codec/RF control per 938c homology); no ROM definition */
extern void port_write_40(int v);                                     /* HW port 40 (port-0 phase per 4009 span); no ROM definition */
extern int port_read_45(void);                                        /* HW port 45 (port-45 poll per 40A1 span); no ROM definition */
extern void port_write_45(int v);                                     /* HW port 45 (port-45 poll per 40A1 span); no ROM definition */
extern void port_write_44(int v);                                     /* HW port 44 (port-45 poll family per 40A1 span); no ROM definition */

void frag_4009(long b_live)
{
    long a;
    long b;
    long a_out_40a1;  /* 40A1 A-out (I/O-live, unbound, flagged) */
    int tc_dark;  /* TC dark-callee-live (unbound, flagged) */
    int i;


    b = b_live;                                            /* B caller-live (unbound) */
    /* pshm al/ah/ag (balanced by popm; caller-live, comments only) */
    /* ssbx st1,intm (hardware, no C form) */
    a = (long)port_read_0();                               /* portr 0,*(0x8) */
    *(volatile int *)0x8 = (int)a;
    a |= 12L;                                              /* or #12,a */
    /* nop (settle) */
    port_write_0(*(volatile int *)0x8);                    /* portw *(0x8),0 */
    for (i = 0; i < 23; i++) {}                            /* rpt #22 nop */
    a = (long)*(volatile int *)0x3EB5 & 2L;                /* ld; and #2,a */
    if (a == 0)                                            /* bc 0x403d,aeq */
        goto l403d;
    a = b - 7;                                             /* sub #7,b,a */
    if (a != 0)                                            /* bc 0x4030,aneq */
        goto l4030;
    /* popm ag/ah/al (restore entry state) */
    /* nop; nop (settles) */
    port_write_40(*(volatile int *)0x8);                    /* portw *(0x8),40 */
l4030:
    /* pshm bl/bh/bg (balanced by popm; caller-live, comments only) */
    b = 13;                                                /* ld #13,b (loop preset) */
    do {                                                 /* bc 0x4033,aneq */
        port45_poll_40A1(13);                              /* call 0x40a1 */
        a = a_out_40a1 & 3L;                               /* and #3,a (A-out I/O) */
    } while (a != 0);
    /* popm bg/bh/bl (restore entry state) */
l403d:
    do {                                                 /* bc 0x403d,aneq */
        a = (long)port_read_45();                        /* portr 45,*(0x9) */
        *(volatile int *)0x9 = (int)a;
        a &= 0x10000000L;                                /* and #4096,16,a */
    } while (a != 0);
    /* popm ag/ah/al (restore entry state) */
    /* nop; nop (settles) */
    port_write_45(*(volatile int *)0x8);                  /* portw *(0x8),45 */
    b &= -17L;                                           /* and #-17,b (B dark, flagged) */
    /* nop (settle) */
    port_write_44(*(volatile int *)0xB);                  /* portw *(0xb),44 */
    if (tc_dark)                                         /* rc tc (unbound, flagged) */
        return;
    /* rsbx st1,intm (hardware, no C form) */
    /* ret @4054 */
}
