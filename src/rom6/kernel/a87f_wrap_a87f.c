/* ROM6 0xA87F WRAP_A87F -- 28w.
 * Verified encoding: src/rom6/kernel/a87f_wrap_a87f.asm (recombine MATCH).
 * ORIGIN 0xA87F
 * EXPECT: F074 067C 69F8 051E 0100 7712 2579 EC08 7092 09C8 10F8 051F F030 1800 F845 A8B1 60F8 0008 0800 F820 A89B 10F8 3082 1AF8 2EF7 F844 A8B9 FC00
 *
 * Intent: Worker plus triple fanout. Runs 0x67C; sets bit 8 of cell 0x51E; AR2 = 9593; 9 copies (rpt #8) of cell 0x9C8 through AR2 (mvdk); A = cell 0x51F AND 6144, zero tail-calls FRAG_A8B1 (bc 0xa8b1,aeq: has .asm, no C yet, forward extern per convention). Else AL == 2048 tail-calls FRAG_A89B (bc 0xa89b,ntc, C: frag_A89B); else A = cell 0x3082 OR cell 0x2EF7, nonzero tail-calls FRAG_A8B9 (bc 0xa8b9,aneq, C: frag_a8b9_zero); else return. BITF... (cmpm sets TC on equal per ti-c54x op_cmpm).
 */
extern void sub_067C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_A8B1(void);
extern void frag_A89B(void);
extern void frag_a8b9_zero(void);

void wrap_A87F(void)
{
    int a;
    sub_067C();                                  /* call 0x67c */
    *(volatile int *)0x51E |= 256;           /* orm #256 */
    {
        int i;
        int *ar2 = (int *)9593;                  /* stm #9593,ar2 */
        for (i = 0; i < 9; i++)                  /* rpt #8 */
            *ar2++ = *(volatile int *)0x9C8; /* mvkd */
    }
    a = *(volatile int *)0x51F & 6144;      /* ld, and */
    if (a == 0) {                                /* bc 0xa8b1,aeq */
        frag_A8B1();                             /* tail, unbound C */
        return;
    }
    if (*(volatile int *)0x8 != 2048) {          /* cmpm, bc ntc */
        frag_A89B();                             /* tail call */
        return;
    }
    a = *(volatile int *)0x3082 |
        *(volatile int *)0x2EF7;               /* ld, or */
    if (a != 0) {                                /* bc 0xa8b9,aneq */
        frag_a8b9_zero();                        /* tail call */
        return;
    }
    /* ret */
}
