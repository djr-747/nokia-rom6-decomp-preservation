/* ROM6 0x3A26 PA60_57_WRITER_B -- 91w.
 * Verified encoding: src/rom6/kernel/3a26_pa60_57_writer_b.asm (recombine MATCH).
 * ORIGIN 0x3A26
 * EXPECT: E800 F074 0632 60F8 250F 0022 F820 3A41 11F8 2512 F330 0200 F84D 3A41 F7BB 74F8 000B 0038 F330 0008 F84D 3A40 F6BB F4E1 F073 3A27 F6BB E903 F495 75F8 000B 003C E905 F495 75F8 000B 003C 771A 000B F072 3A51 F495 7592 0039 E903 F844 3A5E 771A 0001 F072 3A5C F495 7592 0039 F495 E905 F020 FFFC F495 75F8 0008 003C E802 F495 75F8 0008 003C F7BB 74F8 0008 0000 F040 0060 F495 75F8 0008 0000 EC15 F495 F6BB 74F8 0008 0038 F030 0010 F1A0 F495 75F8 000B 0038 FC00
 *
 * Intent: RF port strobe with poll loop-back. A = 0
 * (possible 0632 intake, A-out unbound); loop head at the
 * call (b 0x3a27 re-enters it): runs 0x632 (dark, extern;
 * A re-clobbered opaquely every pass, flagged); TC =
 * (cell 0x250F == 34) (cmpm, oracle: TC = equality);
 * mismatch breaks to the 3A41 lane; B = cell 0x2512 &
 * 512, zero breaks to 3A41 (bc beq); INTM = 1 (ssbx,
 * hardware state); B = port 56 with BL-alias write
 * (portr 56,*(0xb) per the 37C0 mirror pattern);
 * B &= 8, zero breaks to the 3A40 exit (bc beq; the
 * 3A40 rsbx is notional); else INTM = 0 (rsbx,
 * notional), 1 idle cycle (cpu_idle, extern-op
 * placeholder), loop back. 3A41 lane: B = 3, port 60 =
 * B (portw *(0xb),60 reads the BL mirror per 37C0);
 * B = 5, port 60 = B. BRC = 11; 12 passes (rptb 0x3a51:
 * nop, port 57 = *(AR2++)); B = 3; the final-pass 0632
 * A-residue nonzero skips the extra fill (bc 0x3a5e,aneq
 * on the a_0632_out param, flagged), zero runs BRC = 1
 * with 2 passes (rptb 0x3a5c: nop, port 57, nop; REA
 * 0x3a5c) then B = 5. Join: A = -4, port 60 = BL
 * (B-carried 3 or 5); A = 2, port 60 = BL; INTM = 1
 * (ssbx); A = port 0 with alias write; A |= 96;
 * port 0 = A; 22 settle cycles (rpt #21 nop); INTM = 0
 * (rsbx, unconditional here, notional); A = port 56
 * with alias write; A &= 16; B |= A (or a,b); port 56 =
 * B; return. AR2 steps on a local (plain +1, no AR0);
 * ARs/A/B dead at return (flagged). Bound 3A26-3A80.
 */
extern void sub_0632(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern int port_read_56(void);                                        /* HW port 56 (HPI/pa56 poll per 2baa span); no ROM definition */
extern void port_write_60(int v);                                     /* HW port 60 (codec stream select per 399e span); no ROM definition */
extern void port_write_57(int v);                                     /* HW port 57 (codec stream per 399e span); no ROM definition */
extern int port_read_0(void);                                         /* HW port 0 (codec/RF control per 938c homology); no ROM definition */
extern void port_write_0(int v);                                      /* HW port 0 (codec/RF control per 938c homology); no ROM definition */
extern void port_write_56(int v);                                     /* HW port 56 (HPI/pa56 per 2baa span); no ROM definition */
extern void cpu_idle(int mode);                                       /* IDLE sleep (84af precedent: sleep until interrupt); no ROM definition */

void pa60_57_writer_b(long a_0632_out, int *ar2_in)
{
    int *ar2 = ar2_in;
    long a = 0;                                      /* ld #0,a (0632 intake?) */
    long b;
    int i;
    for (;;) {                                       /* loop head = call */
        sub_0632();                                  /* call (A-out unbound) */
        if (*(volatile int *)0x250F != 34)           /* cmpm; bc ntc */
            break;
        b = (long)*(volatile int *)0x2512;           /* ld *(0x2512),b */
        b &= 512;                                    /* and #512,b */
        if (b == 0)                                  /* bc 0x3a41,beq */
            break;
        /* ssbx st1,intm (hardware state) */
        b = port_read_56();                          /* portr 56,*(0xb) */
        *(volatile int *)0xB = (int)(b & 0xFFFF);    /* BL alias write */
        b &= 8;                                      /* and #8,b */
        if (b == 0)                                  /* bc 0x3a40,beq */
            break;                                   /* (3A40 rsbx notional) */
        /* rsbx st1,intm (hardware state) */
        cpu_idle(1);                                 /* idle 1 */
    }
    b = 3;                                           /* ld #3,b (3A41) */
    /* nop */
    port_write_60((int)(b & 0xFFFF));                /* portw *(0xb),60 */
    b = 5;                                           /* ld #5,b */
    /* nop */
    port_write_60((int)(b & 0xFFFF));                /* portw *(0xb),60 */
    /* stm #11,brc */
    for (i = 0; i < 12; i++) {                       /* rptb 0x3a51 */
        /* nop */
        port_write_57(*ar2++);                       /* portw *ar2+,57 */
    }
    b = 3;                                           /* ld #3,b */
    if (a_0632_out == 0) {                           /* bc 0x3a5e,aneq */
        /* stm #1,brc */
        for (i = 0; i < 2; i++) {                    /* rptb 0x3a5c */
            /* nop */
            port_write_57(*ar2++);                   /* portw *ar2+,57 */
            /* nop (REA 0x3a5c) */
        }
        b = 5;                                       /* ld #5,b */
    }
    a = -4;                                          /* ld #-4,a */
    /* nop */
    port_write_60((int)(b & 0xFFFF));                /* portw *(0xb),60 */
    a = 2;                                           /* ld #2,a */
    /* nop */
    port_write_60((int)(b & 0xFFFF));                /* portw *(0xb),60 */
    /* ssbx st1,intm (hardware state) */
    a = port_read_0();                               /* portr 0,*(0x8) */
    *(volatile int *)0x8 = (int)(a & 0xFFFF);        /* AL alias write */
    a |= 96;                                         /* or #96,a */
    /* nop */
    port_write_0((int)(a & 0xFFFF));                 /* portw *(0x8),0 */
    /* rpt #21 nop: 22 settle cycles */
    /* nop */
    /* rsbx st1,intm (hardware state, unconditional) */
    a = port_read_56();                              /* portr 56,*(0x8) */
    *(volatile int *)0x8 = (int)(a & 0xFFFF);        /* AL alias write */
    a &= 16;                                         /* and #16,a */
    b |= a;                                          /* or a,b */
    /* nop */
    port_write_56((int)(b & 0xFFFF));                /* portw *(0xb),56 */
    /* ret */
}
