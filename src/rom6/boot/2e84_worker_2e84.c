/* ROM6 0x2E84 WORKER_2E84 -- 66w (span 2E84-2EC5, two entries).
 * Verified encoding: src/rom6/boot/2e84_worker_2e84.asm (recombine MATCH).
 * ORIGIN 0x2E84
 * EXPECT: 12D2 F030 00FF 1382 F3F8 8911 4915 F310 0002 F073 2EB7 61F8 0866 0001 F820 2EAD F074 2D8F F846 2EB7 F7BB E802 F495 75F8 0008 0001 EC14 F495 68F8 0866 FFFE 74F8 0008 0002 F030 FFFD F495 75F8 0008 0002 F6BB 61F8 0866 0002 FC20 68F8 0866 FFFD F074 2DE4 FC45 F074 0620 8914 F110 0057 F84F 2ECD F110 0070 F84C 2EC6 F074 43BA F073 2E64
 *
 * Intent: Boot HPI/port dispatch worker with a hot mid-entry. The
 * 2E84 head is trace-cold (zero hits in both pchist runs); the
 * 2E8F mid-entry is hot (275x, 1:1 with the 2E64 caller: 2E64
 * branches to 0x2E8F directly on the bit-clear path, and the
 * never-taken beq path would enter 2E84). Shared static tail_2EB7
 * per the 5362 sled precedent (one file, N entry functions, one
 * EXPECT). Head entry worker_2E84: A = *AR2++ unsigned (ldu,
 * circular BK wrap flagged, linear ++ in C); A &= 255 (and);
 * B = *AR2 unsigned (ldu, no step); B >>= 8 (sftl, B >= 0 from
 * ldu so logical == arith, exact); AR1 = B-low (stlm, dead: the
 * dark 0x620 call may clobber ARs, liveness unbound, flagged
 * not-carried); B = AR5-value (ldm ar5,b, zero-extend per the
 * 3273 precedent); B -= 2 (sub, dead: dark call clobbers B);
 * joins the shared tail (b 0x2eb7). Mid entry frag_2E8F (entry
 * A/B unread, recomputed or dark-sourced in-span; AR2/SP live):
 * TC = (cell 0x866 & 1) != 0 (bitf, 5d38 polarity); clear skips
 * the HPI call (bc 0x2ead,ntc). Else runs C-bound SUB_2D8F (call,
 * SP threaded as its explicit dark-ISR-context param); its
 * void-C A-out is hardware-live for the agt test, carried as an
 * unbound local (afab precedent, flagged). A > 0 joins the tail
 * (bc 0x2eb7,agt). Else the port 1/2 strobe under INTM (ssbx,
 * hardware): A = 2 (ld); settle nop; port 1 = cell *(0x8)
 * (portw); 21 settle cycles (rpt #20, 2a5f precedent); cell
 * 0x866 &= ~2 (andm); A = port 2 (portr, AL-alias cell write per
 * the 2867 precedent); A &= ~3 (and); settle nop; port 2 = A
 * (portw); INTM restore (rsbx, hardware). L2EAD: TC = (cell
 * 0x866 & 2) != 0; clear returns (rc ntc); cell 0x866 &= ~3;
 * runs C-bound ISR_2DE4 (call, void); its uncarried A-out gates
 * the aeq return (rc aeq, unbound local, flagged); falls into
 * the shared tail. Shared tail_2EB7: runs dark SUB_0620 (call,
 * forward extern void); A/B outs unbound locals (flagged);
 * AR4-slot = B-low (stlm, 43BA-clobber unbound, flagged);
 * B = A - 87 (sub); B <= 0 runs C-bound FRAG_2ECD with A (bc
 * 0x2ecd,bleq); B = A - 112 (sub); nonzero runs C-bound
 * FRAG_2EC6 (bc 0x2ec6,bneq, void); else runs dark SUB_43BA
 * (call); B-out unbound; tail-enters DISPATCH_MATCH_LOOP (b
 * 0x2e64) with B = 43BA B-out low, AR2 = entry cursor, and the
 * AR4 slot (*ppar4 write-only in the callee, never read).
 * AR2 unstepped after the head (ldu block); BK/INTM hardware.
 */
