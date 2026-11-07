/* ROM6 0x3306 SUB_3306 -- 54w.
 * Verified encoding: src/rom6/kernel/3306_sub_3306.asm (recombine MATCH).
 * ORIGIN 0x3306
 * EXPECT: 7715 2627 6985 0010 7714 2639 6182 8000 6884 FFFE FF30 6984 0001 61F8 3EC8 0010 F820 333C 6182 4000 68F8 263A E3FF F820 3322 69F8 263A 1800 6FD2 0C58 F030 003F 80F8 2655 7714 03B5 76F8 0588 0000 7713 001F 10DA F110 FFFF F84D 3338 6BF8 0588 0001 8094 6C8B 332F F073 335C
 *
 * Intent: Bit-gated collect loop with epilogue join. AR5 =
 * 9767, cell |= 16; AR4 = 9785; TC = bit 15 of *AR2 (bitf
 * single-bit mask, both TC senses coincide); cell AR4 &=
 * 0xFFFE (andm, always); xc 2,tc skips cell |= 1 iff TC set
 * (XC-taken-skips per the oracle); TC = bit 4 of cell
 * 0x3EC8; clear tail-calls frag_333C with live AR0/AR2
 * (bc 0x333c,ntc; the callee now has C intent); else TC =
 * bit 14 of *AR2, cell 0x263A &= 0xE3FF, set runs cell |=
 * 6144 (333C prelude shape); A = *AR2 arith>>8 with AR2 +=
 * AR0 (ld *ar2+%,-8,a: binutils decode plus the 333C twin
 * with the identical shift word 0C58 and parallel
 * load-mask-store data flow; the ti-c54x catalog carries
 * no LD_MOD10 row yet -- catalog gap flagged, semantics
 * from the LD-shift leaf plus the 351d +0% step, SXM = 1
 * flagged); A &= 63 (upper cleared); cell 0x2655 = A-low;
 * AR4 = 949; cell 0x588 = 0; AR3 = 31. Collect loop (latch
 * at 3338): A = *(AR2) with AR2 += AR0 (ld *ar2+0%,a, same
 * +0% step convention, circular wrap needs caller-live BK,
 * linear modeled flagged); B = A + 1 (sub #-1); B nonzero
 * runs cell 0x588++ (addm) and cell AR4 = A-low with AR4++;
 * the banz latch ALWAYS decrements AR3 and takes iff the
 * pre-decrement value is nonzero (oracle branch-Sind
 * helper plus CPU RED tests: taken = value != 0,
 * value_after = value - 1, side effect applied on the
 * not-taken path too), so the body runs up to 32 passes;
 * B == 0 rejoins the latch (bc 0x3338,beq skips addm/stl
 * but still decrements). Exit tail-joins the 333C epilogue
 * at 335C (call 0x2e2f then b 0x2e64 -- the same two words
 * the frag_333C model ends with), modeled with the same
 * two grounded externs. ARs/A/B dead at exit (flagged).
 * Bound 3306-333B.
 */
extern void frag_333C(int ar0_live, int *ar2_in);
extern void sub_2E2F(void);
extern void frag_2E64(void);

void sub_3306(int ar0_live, int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar4;
    int ar3;
    long a;
    long b;
    int taken;
    *(volatile int *)9767 |= 16;                     /* orm #16,*ar5 */
    ar4 = (int *)9785;                               /* stm #9785,ar4 */
    taken = (*ar2 & -32768) != 0;                    /* bitf *ar2,#-32768 */
    *ar4 &= 65534;                                   /* andm #-2,*ar4 */
    if (!taken)                                      /* xc 2,tc */
        *ar4 |= 1;                                   /* orm #1,*ar4 */
    if ((*(volatile int *)0x3EC8 & 16) == 0) {       /* bitf; bc ntc */
        frag_333C(ar0_live, ar2);
        return;
    }
    {                                                /* 333C prelude shape */
        int tc = (*ar2 & 16384) != 0;
        *(volatile int *)0x263A &= 58367;            /* andm #-7169 */
        if (tc)                                      /* bc 0x3322,ntc */
            *(volatile int *)0x263A |= 6144;         /* orm #6144 */
    }
    a = (long)*ar2 >> 8;                             /* ld *ar2+%,-8,a (gap flagged) */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    a &= 63;                                         /* and #63,a */
    *(volatile int *)0x2655 = (int)(a & 0xFFFF);     /* stl a,*(0x2655) */
    ar4 = (int *)949;                                /* stm #949,ar4 */
    *(volatile int *)0x588 = 0;                      /* st #0,*(0x588) */
    ar3 = 31;                                        /* stm #31,ar3 */
    for (;;) {                                       /* 332F body, latch 3338 */
        a = (long)*ar2;                              /* ld *ar2+0%,a */
        ar2 += ar0_live;                             /* +0% (wrap flagged) */
        b = a + 1;                                   /* sub #-1,a,b */
        if (b != 0) {                                /* bc 0x3338,beq */
            (*(volatile int *)0x588)++;              /* addm #1 */
            *ar4++ = (int)(a & 0xFFFF);              /* stl a,*ar4+ */
        }
        taken = (ar3 != 0);                          /* banz (always decrements) */
        ar3--;
        if (!taken)
            break;
    }
    sub_2E2F();                                      /* 335C epilogue join */
    frag_2E64();                                      /* b 0x2e64 (tail) */
}
