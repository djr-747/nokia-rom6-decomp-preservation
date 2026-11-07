/* ROM6 0x7FC6 SUB46_7FC6 -- 22w.
 * Verified encoding: src/rom6/kernel/7fc6_sub46_7fc6.asm (recombine MATCH).
 * ORIGIN 0x7FC6
 * EXPECT: F074 059E 6DEA 0007 771A 0003 F072 7FD1 458A 1B92 F762 838A 1182 F330 FE00 F762 1082 F030 01FF FE00 F1A0 8182
 *
 * Intent: Neighbor-merge filter with delayed return. Runs 0x59E (dark, forward extern); AR2 = live-in + 7 (mar); 4 iterations (BRC = 3, rptb): B = *AR2-- << 16 OR *AR2++ (SXM-on-entry unknown, plain OR per 5e7d), B <<= 2 arithmetic, high word back to *AR2-- (STH per op_sth). Then B = *AR2 AND -512 (keeps all but low 9) <<= 2; A = *AR2 AND 511; retd delay slots always run (B |= A; store B-low); return. AR2 threaded from callers (83b4/83ce pass their live pointer). Bound 7FC6-7FDB.
 */
extern void sub_059E(void);

void sub_7FC6(int *par2)
{
    long b;
    int a;
    int i;
    int *ar2 = par2 + 7;                       /* mar *+ar2(0x7) */
    sub_059E();                                  /* call 0x59e */
    for (i = 0; i < 4; i++) {                    /* stm #3,brc; rptb */
        b = (long)(*ar2--) << 16;               /* ld *ar2-,16,b */
        b |= (unsigned short)*ar2++;              /* or *ar2+,b (Smem zero-ext) */
        b <<= 2;                                 /* sfta b,2 */
        *ar2-- = (int)((b >> 16) & 0xFFFF);     /* sth b,*ar2- */
    }
    b = *ar2;                                    /* ld *ar2,b */
    b &= -512;                                   /* and #-512,b */
    b <<= 2;                                     /* sfta b,2 */
    a = *ar2;                                    /* ld *ar2,a */
    a &= 511;                                    /* and #511,a */
    b |= a;                                      /* retd delay: or a,b */
    *ar2 = (int)b;                               /* stl b,*ar2 */
    /* retd */
}
