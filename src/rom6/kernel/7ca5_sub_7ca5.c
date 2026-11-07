/* ROM6 0x7CA5 SUB_7CA5 -- 17w.
 * Verified encoding: src/rom6/kernel/7ca5_sub_7ca5.asm (recombine MATCH).
 * ORIGIN 0x7CA5
 * EXPECT: F074 059E 7713 2A87 1084 F010 0004 F120 0200 FF46 F120 0400 1B83 8183 FE00 6B84 FFFF
 *
 * Intent: Conditional cell set with countdown. Runs SUB_059E (returns
 * int, discarded); AR3 = 10887; A = *AR4 - 4; B = 512, A > 0 makes
 * B = 1024 ORed with the cell (xc 2,agt covers the 2-word LD+OR only,
 * per ti-c54x op_xc; both paths rejoin); cell = B-low; the retd delay
 * decrements *AR4 (addm, always runs); return. XC audited against the
 * 3115-class miscount (both paths hit the store, exact). Bound
 * 7CA5-7CB5.
 */
extern int sub_059E(void);

void sub_7CA5(int *par4)
{
    int *ar3;
    long a;
    long b;
    (void)sub_059E();                                /* call 0x59e */
    ar3 = (int *)10887;                              /* stm #10887,ar3 */
    a = (long)*par4;                                 /* ld *ar4,a */
    a -= 4;                                          /* sub #4,a */
    b = 512;                                         /* ld #512,b */
    if (a > 0) {                                     /* xc 2,agt */
        b = 1024;                                    /* ld #1024,b */
        b |= (long)*ar3;                             /* or *ar3,b */
    }
    *ar3 = (int)(b & 0xFFFF);                        /* stl b,*ar3 */
    (*par4)--;                                       /* retd delay: addm (always runs) */
    /* retd */
}
