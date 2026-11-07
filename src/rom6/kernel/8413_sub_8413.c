/* ROM6 0x8413 SUB_8413 -- 32w.
 * Verified encoding: src/rom6/kernel/8413_sub_8413.asm (recombine MATCH).
 * ORIGIN 0x8413
 * EXPECT: F074 05A0 4915 F310 0003 F77F 891A FC4B 60F8 250F 0022 F820 8436 60F8 34BF 0003 F820 8436 61F8 2648 0800 F820 8433 7714 2649 7713 34F2 68F8 2648 F7FF F073 843A
 *
 * Intent: Index-halve gate with three away tails. Runs 0x5A0 (dark, forward extern); B = AR5-live-in minus 3, halved arithmetic (sfta -1); BRC = B as a side effect (stlm, hardware state feeding callee repeat blocks, cited not bound); B < 0 signed returns (rc blt). Cell 0x250F != 34 or cell 0x34BF != 3 tail-enter 0x8436 (bc ntc pair, dark forward extern); bit 11 of cell 0x2648 clear tail-enters FRAG_8433 (bc ntc: bit-reversed span, asm-only, extern only). Else presets AR4/AR3 (dead, unused after, noted), clears bit 11 of cell 0x2648 (andm #-2049), tail-enters 0x843A (b, dark forward extern). Bound 8413-8432.
 */
extern void sub_05A0(void);
extern void frag_8436(void);
extern void frag_8433(void);
extern void frag_843A(void);

void sub_8413(int ar5_live)
{
    int b;
    sub_05A0();                                  /* call 0x5a0 */
    b = ar5_live;                                /* ldm ar5,b */
    b -= 3;                                      /* sub #3,b */
    b >>= 1;                                     /* sfta b,-1 (arithmetic) */
    /* stlm b,brc (BRC hardware state, cited) */
    if (b < 0)                                   /* rc blt */
        return;
    if (*(volatile int *)0x250F != 34) {         /* cmpm, bc ntc */
        frag_8436();                             /* away, dark */
        return;
    }
    if (*(volatile int *)0x34BF != 3) {          /* cmpm, bc ntc */
        frag_8436();                             /* away, dark */
        return;
    }
    if ((*(volatile int *)0x2648 & 2048) == 0) { /* bitf, bc ntc */
        frag_8433();                             /* away, asm-only span */
        return;
    }
    /* stm #9801,ar4; stm #13554,ar3 (dead presets, unused) */
    *(volatile int *)0x2648 &= -2049;        /* andm #-2049 */
    frag_843A();                                 /* b 0x843a tail */
}
