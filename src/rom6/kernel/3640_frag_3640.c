/* ROM6 0x3640 FRAG_3640 -- 34w AR0 class select on *AR3 bits.
 * Verified encoding: src/rom6/kernel/3640_frag_3640.asm (recombine MATCH).
 * ORIGIN 0x3640
 * EXPECT: F030 0008 7710 2540 FF44 7710 2577 6183 0004 F820 3667 6183 0008 F820 3652 69F8 054F 0010 F030 0008 7710 253F FF44 7710 2576 1184 6183 0002 F830 3662 F330 FEFF F073 3664
 *
 * Intent: A = A-live-in & 8 (Z from the and). AR0 = A-nonzero ? 9591 : 9536
 * (xc 2,aneq over the stm pair). Bit 2 of *AR3-entry clear tail-enters dark
 * FRAG_3667 (bc ntc, forward extern); bit 3 clear tail-enters FRAG_3652 (bc
 * ntc, has .asm, forward extern; numerically inside the 3640-3661 bound but
 * a separate span). Else cell 0x54F |= 16 (orm); A &= 8 again (same value);
 * AR0 = A-nonzero ? 9590 : 9535 (xc pair). B = *AR4-entry; bit 1 of *AR3
 * set skips the mask (bc tc to the tail branch); else B &= -257 (0xFEFF).
 * Tail-enters dark 0x3664 (b, forward extern, void per 283D precedent; B
 * rides dead-or-live, noted). A, AR3, AR4 entry-live; AR0 the only live-out.
 * Bound 3640-3661 (exit F073->3664 + operand; 34w).
 */
extern void frag_3667(void); /* joins 3662_frag_3662 interior @+0x5; see docs/evidence/extern-triage.md */
extern void frag_3652(void); /* joins 3640_frag_3640 interior @+0x12; see docs/evidence/extern-triage.md */
extern void frag_3664(void); /* joins 3662_frag_3662 interior @+0x2; see docs/evidence/extern-triage.md */

void frag_3640(int a_live, int *par3, int *par4, int *par0_out)
{
    long a = (long)a_live & 8L;                /* and #8,a */

    *par0_out = (a != 0) ? 9591 : 9536;        /* xc 2,aneq select */
    if ((*par3 & 4) == 0) {                    /* bitf *ar3,#4; bc ntc */
        frag_3667();
        return;
    }
    if ((*par3 & 8) == 0) {                    /* bitf *ar3,#8; bc ntc */
        frag_3652();
        return;
    }
    *(volatile int *)0x54F |= 16;              /* orm #16,*(0x54f) */
    a = (long)a_live & 8L;                     /* and #8,a (same value) */
    *par0_out = (a != 0) ? 9590 : 9535;        /* xc 2,aneq select */
    {
        long b = (long)*par4;                  /* ld *ar4,b */
        if ((*par3 & 2) == 0)                  /* bitf *ar3,#2; bc 3662,tc */
            b &= -257L;                        /* and #-257,b (mask 0xFEFF) */
        (void)b;                               /* rides into dark tail */
        frag_3664();                           /* b 0x3664 tail */
    }
}
