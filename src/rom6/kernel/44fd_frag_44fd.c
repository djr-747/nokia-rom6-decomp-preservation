/* ROM6 0x44FD FRAG_44FD -- 47w.
 * Verified encoding: src/rom6/kernel/44fd_frag_44fd.asm (recombine MATCH).
 * ORIGIN 0x44FD
 * EXPECT: F074 0594 10F8 2F00 F030 00FF 4A08 4A09 4A0A F074 2E2F 10F8 0871 F110 0000 F84D 4511 8812 F074 226C 8A0A 8A09 8A08 F844 451E F274 2262 7712 000D F074 226C F073 452C F274 2262 7712 000E F074 226C F274 2262 7712 0004 F074 226C F073 3028
 *
 * Intent: Dispatcher-guarded call fanout (three entries, one file per 53EB convention). Entry 0 (0x44FD): runs dark SUB_0594; A = cell 0x2F00 AND 255, saved across the dispatcher call (pshm triple); runs C DISPATCHER_ENTRY_2E2F; A = cell 0x871, B = A - 0 (SUB #lk SHFT-0 per op_sub_lk), zero joins the shared epilogue (bc beq); else AR2 = A (stlm, local, live into dark SUB_226C per precedent) and runs SUB_226C. Epilogue 0x4511 (shared join): restores A (popm triple; the aneq below tests the restored masked value, not call junk); nonzero runs entry 2 (bc aneq). Else delayed-call into SUB_2262 (calld, void per 84CF; delay stm #13,ar2 preset dead in C, noted) then SUB_226C, tail-enters C FRAG_452C (b, C-bound). Entry 2 (0x451E): delayed-call 2262 (delay stm #14, dead), SUB_226C, falls into the 4524 tail: delayed-call 2262 (delay stm #4, dead), SUB_226C, tail-enters C FRAG_3028 (b, C-bound). Bound 44FD-452B.
 */
extern void sub_0594(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void dispatcher_entry_2E2F(void);
extern void sub_226C(void); /* unowned @0x226C; see docs/evidence/extern-triage.md */
extern void sub_2262(void); /* unowned @0x2262; see docs/evidence/extern-triage.md */
extern void frag_452C(void);
extern void frag_3028(void);
extern void frag_451E(void);

void frag_44FD(void)
{
    int a, b;
    int *ar2;
    int a_saved;
    sub_0594();                                    /* call 0x594 */
    a = *(volatile int *)0x2F00;               /* ld */
    a &= 255;                                      /* and #255,a */
    a_saved = a;                                   /* pshm al/ah/ag */
    dispatcher_entry_2E2F();                       /* call 0x2e2f */
    a = *(volatile int *)0x871;                /* ld */
    b = a - 0;                                     /* sub #0,a,b */
    if (b == 0) {
        goto l4511;                                /* bc 0x4511,beq */
    }
    ar2 = (int *)(long)(a & 0xFFFF);               /* stlm a,ar2 */
    (void)ar2;                                     /* live into sub_226C */
    sub_226C();                                    /* call 0x226c */
/* l4511: popm ag/ah/al (A restored) */
l4511:
    a = a_saved;
    if (a != 0) {                                  /* bc 0x451e,aneq */
        frag_451E();                               /* join entry 2 */
        return;
    }
    /* stm #13,ar2 (calld delay slot, dead preset, noted) */
    sub_2262();                                    /* calld 0x2262 */
    sub_226C();                                    /* call 0x226c */
    frag_452C();                                   /* b 0x452c tail */
}

void frag_451E(void)
{
    /* stm #14,ar2 (calld delay slot, dead preset, noted) */
    sub_2262();                                    /* calld 0x2262 */
    sub_226C();                                    /* call 0x226c */
    /* stm #4,ar2 (calld delay slot, dead preset, noted) */
    sub_2262();                                    /* calld 0x2262 */
    sub_226C();                                    /* call 0x226c */
    frag_3028();                                   /* b 0x3028 tail */
}
