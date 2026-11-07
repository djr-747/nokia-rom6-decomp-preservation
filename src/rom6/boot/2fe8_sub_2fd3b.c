/* ROM6 0x2FE8 SUB_2FD3B -- 58w (span 2FE8-3021, two entries).
 * Verified encoding: src/rom6/boot/2fe8_sub_2fd3b.asm (recombine MATCH).
 * ORIGIN 0x2FE8
 * EXPECT: 68F8 2549 FDFF F130 0001 F84C 2FF2 68F8 2512 FDFF 7714 254B E745 F130 0001 F84C 2FFB 7715 2514 771A 0003 F072 3001 11D2 8194 8195 7714 0000 61F8 0013 0001 F820 300B 7714 0001 7314 056D F030 0001 F844 301E 74F8 0008 0038 F040 0010 6C84 301A F030 FFEF F495 75F8 0008 0038 F074 2E2F F073 2E64 4811 80F8 2649 FE00 80F8 2648
 *
 * Intent: Boot copy-and-poll tail (called by SUB_2FD3A with A = the
 * ldu-loaded byte >>= 8 and AR2 = the advanced cursor; also a TRACE
 * entry, so other callers possible -- A/AR2 stay explicit params).
 * Shared static tail_2FFB per the 5362 sled precedent (one file, N
 * entry functions, one EXPECT); the 2FD3A caller already declares
 * the frag_2FF2 mid-entry per the 5371 precedent. Head entry
 * sub_2FD3B: cell 0x2549 &= ~512 (andm #-513); B = A & 1 (and
 * #1,a,b, full-width per the 2baa precedent); nonzero skips the
 * second clear (bc 0x2ff2,bneq), else cell 0x2512 &= ~512; falls
 * into the 2FF2 midhead. Mid entry frag_2FF2: AR4 = 0x254B (stm),
 * AR5 = AR4 (mvmm); B = A & 1; nonzero keeps AR5 = AR4 (bc
 * 0x2ffb,bneq), else AR5 = 0x2514; falls into tail_2FFB. Shared
 * tail: 4-copy fanout (rptb 0x3001, BRC = 3, RSA/REA inclusive per
 * repeat_block: B = *AR2++ sign-extended (ld, 71a3/28a5 precedent;
 * BK circular wrap flagged, linear ++ in C), MEM[AR4++] =
 * MEM[AR5++] = B-low each pass); AR4 = 0 (stm); cell 0x13 bit 0
 * set remakes AR4 = 1 (bitf plus bc ntc, 5d38 polarity);
 * MEM[0x56D] = AR4 (mvmd); A &= 1 (and #1,a, full-width);
 * nonzero skips the port dance (bc 0x301e,aneq, A == 1 into the
 * call). Else the dance: A = port 56 (portr pa56,*(0x8), AL-alias
 * cell write per the 2867 precedent); A |= 16 (or); banz
 * 0x301a,*ar4 tests-then-decrements AR4 (3306/4ee0 precedent:
 * taken iff nonzero) over the A &= ~16 clear (and #-17,a), so the
 * surviving A bit 4 mirrors the pre-decrement AR4; nop settle;
 * port 56 = A (portw). Both lanes: call dispatcher_entry_2E2F
 * (void: the computed A in {0,1,16} passes as hardware residue,
 * flagged), then tail-call dispatch_match_loop (b 0x2e64) with B
 * = the 4th copied word low (stlm exact), AR2 = the +4 cursor,
 * and an AR4 slot init from the hardware AR4 value (write-only
 * *ppar4 in the callee, never read). A-out void (dies in the
 * calls); B/AR2/TC outs via the tail call.
 */
extern int port_read_56(void);                                        /* HW port 56 (HPI/pa56 poll per 2baa span); no ROM definition */
extern void port_write_56(int v);                                     /* HW port 56 (HPI/pa56 per 2baa span); no ROM definition */
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(int b_live, int *par2, int **ppar4);

static void tail_2FFB(long a, long b, int *ar2, int *ar4, int *ar5)
{
    int i;
    int ar4v;
    int *ar4slot;
    for (i = 0; i <= 3; i++) {                       /* rptb 0x3001, BRC = 3 */
        b = (long)*ar2++;                            /* ld *ar2+%,b (BK wrap flagged) */
        *ar4++ = (int)(b & 0xFFFF);                  /* stl b,*ar4+ */
        *ar5++ = (int)(b & 0xFFFF);                  /* stl b,*ar5+ */
    }
    ar4v = 0;                                        /* stm #0,ar4 */
    if (*(volatile int *)0x13 & 1)                   /* bitf *(0x13),#1; bc ntc */
        ar4v = 1;                                    /* stm #1,ar4 */
    *(volatile int *)0x56D = ar4v;                   /* mvmd ar4,0x56d */
    a &= 1L;                                         /* and #1,a */
    if (a != 0) {                                    /* bc 0x301e,aneq (A == 1) */
        dispatcher_entry_2E2F();                     /* call 0x2e2f */
        ar4slot = (int *)(long)(ar4v & 0xFFFF);      /* AR4 value (no banz this lane) */
        dispatch_match_loop((int)(b & 0xFFFF), ar2, &ar4slot);
        return;                                      /* b 0x2e64 tail */
    }
    a = (long)port_read_56();                        /* portr pa56,*(0x8) */
    *(volatile int *)0x8 = (int)a;                   /* AL alias write (2867 precedent) */
    a |= 16L;                                        /* or #16,a */
    if (ar4v-- == 0)                                 /* banz 0x301a (test-then-decrement) */
        a &= -17L;                                   /* and #-17,a */
    /* nop (settle) */
    port_write_56((int)a);                           /* portw *(0x8),pa56 */
    dispatcher_entry_2E2F();                         /* call 0x2e2f */
    ar4slot = (int *)(long)(ar4v & 0xFFFF);          /* AR4 post-decrement (wrap exact) */
    dispatch_match_loop((int)(b & 0xFFFF), ar2, &ar4slot);
    /* b 0x2e64 tail */
    /* 3022 dead lane (unreachable past unconditional b; ldm/retd + delays not modeled, 5886 precedent) */
}

void frag_2FF2(long a_in, int *ar2_in)
{
    long b;
    int *ar4 = (int *)0x254B;                        /* stm #9547,ar4 */
    int *ar5 = ar4;                                  /* mvmm ar4,ar5 */
    b = a_in & 1L;                                   /* and #1,a,b */
    if (b == 0)                                      /* bc 0x2ffb,bneq */
        ar5 = (int *)0x2514;                         /* stm #9492,ar5 */
    tail_2FFB(a_in, b, ar2_in, ar4, ar5);            /* fall into 2FFB */
}

void sub_2FD3B(long a_in, int *ar2_in)
{
    long a = a_in;
    long b;
    *(volatile int *)0x2549 &= ~512;                 /* andm #-513,*(0x2549) */
    b = a & 1L;                                      /* and #1,a,b */
    if (b == 0)                                      /* bc 0x2ff2,bneq */
        *(volatile int *)0x2512 &= ~512;             /* andm #-513,*(0x2512) */
    frag_2FF2(a, ar2_in);                            /* fall into 2FF2 */
}
