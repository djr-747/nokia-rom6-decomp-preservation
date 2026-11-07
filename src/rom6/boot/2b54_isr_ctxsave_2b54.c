/* ROM6 0x2B54 ISR_CTXSAVE_2B54 -- 77w.
 * Verified encoding: src/rom6/boot/2b54_isr_ctxsave_2b54.asm (recombine MATCH).
 * ORIGIN 0x2B54
 * EXPECT: 69F8 0866 0002 4A08 4A09 4A0A 4A0B 4A0C 4A0D 12F8 0870 F845 2B98 10F8 04C2 F010 0004 F842 2B98 4BF8 0060 4BF8 0061 4A0E 4A10 4A11 4A12 4A13 4A14 4A15 4A16 4A17 4A1A 4A1B 4A1C 4A19 771B 0000 771C 0000 F074 B4F8 69F8 0029 0008 68F8 0029 FFF7 76F8 0870 0000 8A19 8A1C 8A1B 8A1A 8A17 8A16 8A15 8A14 8A13 8A12 8A11 8A10 8A0E 8BF8 0061 8BF8 0060 8A0D 8A0C 8A0B 8A0A 8A09 8A08 8A07 8A06 F4E5
 *
 * Intent: COBBA-command ISR context-save wrapper. Cell 0x866 bit 1 set (orm); A = cell 0x870 unsigned
 * (ldu); zero joins the shared pop lane (bc aeq). A = cell 0x4C2 - 4 (ld/sub); non-negative joins the pop
 * lane (bc ageq). Full register save (pshm group + pshd pair + T/AR/BRC/RSA/REA/BK, balanced by the popm
 * restores -- caller-live, comments only per 2D5E precedent); RSA = REA = 0 (stm); runs dark SUB_B4F8
 * (forward extern void, rf/b4f8_cobba_worker); cell 0x29 bit 3 set then cleared (orm/andm pair, net clear);
 * cell 0x870 cleared (st). Pop lane: balanced restores, frete (interrupt return, no C form). Entry:
 * fall-through from the 2B53 ISR head; no other exterior callers, entry unconfirmed, flagged.
 */
extern void sub_B4F8(void); /* joins b4f8_cobba_worker; see docs/evidence/extern-triage.md */

void isr_2B54(void)
{
    long a;


    *(volatile int *)0x866 |= 2;                           /* orm #2,*(0x866) */
    /* pshm al/ah/ag/bl/bh/bg (balanced by popm; caller-live, comments only) */
    a = (long)(unsigned)*(volatile int *)0x870;            /* ldu *(0x870),a */
    if (a == 0)                                            /* bc 0x2b98,aeq */
        goto l2b98;
    a = (long)*(volatile int *)0x4C2 - 4;                  /* ld; sub #4,a */
    if (a >= 0)                                            /* bc 0x2b98,ageq */
        goto l2b98;
    /* pshd *(0x60)/1 + pshm t/ar0-ar7/brc/rsa/rea/bk (balanced, comments only) */
    /* stm #0,rsa; stm #0,rea (dark callee may read, flagged) */
    sub_B4F8();                                            /* call 0xb4f8 (dark) */
    *(volatile int *)0x29 |= 8;                            /* orm #8,*(0x29) */
    *(volatile int *)0x29 &= -9;                           /* andm #-9 (net clear) */
    *(volatile int *)0x870 = 0;                            /* st #0,*(0x870) */
    /* popm bk/rea/rsa/brc/ar7-ar0/t + popd pair (restore entry state) */
l2b98:
    /* popm bg/bh/bl/ag/ah/al/st1/st0 (restore entry state) */
    /* frete (interrupt return, no C form) */
}
