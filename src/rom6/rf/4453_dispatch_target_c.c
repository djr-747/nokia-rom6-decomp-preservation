/* ROM6 0x4453 DISPATCH_TARGET_C -- 26w.
 * Verified encoding: src/rom6/rf/4453_dispatch_target_c.asm (recombine MATCH).
 * ORIGIN 0x4453
 * EXPECT: 4913 61F8 3EC8 0020 F820 4463 4A08 4A09 4A0A F210 0029 F845 44A6 8A0A 8A09 8A08 7715 052A EC02 7C95 44AF 81F8 052B F074 052A FC00
 *
 * Intent: Guarded program-table broadcast plus call. B = AR3-entry value (ldm, par3; par4 unused per family shape). Bit 5 of cell 0x3EC8 clear skips to the broadcast at 0x4463 (bc ntc). Else saves A (pshm triple, hardware state, restored before use downstream), A = B - 41 (SUB #lk SHFT-0 per ti-c54x op_sub_lk), A == 0 runs dark 0x44A6 (bc aeq, forward extern; B == 41 gate); restores A (popm triple). AR5 = 1322; 3 copies (rpt #2) of program word 0x44AF (mvpd absolute, same word broadcast per 4444 precedent) through AR5; cell 0x52B = B low (stl); runs dark SUB_052A (call, per 4444); returns. Bound 4453-446C.
 */
extern int prom_read_word(int prog_addr);      /* mvpd: program read */
extern void frag_44A6(void);
extern void sub_052A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void dispatch_target_C_4453(int *par3, int *par4)
{
    int i;
    int a, b = (int)(long)par3;                    /* ldm ar3,b */
    int *ar5;
    (void)par4;
    if ((*(volatile int *)0x3EC8 & 32) == 0) { /* bitf, bc ntc */
        goto l4463;
    }
    /* pshm al/ah/ag (hardware state, restored below, no C form) */
    a = b - 41;                                    /* sub #41,b,a */
    if (a == 0) {                                  /* bc 0x44a6,aeq */
        frag_44A6();                               /* away, dark */
        return;
    }
    /* popm ag/ah/al (A restored; dead downstream, noted) */
l4463:
    ar5 = (int *)(long)1322;                       /* stm #1322,ar5 */
    for (i = 0; i < 3; i++) {                      /* rpt #2 */
        *ar5++ = prom_read_word(0x44AF);           /* mvpd 0x44af,*ar5+ */
    }
    *(volatile int *)0x52B = b & 0xFFFF;       /* stl b,*(0x52b) */
    sub_052A();                                    /* call 0x52a */
    /* ret */
}
