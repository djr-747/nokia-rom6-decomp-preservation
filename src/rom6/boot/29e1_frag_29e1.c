/* ROM6 0x29E1 FRAG_29E1 -- 33w.
 * Verified encoding: src/rom6/boot/29e1_frag_29e1.asm (recombine MATCH).
 * ORIGIN 0x29E1
 * EXPECT: 6183 0004 F820 2A02 10F8 1278 F030 00E0 FA44 2A02 7683 1000 7713 1276 6983 8000 10F8 1271 00F8 3F11 6FF8 036A 0D20 F495 F495 FD4A F640 80F8 1271 7712 1270 F073 2A8A
 *
 * Intent: Masked select with delayed-branch join. Bit 2 of *AR3-live-in clear tail-enters FRAG_2A02 (bc ntc, C: frag_2A02 with entry AR3). A = cell 0x1278 AND 224, nonzero tail-enters FRAG_2A02 (bcd aneq with delay slots always run: st #4096 through entry AR3, AR3 = 4726). Else sets bit 15 of cell 4726 (orm #-32768); A = cell 0x1271 + cell 0x3F11; B = A - cell 0x36A (sub 3-word direct form, plain per .asm, op_sub); xc 1,bgeq runs ld b,a when B >= 0; A stored to cell 0x1271; AR2 = 4720; tail-enters FRAG_2A73 at 0x2A8A (b: has .asm, no C yet, forward extern). Bound 29E1-2A01.
 */
extern void frag_2A02(int *par3);
extern void frag_2A73(void);

void frag_29E1(int *par3)
{
    int a;
    int b;
    if ((*par3 & 4) == 0) {                          /* bitf, bc ntc */
        frag_2A02(par3);                             /* tail call */
        return;
    }
    a = *(volatile int *)0x1278 & 224;          /* ld; and #224,a */
    /* bcd delay slots (always run): */
    *par3 = 4096;                                   /* st #4096,*ar3 */
    {
        int *ar3 = (int *)4726;                      /* stm #4726,ar3 */
        if (a != 0) {                                /* bcd 0x2a02,aneq */
            frag_2A02(par3);                         /* tail (entry AR3) */
            return;
        }
        *(volatile int *)4726 |= -32768;         /* orm (AR3 = 4726) */
        (void)ar3;
    }
    a = *(volatile int *)0x1271;                /* ld *(0x1271),a */
    a += *(volatile int *)0x3F11;               /* add *(0x3f11),a */
    b = a - *(volatile int *)0x36A;             /* sub *(0x36a),a,b */
    /* nop; nop */
    if (b >= 0)                                      /* xc 1,bgeq */
        a = b;                                       /* ld b,a */
    *(volatile int *)0x1271 = a;                /* stl a,*(0x1271) */
    /* stm #4720,ar2 (dead preset, unused after) */
    frag_2A73();                                     /* b 0x2a8a tail */
}