extern void sub_2D8F(int *sp);                           /* C-bound, SP explicit */
extern void isr_2DE4(void);                              /* C-bound, A-out uncarried */
extern void sub_0620(void);                              /* dark, no symbol */
extern void sub_43BA(void);                              /* dark, no symbol */
extern void frag_2ECD(long a);                           /* C-bound */
extern void frag_2EC6(void);                             /* C-bound */
extern void dispatch_match_loop(int b_live, int *par2, int **ppar4);
extern int port_read_2(void);                                         /* HW port 2 (FRAME sample combine per 27EB span); no ROM definition */
extern void port_write_1(int v);                                      /* HW port 1 (RF/codec per 3EE1 sweep); no ROM definition */
extern void port_write_2(int v);                                      /* HW port 2 (supervisor per 2875 precedent); no ROM definition */

static void tail_2EB7(int *ar2)
{
    long a_620;                                          /* unbound: dark 0620 A-out (flagged) */
    long b_620;                                          /* unbound: dark 0620 B-out (flagged) */
    long b;
    long b_43ba;                                         /* unbound: dark 43BA B-out (flagged) */
    int *ar4slot;
    sub_0620();                                          /* call 0x620 (dark) */
    ar4slot = (int *)(long)(b_620 & 0xFFFFL);            /* stlm b,ar4 (43BA-clobber flagged) */
    b = a_620 - 87L;                                     /* sub #87,a,b */
    if (b <= 0) {                                        /* bc 0x2ecd,bleq */
        frag_2ECD(a_620);
        return;
    }
    b = a_620 - 112L;                                    /* sub #112,a,b */
    if (b != 0) {                                        /* bc 0x2ec6,bneq */
        frag_2EC6();
        return;
    }
    sub_43BA();                                          /* call 0x43ba (dark) */
    dispatch_match_loop((int)(b_43ba & 0xFFFFL), ar2, &ar4slot);
    /* b 0x2e64 tail */
}

void frag_2E8F(int *ar2_in, int *sp_in)
{
    long a;
    long a_2d8f;                                         /* unbound: void-C 2D8F A-out (flagged) */
    long a_2de4;                                         /* unbound: void-C 2DE4 A-out (flagged) */
    int tc;
    int i;
    int *ar2 = ar2_in;
    tc = (*(volatile int *)0x866 & 1) != 0;              /* bitf *(0x866),#1 */
    if (!tc)                                             /* bc 0x2ead,ntc */
        goto l2ead;
    sub_2D8F(sp_in);                                     /* call 0x2d8f */
    if (a_2d8f > 0) {                                    /* bc 0x2eb7,agt */
        tail_2EB7(ar2);
        return;
    }
    /* ssbx st1,intm (hardware, no C form) */
    a = 2;                                               /* ld #2,a */
    /* nop (settle) */
    port_write_1(*(volatile int *)0x8);                   /* portw *(0x8),pa1 */
    for (i = 0; i < 21; i++) {}                          /* rpt #20; nop */
    *(volatile int *)0x866 &= -2;                         /* andm #-2,*(0x866) */
    a = (long)port_read_2();                             /* portr pa2,*(0x8) */
    *(volatile int *)0x8 = (int)a;                       /* AL alias write (2867 precedent) */
    a &= -3L;                                            /* and #-3,a */
    /* nop (settle) */
    port_write_2((int)a);                                /* portw *(0x8),pa2 */
    /* rsbx st1,intm (hardware, no C form) */
l2ead:
    tc = (*(volatile int *)0x866 & 2) != 0;              /* bitf *(0x866),#2 */
    if (!tc)                                             /* rc ntc */
        return;
    *(volatile int *)0x866 &= -3;                         /* andm #-3,*(0x866) */
    isr_2DE4();                                          /* call 0x2de4 */
    if (a_2de4 == 0)                                     /* rc aeq */
        return;
    tail_2EB7(ar2);                               /* fall into 2EB7 */
}

void worker_2E84(int *ar2_in, int *ar5_in)
{
    long a;
    long b;
    int ar1;
    int *ar2 = ar2_in;
    a = (long)(unsigned)*ar2++;                          /* ldu *ar2+%,a (BK wrap flagged) */
    a &= 255L;                                           /* and #255,a */
    b = (long)(unsigned)*ar2;                            /* ldu *ar2,b (no step) */
    b >>= 8;                                             /* sftl b,-8 (b >= 0, exact) */
    ar1 = (int)(b & 0xFFFFL);                            /* stlm b,ar1 (dead, flagged) */
    (void)ar1;
    b = (long)(unsigned)ar5_in;                          /* ldm ar5,b (3273 precedent) */
    b -= 2;                                              /* sub #2,b (dead: dark call clobbers) */
    (void)b;
    tail_2EB7(ar2);                               /* b 0x2eb7 */
}
