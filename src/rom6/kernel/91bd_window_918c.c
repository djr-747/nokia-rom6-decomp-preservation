/* ROM6 0x91BD WINDOW_918C -- 53w (span 91BD-91F1, two entries).
 * Verified encoding: src/rom6/kernel/91be_window_918c.asm (recombine MATCH).
 * ORIGIN 0x91BD
 * EXPECT: FC00 F074 0594 E864 EC03 7308 3032 7716 0080 7717 2FA4 771A 002A F072 91CE 6F97 0C5A 8096 7717 300B 771A 002A F072 91D7 6F97 0C5A 8096 F074 918C 7717 0080 771A 0055 F074 9004 7717 0084 7713 0080 771A 0026 F072 91E9 1197 8193 6DEF 0004 771A 0026 F072 91F1 1197 8193
 *
 * Intent: Mesh driver E2 (0x80 AR6 variant; the 0x160 variant
 * lives in the 91F2 span). Leading ret word (word 0: the 918C
 * span's fall-through return abut, no entry function -- the
 * 9146/918B-ret precedent). Entry frag_91BE: AR3 live (the
 * window cursor passed through to window_918C, then reseated);
 * entry A/B unread (A recomputed by ld #100, B recomputed in
 * the loops); void. Runs dark helper_0594 (call, 44b2
 * precedent); A = 100 (ld); 4 identical stores of A-low to
 * cell 0x3032 (rpt #3 plus mvmd al, 2a5f shapes). AR6 = 128,
 * AR7 = 12196 (stm locals). BRC = 42; rptb block [91CC,91CE],
 * 43 passes (2-word ld with shift word 0C5A plus stl): A =
 * *AR7++ arithmetically shifted right 6 (SXM dark, flagged);
 * *AR6++ = A-low. AR7 = 12299; BRC = 42; second rptb block
 * [91D5,91D7], 43 passes, same shape. Calls window_918C with
 * the entry AR3 (call 0x918c; the cursor has not been reseated
 * yet -- threading order exact). AR7 = 128; BRC = 85; runs
 * dark SUB_9004 (call, forward extern void). AR7 = 132,
 * AR3 = 128 (stm reseat); BRC = 38; rptb block [91E6,91E9],
 * 39 passes (REA lands on the stl; the mar runs once after):
 * B = *AR7++ (ld); *AR3++ = B-low (stl). mar AR7 += 4 once.
 * BRC = 38; rptb block [91EE,91F1], 39 passes, same ld/stl
 * shape; return (the 91F2 span owns the ret word, executed as
 * this path's return -- abut, 9146 precedent). A/B/ARs dead
 * after (void); outs via DARAM, cells 0x3032/0x60-family
 * writes inside window_918C, dark calls.
 */
extern void helper_0594(void);                           /* call 0x594 (dark) */
extern void window_918C(int *ar3);                       /* C-bound mesh entry */
extern void sub_9004(void);                              /* dark, no symbol */

void ret_91BD(void)
{
    /* ret (918C-span fall-through abut, no state) */
}

void frag_91BE(int *ar3_in)
{
    long a;
    long b;
    int *ar3 = ar3_in;
    int *ar6;
    int *ar7;
    int brc;
    int i;
    helper_0594();                                       /* call 0x594 */
    a = 100;                                             /* ld #100,a */
    for (i = 0; i < 4; i++)                              /* rpt #3; mvmd */
        *(volatile int *)0x3032 = (int)(a & 0xFFFFL);    /* mvmd al,0x3032 */
    ar6 = (int *)128;                                    /* stm #128,ar6 */
    ar7 = (int *)12196;                                  /* stm #12196,ar7 */
    brc = 42;                                            /* stm #42,brc */
    for (i = 0; i <= brc; i++) {                         /* rptb 0x91ce */
        a = (long)*ar7++ >> 6;                           /* ld *ar7+,-6,a (arith, flagged) */
        *ar6++ = (int)(a & 0xFFFFL);                     /* stl a,*ar6+ */
    }
    ar7 = (int *)12299;                                  /* stm #12299,ar7 */
    brc = 42;                                            /* stm #42,brc */
    for (i = 0; i <= brc; i++) {                         /* rptb 0x91d7 */
        a = (long)*ar7++ >> 6;                           /* ld *ar7+,-6,a */
        *ar6++ = (int)(a & 0xFFFFL);                     /* stl a,*ar6+ */
    }
    window_918C(ar3);                                    /* call 0x918c (entry AR3) */
    ar7 = (int *)128;                                    /* stm #128,ar7 */
    brc = 85;                                            /* stm #85,brc (dark 9004 may read, flagged) */
    sub_9004();                                          /* call 0x9004 (dark) */
    ar7 = (int *)132;                                    /* stm #132,ar7 */
    ar3 = (int *)128;                                    /* stm #128,ar3 */
    brc = 38;                                            /* stm #38,brc */
    for (i = 0; i <= brc; i++) {                         /* rptb 0x91e9 */
        b = (long)*ar7++;                                /* ld *ar7+,b */
        *ar3++ = (int)(b & 0xFFFFL);                     /* stl b,*ar3+ */
    }
    ar7 += 4;                                            /* mar *+ar7(0x4) (post-loop) */
    brc = 38;                                            /* stm #38,brc */
    for (i = 0; i <= brc; i++) {                         /* rptb 0x91f1 */
        b = (long)*ar7++;                                /* ld *ar7+,b */
        *ar3++ = (int)(b & 0xFFFFL);                     /* stl b,*ar3+ */
    }
    /* ret (91F2 span owns the word, abut) */
}
