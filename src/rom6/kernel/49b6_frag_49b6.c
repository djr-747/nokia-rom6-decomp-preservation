/* ROM6 ORIGIN 0x49B6 (65w): marker-gated mode dispatcher with ack-cell lanes.
 *
 * Verified encoding: src/rom6/kernel/49b6_frag_49b6.asm (recombine MATCH).
 *
 * Shape: cmpm/bc poll on cells 0x250F/#34 and 0x34BF (mode id 1/3/4),
 * three BCD-AEQ lanes through ack cells (delay: st #1,*ar5 always runs,
 * branch tests pre-delay A per op_bcd), pure tail fan-out; no ret.
 *
 * Entry: no in-span register setup. AR5 = ack-cell pointer (stored by the
 * always-run bcd delay and read by 4AE0/4A4B -> int * param). B, AR4, AR2
 * pass through untouched to the 4A19/4A4B tails -> caller-live params.
 * A is loaded in-span (ld 0x366F/0x37B0/0x2656). Dark tails 49D0/49D8/49DE/4A1E
 * are exterior with unknown live-ins -> parameterless, noted as dark.
 * Cells 0x250F/0x34BF/0x366F/0x37B0/0x2656 and ack cell are PROM/model state.
 *
 * ROM: build/rom6/prom.lst @0x49B6. Oracle: vendor ti-c54x
 * src/isa/ops/op_cmpm_smem_lk.c, op_bcd.c, op_branch_sind_common.c.
 * EXPECT transcription verified against the slice (see EXPECT below).
 */

extern void frag_49D0(void);   /* dark tail */
extern void frag_49D8(void);   /* dark tail */
extern void frag_49DE(void);   /* dark tail */
extern void frag_4AE0(int *par5);
extern void frag_4A01(void);
extern void frag_4A19(int b_live, int *par4, int *par5, int *par2);
extern void frag_49F7(void);
extern void frag_4A1E(void);   /* dark tail */
extern void frag_4A4B(int b_live, int *par5);

extern int PROM[];

/* frag_49B6: marker-gated dispatcher; every path tails out (no ret). */
void frag_49B6(int b_live_in, int *ar4_in, int *ar5_in, int *ar2_in)
{
    int a;

    /* cmpm *(0x250F),#34; bc 49D8,ntc: marker mismatch exits the region. */
    if (PROM[0x250F] != 34) {
        frag_49D8();                                   /* tail, dark */
        return;
    }
    /* Mode 1 or 4 enters the polled ack lane (two tc exits to 49D0). */
    if (PROM[0x34BF] == 1 || PROM[0x34BF] == 4) {
        /* 49D0 lane: test ack cell 0x2656. */
        a = PROM[0x2656];
        *ar5_in = 1;                                   /* bcd delay (always runs) */
        if (a == 0) {
            frag_4AE0(ar5_in);                         /* tail */
            return;
        }
        if (PROM[0x250F] != 34) {
            frag_4A19(b_live_in, ar4_in, ar5_in, ar2_in); /* tail */
            return;
        }
        if (PROM[0x34BF] != 3) {
            frag_4A01();                               /* tail */
            return;
        }
        if (PROM[0x366F] != 15) {
            frag_49F7();                               /* tail */
            return;
        }
        PROM[0x366F] = 0;                              /* st #0,*(0x366F) */
        if (PROM[0x37B0] == 15) {
            frag_4A1E();                               /* tail, dark */
            return;
        }
        frag_4A4B(b_live_in, ar5_in);                  /* tail */
        return;
    }
    /* Default lane: test ack cell 0x366F. */
    a = PROM[0x366F];
    *ar5_in = 1;                                       /* bcd delay (always runs) */
    if (a == 0) {
        frag_4AE0(ar5_in);                             /* tail */
        return;
    }
    if (PROM[0x34BF] != 3) {
        frag_49DE();                                   /* tail, dark */
        return;
    }
    a = PROM[0x37B0];
    *ar5_in = 1;                                       /* bcd delay (always runs) */
    if (a == 0) {
        frag_4AE0(ar5_in);                             /* tail */
        return;
    }
    frag_49DE();                                       /* b 49DE; tail, dark */
}

/* EXPECT: 60F8 250F 0022 F820 49D8 60F8 34BF 0001 F830 49D0 60F8 34BF 0004 F830 49D0 10F8 366F FA45 4AE0 7685 0001 60F8 34BF 0003 F820 49DE 10F8 37B0 FA45 4AE0 7685 0001 F073 49DE 10F8 2656 FA45 4AE0 7685 0001 60F8 250F 0022 F820 4A19 60F8 34BF 0003 F820 4A01 60F8 366F 000F F820 49F7 76F8 366F 0000 60F8 37B0 000F F830 4A1E F073 4A4B */
