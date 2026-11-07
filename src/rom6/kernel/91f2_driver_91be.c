/* ROM6 0x91F2 DRIVER_91BE -- 37w (span 91F2-9216, two entries; overlap-trimmed wave-12).
 * Verified encoding: src/rom6/kernel/91f2_driver_91be.asm (recombine MATCH).
 * Wave-12: exit ret @9216 owned here; ret_9216 wrapper deleted.
 * ORIGIN 0x91F2
 * EXPECT: FC00 F074 0594 E864 EC03 7308 3032 7716 0160 7717 2FA4 771A 0091 F072 9203 6F97 0C5A 8096 F074 918C 7717 0160 771A 0091 F074 9004 7717 0164 7713 0160 771A 008D F072 9215 1197 8193 FC00
 *
 * Intent: Mesh driver E3 (0x160 AR6 variant; the 0x80 variant
 * lives in the 91BD span; the CALA-called 9233 family lives
 * past 9217). Leading ret word (word 0: the 91BE span's
 * fall-through return abut, no entry function -- the
 * 9146/918B-ret precedent). Entry frag_91F3: AR3 live (the
 * window cursor passed through to window_918C, then reseated);
 * entry A/B unread (both recomputed); void. Same skeleton as
 * frag_91BE with variant constants: dark helper_0594; A =
 * 100; 4 stores of A-low to cell 0x3032 (rpt #3 plus mvmd al);
 * AR6 = 352, AR7 = 12196; BRC = 145; rptb block [9200,9202],
 * 146 passes: A = *AR7++ arithmetically >> 6 (SXM dark,
 * flagged), *AR6++ = A-low; calls window_918C with the entry
 * AR3 (threading order exact); AR7 = 352; BRC = 145; runs
 * dark SUB_9004 (BRC value may be read by the callee,
 * flagged); AR7 = 356, AR3 = 352; BRC = 141; rptb block
 * [9212,9215], 142 passes: B = *AR7++; *AR3++ = B-low;
 * return (in-span ret@9216, owned here). The former E4-head
 * tail (9217-9226) was trimmed to the 9217 span (exact
 * duplicate) -- one owner per word. A/B/ARs dead after
 * (void); outs via DARAM, cell 0x3032, calls.
 */
extern void helper_0594(void);                           /* call 0x594 (dark) */
extern void window_918C(int *ar3);                       /* C-bound mesh entry */
extern void sub_9004(void);                              /* dark, no symbol */

void ret_91F2(void)
{
    /* ret (91BE-span fall-through abut, no state) */
}

void frag_91F3(int *ar3_in)
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
    ar6 = (int *)352;                                    /* stm #352,ar6 */
    ar7 = (int *)12196;                                  /* stm #12196,ar7 */
    brc = 145;                                           /* stm #145,brc */
    for (i = 0; i <= brc; i++) {                         /* rptb 0x9203 */
        a = (long)*ar7++ >> 6;                           /* ld *ar7+,-6,a (arith, flagged) */
        *ar6++ = (int)(a & 0xFFFFL);                     /* stl a,*ar6+ */
    }
    window_918C(ar3);                                    /* call 0x918c (entry AR3) */
    ar7 = (int *)352;                                    /* stm #352,ar7 */
    brc = 145;                                           /* stm #145,brc (dark 9004 may read) */
    sub_9004();                                          /* call 0x9004 (dark) */
    ar7 = (int *)356;                                    /* stm #356,ar7 */
    ar3 = (int *)352;                                    /* stm #352,ar3 */
    brc = 141;                                           /* stm #141,brc */
    for (i = 0; i <= brc; i++) {                         /* rptb 0x9215 */
        b = (long)*ar7++;                                /* ld *ar7+,b */
        *ar3++ = (int)(b & 0xFFFFL);                     /* stl b,*ar3+ */
    }
    /* ret (in-span ret@9216) */
}
