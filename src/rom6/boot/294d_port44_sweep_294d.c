/* ROM6 0x294D PORT44_SWEEP_294D -- 29w.
 * Verified encoding: src/rom6/boot/294d_port44_sweep_294d.asm (recombine MATCH).
 * ORIGIN 0x294D
 * EXPECT: F074 072E 771A 001D 7713 28D9 E903 F072 2968 F495 75F8 000B 002C F495 F495 7593 002D F495 74F8 0009 002D F063 1000 F844 295F EC1E F495 F495 FC00
 *
 * Intent: Port-44 sweep with bounded retry. Runs dark 0x72E (forward extern); BRC = 29; AR3 = 10457;
 * 30x rptb block: port 44 = cell 0xB; port 45 = *AR3++; read port 45 to cell 9; A = read masked with
 * 0x10000000 (and #4096,16); nonzero retries the read (bc 295F,aneq -- inner retry, still inside the
 * rptb block); then 31x settle nops (rpt #30); return. Post-branch head (prev b 283D); no exterior
 * callers, entry unconfirmed, flagged.
 */
extern void sub_072E(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void port_write_44(int v);                                     /* HW port 44 (port-45 poll family per 40A1 span); no ROM definition */
extern void port_write_45(int v);                                     /* HW port 45 (port-45 poll per 40A1 span); no ROM definition */
extern int port_read_45(void);                                        /* HW port 45 (port-45 poll per 40A1 span); no ROM definition */

void frag_294D(void)
{
    long a;
    int *ar3;
    int i;

    sub_072E();                                            /* call 0x72e */
    ar3 = (int *)10457;                                    /* stm #10457,ar3 */
    /* stm #29,brc; rptb 0x2968 (30 iters) */
    for (i = 0; i < 30; i++) {
        /* nop (settle) */
        port_write_44(*(volatile int *)0xB);                /* portw *(0xb),44 */
        /* nop; nop */
        port_write_45(*ar3++);                              /* portw *ar3+,45 */
        /* nop */
        do {                                               /* bc 0x295f,aneq retry */
            a = (long)port_read_45();                      /* portr 45,*(0x9) */
            *(volatile int *)0x9 = (int)a;
            a &= 0x10000000L;                              /* and #4096,16,a */
        } while (a != 0);
        for (a = 0; a < 31; a++) {}                        /* rpt #30 nop (settle) */
    }
    /* ret @2969 */
    (void)a;
}
