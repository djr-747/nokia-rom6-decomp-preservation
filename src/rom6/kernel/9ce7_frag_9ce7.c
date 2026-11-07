/* ROM6 0x9CE7 FRAG_9CE7 -- 36w polled copy/fill + strobe pulse.
 * Verified encoding: src/rom6/kernel/9ce7_frag_9ce7.asm (recombine MATCH).
 * ORIGIN 0x9CE7
 * EXPECT: F074 06C8 61F8 085D 0020 F820 9D0B 7712 29C9 7713 0926 47F8 000B E589 61F8 0861 0001 7712 086F 7682 0001 FF30 69F8 0861 0002 69F8 0861 0001 69F8 0029 0008 68F8 0029 FFF7 F073 9D15
 *
 * Intent: Runs sub_06C8; unless bit 5 of cell 0x85D is set
 * (bitf, bc 0x9D0B ntc -- tail span owns) copies *(0xB)+1
 * words from 0x29C9 up to 0x926 (rpt *(0xb), mvdd *ar2+,*ar3+,
 * second operand is the destination per 25F2 precedent),
 * sets flag cell *(0x86F) = 1, then pulses strobe bit 3 of
 * *(0x29) (orm #8 then andm #-9). The xc 2,tc over the first
 * orm is a 2-word skip of a 3-word orm: it skips the orm
 * opcode + Smem words and lands on the lk word 0x0002, which
 * executes as ADD *(0x02),a (direct, A += cell<<16 -- ADD
 * Smem always shifts left 16, no SXM dependence) and resyncs
 * at the next orm opcode, so the TC-set path skips only the
 * bit-1 set (orm #2) while still setting bit 0 (orm #1) and
 * pulsing the strobe. A is live-through (caller-evidenced,
 * flagged); TC = bit 0 of *(0x861) (BITF any-bit, oracle
 * op_bitf_smem_lk); DP dark (direct cells absolute, flagged).
 * In *(0xB)/AR2/AR3/entry A (dark); out cells/flags/A.
 */
void frag_9CE7(void)
{
    long a;  /* live-in (dark, flagged); live-through, TC path adds */
    int *ar2;
    int *ar3;
    int n;
    int i;
    int tc;

    sub_06C8();                                              /* call 0x6c8 */
    if ((*(volatile int *)0x85D & 32) == 0) {                /* bitf *(0x85d),#32; bc 0x9d0b,ntc */
        /* bc 0x9d0b,ntc (tail span owns) */
        return;
    }
    ar2 = (int *)10697;                                      /* stm #10697,ar2 */
    ar3 = (int *)2342;                                       /* stm #2342,ar3 */
    n = *(volatile int *)0xB;                                 /* rpt *(0xb): runs n+1 */
    for (i = 0; i < n + 1; i++)                              /* mvdd *ar2+,*ar3+ */
        *ar3++ = *ar2++;
    tc = (*(volatile int *)0x861 & 1) != 0;                  /* bitf *(0x861),#1 */
    ar2 = (int *)2159;                                       /* stm #2159,ar2 */
    *ar2 = 1;                                                /* st #1,*ar2 */
    if (!tc)                                                 /* xc 2,tc falls through */
        *(volatile int *)0x861 |= 2;                         /* orm #2,*(0x861) */
    else                                                     /* xc skips op+Smem, lands on lk */
        a += (long)(*(volatile int *)0x2 & 0xFFFF) << 16;    /* 0x0002 runs as add *(0x2),a; resyncs */
    *(volatile int *)0x861 |= 1;                             /* orm #1,*(0x861) */
    *(volatile int *)0x29 |= 8;                              /* orm #8: strobe assert */
    *(volatile int *)0x29 &= -9;                              /* andm #-9: strobe deassert */
    /* b 0x9d15 (next span owns) */
}
