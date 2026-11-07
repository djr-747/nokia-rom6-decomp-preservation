/* ROM6 0x8DDB ROUTINE_8DDB -- 42w dual-accumulator FIR kernel.
 * Verified encoding: src/rom6/kernel/8ddb_routine_8ddb.asm (recombine MATCH).
 * ORIGIN 0x8DDB
 * EXPECT: 4493 7710 0001 7719 0010 7712 2F40 EC07 7192 2F48 F272 8E02 7712 2F40 8295 4584 3792 D6AB 4584 3792 D6AB 4584 3792 D6AB 4584 3792 D6AB 4584 3792 D6AB 4584 3792 D6AB 4584 3792 D6AF 4584 37D2 2AD4 C891 8221 FC00
 *
 * Intent: A = *(AR3++)<<16 (AR3 dark); AR0 = 1 (unused, out
 * flagged); BK = 16; AR2 = 12096; 8x *(0x2F48) = *(AR2++)
 * (rpt #7, last wins at *(12103)); AR2 = 12096 (rptbd
 * delay). RPTB block (BRC caller-live dark, flagged; exact
 * BRC+1 incl. wrap): sth A-high to *(AR5++) (ASM dark;
 * AR5 dark); six identical passes B = *(AR4)<<16, T =
 * *(AR2++), B += round(T x A-high) (macar, R bit per
 * catalog; rounding = (sum+0x8000)&~0xFFFF per oracle
 * op_multiply; FRCT doubling dark, flagged), store B-low
 * to *(AR5++) in parallel with A += round(T x *(AR4++))
 * (macr; the pair is sequential words so no T hazard --
 * macr reads the just-loaded T); seventh pass same with
 * the store frozen (+0%, BK circular wrap flagged); tail B
 * = *(AR4)<<16, T = *(AR2) (circular %, wrap flagged),
 * B += round, A += round(T x *(AR4)) (% wrap flagged),
 * tmp = *(AR3), *(AR3) = A-low, A = tmp<<16 (parallel
 * st||ld reads pre-store memory, SXM dark), AR3++;
 * *(0x21) = A-high (sth, ASM dark); return. T/A-high/FRCT/
 * OVM/SXM/ASM/BK/BRC dark as noted. In ARs/cells; out
 * cells/ARs/T.
 * EXPECT from the image.
 */
void routine_8DDB(void)
{
    long a;
    long b;
    int *ar2;
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;  /* live-in (dark, flagged) */
    int *ar5;  /* live-in (dark, flagged) */
    int t;
    long p;
    int tmp;
    int brc;  /* live-in (dark, flagged) */
    int i;
    int j;

    a = (long)*ar3++ << 16;                                  /* ld *ar3+,16,a (SXM dark, flagged) */
    /* stm #1,ar0 (unused, out flagged); stm #16,bk */
    ar2 = (int *)12096;                                      /* stm #12096,ar2 */
    for (j = 0; j < 8; j++)                                  /* rpt #7 (k+1) */
        *(volatile int *)0x2F48 = *ar2++;                    /* mvdk *ar2+,0x2f48 (last wins) */
    /* rptbd 0x8e02: stm #12096,ar2 delay runs once */
    ar2 = (int *)12096;
    for (i = 0; i <= (unsigned)brc; i++) {                   /* (BRC+1 incl. wrap; BRC dark) */
        *ar5++ = (int)((a >> 16) & 0xFFFFL);                 /* sth a,*ar5+ (ASM dark, flagged) */
        b = (long)*ar4 << 16;                                /* pass 1: ld *ar4,16,b (SXM dark) */
        t = *ar2++;                                          /* macar: T = *(AR2++) */
        p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);   /* (FRCT doubling dark, flagged) */
        b = (b + p + 0x8000L) & ~0xFFFFL;                    /* (MACAR rounding, oracle) */
        *ar5++ = (int)(b & 0xFFFFL);                         /* st b,*ar5+ (parallel) */
        p = (long)t * (long)*ar4++;                          /* macr *ar4+,a */
        a = (a + p + 0x8000L) & ~0xFFFFL;                    /* (rounding) */
        b = (long)*ar4 << 16;                                /* pass 2 */
        t = *ar2++;
        p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);
        b = (b + p + 0x8000L) & ~0xFFFFL;
        *ar5++ = (int)(b & 0xFFFFL);
        p = (long)t * (long)*ar4++;
        a = (a + p + 0x8000L) & ~0xFFFFL;
        b = (long)*ar4 << 16;                                /* pass 3 */
        t = *ar2++;
        p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);
        b = (b + p + 0x8000L) & ~0xFFFFL;
        *ar5++ = (int)(b & 0xFFFFL);
        p = (long)t * (long)*ar4++;
        a = (a + p + 0x8000L) & ~0xFFFFL;
        b = (long)*ar4 << 16;                                /* pass 4 */
        t = *ar2++;
        p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);
        b = (b + p + 0x8000L) & ~0xFFFFL;
        *ar5++ = (int)(b & 0xFFFFL);
        p = (long)t * (long)*ar4++;
        a = (a + p + 0x8000L) & ~0xFFFFL;
        b = (long)*ar4 << 16;                                /* pass 5 */
        t = *ar2++;
        p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);
        b = (b + p + 0x8000L) & ~0xFFFFL;
        *ar5++ = (int)(b & 0xFFFFL);
        p = (long)t * (long)*ar4++;
        a = (a + p + 0x8000L) & ~0xFFFFL;
        b = (long)*ar4 << 16;                                /* pass 6 */
        t = *ar2++;
        p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);
        b = (b + p + 0x8000L) & ~0xFFFFL;
        *ar5++ = (int)(b & 0xFFFFL);
        p = (long)t * (long)*ar4++;
        a = (a + p + 0x8000L) & ~0xFFFFL;
        b = (long)*ar4 << 16;                                /* pass 7 (frozen store) */
        t = *ar2++;
        p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);
        b = (b + p + 0x8000L) & ~0xFFFFL;
        *ar5 = (int)(b & 0xFFFFL);                           /* st b,*ar5+0% (BK wrap flagged) */
        p = (long)t * (long)*ar4++;
        a = (a + p + 0x8000L) & ~0xFFFFL;
        b = (long)*ar4 << 16;                                /* tail: ld *ar4,16,b */
        t = *ar2++;                                          /* macar *ar2+%,b (BK wrap flagged) */
        p = (long)t * (long)(short)((a >> 16) & 0xFFFFL);
        b = (b + p + 0x8000L) & ~0xFFFFL;
        p = (long)t * (long)*ar4++;                          /* macr *ar4+%,a (BK wrap flagged) */
        a = (a + p + 0x8000L) & ~0xFFFFL;
        tmp = *ar3;                                          /* st a,*ar3 || ld *ar3+,a */
        *ar3 = (int)(a & 0xFFFFL);                           /* (store uses issue-time A/AR3) */
        a = (long)tmp << 16;                                 /* (load reads pre-store; SXM dark) */
        ar3++;
        *(volatile int *)0x21 = (int)((a >> 16) & 0xFFFFL);  /* sth a,0x21 (ASM dark) */
    }
    /* ret */
}
