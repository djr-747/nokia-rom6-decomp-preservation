/* ROM6 0xA91C ROUTINE_A91C -- 56w status-fork + block-fill + status-store.
 * Verified encoding: src/rom6/kernel/a91c_routine_a91c.asm (recombine MATCH).
 * ORIGIN 0xA91C
 * EXPECT: F074 0686 61F8 263A 0200 FC30 10F8 0B67 FC44 61F8 051C 0003 F830 A93B E803 F274 D0BE 80F8 0ECC 61F8 0A5A 0001 7712 051E 6982 0100 FF20 6882 FEFF F073 A946 69F8 051E 0100 69F8 0A5A 0001 7714 0ED6 EC38 7094 2799 F074 D29E F274 872B 7714 2579 1AF8 257E 80F8 257E 76F8 25A0 00C1 FC00
 *
 * Intent: Entry via 2x far-backward conditional-call (cc @B13A/B165,
 * AE/B0-arm zone) with no live regs (void). Runs dark SUB_0686
 * (low-zone mini-kernel, no symbol, opaque). TC = (cell 0x263A & 512)
 * != 0 (bitf, TC = (Smem&lk)!=0 per op_bitf_smem_lk); rc tc clears
 * carry when set. A = cell 0xB67 (sign-extended); rc aneq clears carry
 * when nonzero. Carry is modeled 0-in (dark, 7e88 precedent) and never
 * read in-span (callee-observed at most, flagged). TC = (cell 0x51C & 3)
 * != 0; bc skips the D0BE lane when clear. Fall lane: A = 3, cell 0xECC
 * = 3 (calld delay stl runs before the call), asm-only ROUTINE_D0BE
 * (calld, joins d0be_routine_d0be). TC = (cell 0xA5A & 1) != 0; AR2 =
 * 1310; cell 1310 |= 256 (orm, TC-neutral per the neutral ANDM/ORM/XORM
 * rows, so the bitf TC survives the stm/orm); xc 2,ntc runs the andm
 * (cell 1310 &= -257, clears bit 8) only when TC clear, then joins at
 * A946 either way. Taken lane: cell 0x51E |= 256, cell 0xA5A |= 1, then
 * joins. Tail: AR4 = 3798; rpt #56 broadcasts cell 0x2799 into 57 cells
 * (mvkd dmad=source, k+1 = 57); pooled D29E call (no C entry, effects
 * dark, flagged); AR4 = 9593 (calld delay stm runs before the call);
 * asm-only SUB_872B (calld, joins 872b_sub_872b). A |= cell 0x257E
 * (fall lane A = 3, taken lane A = cell 0xB67); cell 0x257E = A-low;
 * cell 0x25A0 = 193 (st); ret. B never set (dark in/out, noted); BRC =
 * 56 dead after (loop const, noted). TC out = last bitf result. Out
 * cells/A/AR4/AR2/TC/C. EXPECT from the image.
 */
extern void sub_0686(void);    /* dark, no symbol (low-zone) */
extern void routine_D0BE(void); /* asm-only, joins d0be_routine_d0be */
extern void sub_872B(void);     /* asm-only, joins 872b_sub_872b */
/* call 0xd29e: pooled, no C entry (see Pool note in d29e_leaf_d29e.c) */

void routine_A91C(void)
{
    long a;
    int carry = 0;  /* C54x carry in (dark, flagged); never read in-span */
    int tc;
    int *ar2;
    int *ar4;
    int i;

    sub_0686();                                              /* call 0x686 */
    tc = ((*(volatile int *)0x263A & 512) != 0);             /* bitf *(0x263a),#512 */
    if (tc)                                                  /* rc tc */
        carry = 0;
    a = (long)*(volatile int *)0xB67;                        /* ld *(0xb67),a */
    if (a != 0)                                              /* rc aneq */
        carry = 0;
    tc = ((*(volatile int *)0x51C & 3) != 0);                /* bitf *(0x51c),#3 */
    if (!tc) {                                               /* bc 0xa93b,tc not taken */
        a = 3L;                                              /* ld #3,a */
        *(volatile int *)0xECC = (int)(a & 0xFFFFL);         /* calld delay: stl a,*(0xecc) */
        routine_D0BE();                                      /* calld 0xd0be */
        tc = ((*(volatile int *)0xA5A & 1) != 0);            /* bitf *(0xa5a),#1 */
        ar2 = (int *)(long)1310;                             /* stm #1310,ar2 */
        *ar2 |= 256;                                         /* orm #256,*ar2 (TC-neutral) */
        if (!tc)                                             /* xc 2,ntc */
            *ar2 &= -257;                                    /* andm #-257,*ar2 */
    } else {                                                 /* bc 0xa93b,tc taken */
        *(volatile int *)0x51E |= 256;                       /* orm #256,*(0x51e) */
        *(volatile int *)0xA5A |= 1;                         /* orm #1,*(0xa5a) */
    }
    ar4 = (int *)(long)3798;                                 /* stm #3798,ar4 */
    for (i = 0; i < 57; i++)                                 /* rpt #56: mvkd x57 */
        *ar4++ = *(volatile int *)0x2799;                    /* mvkd 0x2799,*ar4+ */
    /* call 0xd29e (pooled; effects dark, flagged) */
    ar4 = (int *)(long)9593;                                 /* calld delay: stm #9593,ar4 */
    sub_872B();                                              /* calld 0x872b */
    a |= (long)*(volatile int *)0x257E;                      /* or *(0x257e),a */
    *(volatile int *)0x257E = (int)(a & 0xFFFFL);            /* stl a,*(0x257e) */
    *(volatile int *)0x25A0 = 193;                           /* st #193,*(0x25a0) */
    (void)carry;
}
