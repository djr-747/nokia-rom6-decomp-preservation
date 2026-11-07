/* ROM6 0xDFCF PORT_DISPATCH_DFCF -- 47w (span DFCF-DFFD, ret @DFFD).
 * Verified encoding: src/rom6/rf/dfcf_port_dispatch_dfcf.asm (recombine MATCH).
 * ORIGIN 0xDFCF
 * EXPECT: F074 0682 4A06 4A07 4A16 7707 0740 7719 0000 11F8 0C4C F330 0001 F84D DFE6 11F8 0C4C F330 FFFE F274 DC43 81F8 0C4C F274 DC2E 7714 0D94 771A 009F F272 DFF2 7712 0D94 6F82 0C5D 9883 EA00 771A 004F F274 DFFE 7712 0D92 8A16 8A07 8A06 FC00
 *
 * Intent: Port-dispatch worker with guarded subcalls (caller AA2A).
 * Runs dark SUB_0682 (no symbol, opaque). pshm st0/st1/ar6 (entry
 * preserved, never read through the copies -- comments only per
 * 5d38). ST1 = 1856 in-lane (stm; SXM bit clear -> all in-lane
 * shifts logical, exact; OVM/CPL effects flagged; restored by
 * popm). BK = 0 (stm; unused in-span, caller-observable, not
 * carried). B = *(0xC4C) & 1 (ld/and); zero skips the DC43 lane
 * (bc 0xdfe6,beq to the in-span LDFE6). Else B = *(0xC4C) & -2
 * (ld/and, volatile re-read); MEM[0xC4C] = B-low (stl: the calld
 * 0xdc43 delay, always runs before the call); runs pooled
 * SUB_DC43 (forward extern void sub_DC43; returns to LDFE6).
 * LDFE6 lane: AR4 = 3476 (stm: the calld 0xdc2e delay, runs before
 * the call); runs linked SUB_DC2E (C: sub_DC2E(ar4)). BRC = 159
 * (folded); rptbd block DFF0-DFF2, 160 passes (delays stm AR2 =
 * 3476 once; RPTBD PC+4 convention per d5ca, Z=1 flagged): per
 * pass A = *(AR2) >> 3 logical (ld *ar2,-3,a; SXM = 0 proven, so
 * (unsigned) shift exact); MEM[*AR2++] = (A << 3) & 0xFFFF (stl
 * a,3,*ar2+ per the 4b2c precedent). AR2-out = 3636 (local, not
 * carried); A dead after (void lane). DP = 0 (ld #0,dp; hardware,
 * comment). BRC = 79 (folded, then overwritten -- hmm, actually
 * stm #79,brc re-arms BRC but no rptbd follows; dead MMR write,
 * noted). calld 0xdffe with delay stm AR2 = 3474 first; runs
 * linked ROUTINE_DFFE (C: routine_DFFE; returns to popm). popm
 * ar6/st1/st0 restores entry state; return. No entry live-ins
 * (ARs set or preserved, A/B recomputed); void.
 */
extern void sub_0682(void);                          /* dark, no symbol */
extern void sub_DC43(void);                          /* asm-only, forward extern */
extern void sub_DC2E(int *ar4);                      /* linked C */
extern void routine_DFFE(void);                      /* linked C */

void frag_DFCF(void)
{
    long a;
    long b;
    int *ar2;
    int *ar4;
    int pass;
    sub_0682();                                      /* call 0x682 */
    /* pshm st0/st1/ar6 (balanced by popm; caller-live, comments only) */
    /* stm #1856,st1 (in-lane status; SXM=0 -> logical shifts, exact) */
    /* stm #0,bk (unused in-span, not carried) */
    b = (long)*(volatile int *)0xC4C;                /* ld *(0xc4c),b */
    if ((b & 1L) == 0)                               /* and #1,b; bc 0xdfe6,beq */
        goto ldfe6;
    b = (long)*(volatile int *)0xC4C;                /* ld *(0xc4c),b (re-read) */
    b &= -2L;                                        /* and #-2,b */
    *(volatile int *)0xC4C = (int)(b & 0xFFFF);      /* calld delay: stl (always runs) */
    sub_DC43();                                      /* calld 0xdc43 (returns to ldfe6) */
ldfe6:
    ar4 = (int *)(long)3476;                         /* calld delay: stm (always runs) */
    sub_DC2E(ar4);                                   /* calld 0xdc2e */
    /* stm #159,brc (folded); rptbd 0xdff2 */
    ar2 = (int *)(long)3476;                         /* rptbd delay: stm (once) */
    for (pass = 0; pass < 160; pass++) {             /* rptbd block DFF0-DFF2 */
        a = (long)(unsigned)*ar2 >> 3;                /* ld *ar2,-3,a (SXM=0 logical) */
        *ar2++ = (int)(((unsigned long)a << 3) & 0xFFFF); /* stl a,3,*ar2+ */
    }
    (void)ar2;                                       /* AR2-out = 3636, not carried */
    /* ld #0,dp (hardware, no C form) */
    /* stm #79,brc (dead MMR write: no rptbd follows, noted) */
    ar2 = (int *)(long)3474;                         /* calld delay: stm (always runs) */
    (void)ar2;
    routine_DFFE();                                  /* calld 0xdffe */
    /* popm ar6/st1/st0 (restore entry state) */
}
