/* ROM6 ORIGIN 0x3273 (65w): SUB_3273A -- scaled-copy head with PA33/PA36 tail.
 * Verified encoding: src/rom6/kernel/3273_sub_3273a.asm (recombine MATCH).
 * EXPECT: 61F8 3EC8 0020 6FD2 0C45 8815 FF20 F000 3158 FF30 F000 12D0 8814 F495 EC1F E5CA F074 2E2F 4815 F010 0060 F844 2E64 F7BB 74F8 000B 0021 F340 0005 F330 FFFD F495 75F8 000B 0021 61F8 3EC8 0020 7713 3158 FF30 7713 12D0 771A 007F F072 32A5 F495 7593 0024 F495 74F8 000B 0021 F330 FFFB F340 0003 F495 75F8 000B 0021 F6BB F073 2E64
 *
 * Intent: A = (*AR2 << 5) + (TC ? 4816 : 12632), TC = bit 5 of cell
 * 0x3EC8 (bitf ANY-bit; xc 2,ntc covers the 2-word add #12632, xc 2,tc
 * the 2-word add #4816, per op_xc). AR5 = A-low, AR4 = A-low (stlm pair).
 * 32-word copy *AR2(+AR0 circular) -> *AR4++ (rpt #31 + mvdd; +0% step
 * convention, circular wrap needs caller-live BK, linear flagged).
 * Dark call 0x2E2F always runs. A = AR5 (ldm zero-extends, oracle);
 * A -= 96; nonzero tails to dark 0x2E64 (bc aneq). Else INTM = 1
 * (hardware, no C form): cell 0x0B = PA33 (portr), B = (B|5)&-3, PA33 =
 * cell 0x0B (unchanged round-trip; or/and target B, not the cell).
 * AR3 = TC ? 4816 : 12632 (xc 2,tc over the 2-word stm; TC re-read from
 * cell 0x3EC8 bit 5). BRC = 127; rptb 0x32A5: RSA = PC+2 = 0x32A2,
 * REA = 0x32A5, block [RSA,REA] inclusive (oracle sequencer
 * repeat_block.c: block ends with the instruction whose last word is
 * REA), nop + portw *ar3+,36 + nop x128 (PA36 sweep of 128 successive
 * cells). Then cell 0x0B = PA33,
 * B = (B&-5)|3, PA33 = cell, INTM = 0, tail to dark 0x2E64 (b).
 * B is caller-live in, modified in-span, live
 * out to the dark tail (liveness flagged). AR2/AR0 caller-live (value,
 * step). No ret: every path tails. Bound 3273-32B3 (abuts 3273b @32B4).
 */
extern void dispatcher_entry_2E2F(void);
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */
extern int port_read_33(void);                                        /* HW port 33 (SAMPLE handshake per 22F3 span); no ROM definition */
extern void port_write_33(int v);                                     /* HW port 33 (SAMPLE handshake per 22F3 span); no ROM definition */
extern void port_write_36(int v);                                     /* HW port 36 (per 3273/4b06 spans); no ROM definition */

void sub_3273A(int *ar2_in, int ar0_live, int b_live_in)
{
    long a;
    long b = (long)b_live_in;
    int tc;
    int *ar2 = ar2_in;
    int *ar4;
    int ar5;
    int *ar3;
    int i;
    int cellB;

    tc = (*(volatile int *)0x3EC8 & 32) != 0;   /* bitf *(0x3ec8),#32 */
    a = (long)*ar2;                             /* ld *ar2+%,5,a */
    ar2 += ar0_live;                            /* +0% (wrap flagged) */
    a <<= 5;
    if (!tc)                                    /* xc 2,ntc */
        a += 12632;                             /* add #12632,a */
    if (tc)                                     /* xc 2,tc */
        a += 4816;                              /* add #4816,a */
    ar5 = (int)(a & 0xFFFF);                    /* stlm a,ar5 */
    ar4 = (int *)(int)(a & 0xFFFF);             /* stlm a,ar4 */
    /* nop */
    for (i = 0; i < 32; i++) {                  /* rpt #31 */
        *ar4++ = *ar2;                          /* mvdd *ar2+0%,*ar4+ */
        ar2 += ar0_live;                        /* +0% (wrap flagged) */
    }
    dispatcher_entry_2E2F();                                 /* call 0x2e2f (dark, always runs) */
    a = (long)(unsigned)ar5;                    /* ldm ar5,a (zero-extend) */
    a -= 96;                                    /* sub #96,a */
    if (a != 0) {                               /* bc 0x2e64,aneq */
        frag_2E64();                            /* tail, dark */
        return;
    }
    /* ssbx st1,intm (hardware, no C form) */
    cellB = port_read_33();                     /* portr 33,*(0xb) */
    b |= 5;                                     /* or #5,b */
    b &= -3;                                    /* and #-3,b */
    /* nop */
    port_write_33(cellB);                       /* portw *(0xb),33 */
    tc = (*(volatile int *)0x3EC8 & 32) != 0;   /* bitf *(0x3ec8),#32 */
    ar3 = (int *)12632;                         /* stm #12632,ar3 */
    if (tc)                                     /* xc 2,tc */
        ar3 = (int *)4816;                      /* stm #4816,ar3 */
    /* stm #127,brc */
    /* rptb 0x32a5: RSA = PC+2 = 0x32a2, REA = 0x32a5, block [RSA,REA]
       inclusive = nop + portw *ar3+,36 + nop, BRC+1 = 128 passes
       (PA36 sweep; trailing nop pads each pass). */
    for (i = 0; i < 128; i++) {
        /* nop */
        port_write_36(*ar3++);                  /* portw *ar3+,36 */
        /* nop */
    }
    /* nop */
    cellB = port_read_33();                     /* portr 33,*(0xb) */
    b &= -5;                                    /* and #-5,b */
    b |= 3;                                     /* or #3,b */
    /* nop */
    port_write_33(cellB);                       /* portw *(0xb),33 */
    /* rsbx st1,intm (hardware, no C form); B live-out flagged */
    frag_2E64();                                /* b 0x2e64; tail, dark */
}
