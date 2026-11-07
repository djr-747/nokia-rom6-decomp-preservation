/* ROM6 0x7E88 SUB31_7E88 -- 30w circular bit-rotate loop.
 * Verified encoding: src/rom6/kernel/7e88_sub31_7e88.asm (recombine MATCH).
 * ORIGIN 0x7E88
 * EXPECT: F074 059E 7719 0002 7714 0060 7715 0061 771A 0007 F274 7EA7 7710 0003 1183 F072 7E9C 4485 F491 82D5 F591 818B 1183 6E88 7E97 771A 0007 6C89 7E92 6D93
 *
 * Intent: Nested bit-rotate/permutation loop over a BK = 2
 * circular buffer at AR5 (96/97 pair) with a downward AR3
 * stream. Entry call 0x59E (RAM: zero in mask dump); BK = 2,
 * AR4/AR5 = 96/97, BRC = 7. Outer loop (AR1 caller-preset,
 * dark -- trip count dark, flagged): deferred call 0x7EA7
 * (in-image bit-merge, C entry bit_merge_7EA7) with AR0 = 3
 * in the 2 delay words; B = *AR3 loads at the return
 * address. Middle loop (AR0, 3 passes): RPTB block
 * 7E99-7E9C x8 {A = *AR5 << 16, A = ROL-through-carry,
 * *AR5+% = MSW (circular, BK dark, flagged), B =
 * ROL-through-carry (shared carry with A, initial carry
 * dark, flagged)}; *AR3-- = BL; B = *AR3; AR0-- with BRC =
 * 7 re-armed in the BANZD delay slots; loop back to RPTB.
 * Outer BANZ (immediate, no delay slots) back to the CALLD
 * while AR1 != 0; fall-through runs mar *AR3+ and returns
 * through the abutting 7EA6 ret. Interleaver/permute shape.
 * (Wave-13: RPTB block = 4 words through REA 7E9C;
 * stl/ld/banzd/banz sit outside it; BANZ/BCC/B are
 * immediate -- no delay slots -- per the D-suffix rule;
 * CALLD order = delays, call, return-address load.)
 */
extern void sub_059E(void); /* low-region: zero in mask dump; see docs/evidence/extern-triage.md */
extern void bit_merge_7EA7(int **ppar2, int **ppar4);

void sub31_7E88(void)
{
    long a;
    long b;
    int *ar0;
    int *ar1;  /* outer counter, caller-preset (dark, flagged) */
    int *ar2;  /* dark handoff to bit_merge (flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;  /* dark handoff to bit_merge (flagged) */
    int *ar5;
    int carry = 0;  /* C54x carry in (dark, flagged) */
    int i;

    sub_059E();                                                /* call 0x59e (RAM) */
    /* stm #2,bk (BK = 2, circular modulus) */
    ar4 = (int *)96;                                           /* stm #96,ar4 */
    ar5 = (int *)97;                                           /* stm #97,ar5 */
    /* stm #7,brc */
    do {                                                       /* outer (AR1 dark) */
        ar0 = (int *)3;                                        /* calld delay: stm #3,ar0 */
        bit_merge_7EA7(&ar2, &ar4);                            /* calld 0x7ea7 */
        b = (long)*ar3;                                        /* return address: ld *ar3,b */
        do {                                                   /* middle (AR0: 3 passes) */
            for (i = 0; i < 8; i++) {                          /* rptbd 0x7e9c */
                a = (long)*ar5 << 16;                          /* ld *ar5,16,a */
                { int nc = (int)((a >> 31) & 1L); a = (a << 1) | carry; carry = nc; } /* rol a (through carry) */
                *ar5++ = (int)((a >> 16) & 0xFFFFL);           /* sth a,*ar5+% (circular, flagged) */
                { int nc = (int)((b >> 31) & 1L); b = (b << 1) | carry; carry = nc; } /* rol b (shared carry) */
            }
            *ar3-- = (int)(b & 0xFFFFL);                       /* stl b,*ar3- */
            b = (long)*ar3;                                    /* ld *ar3,b */
            ar0--;                                             /* banzd delays: AR0-- */
            /* stm #7,brc (re-arms RPTB) */
        } while (ar0 != (int *)0);                             /* banzd 0x7e97 (sole delay: stm #7,brc) */
        ar1--;                                                 /* banz 0x7e92,*ar1- (immediate) */
    } while (ar1 != (int *)0);
    ar3++;                                                     /* mar *ar3+ */
    /* ret @7EA6 (abutting 7EA6 span owns the word) */
    (void)a; (void)b;
}
