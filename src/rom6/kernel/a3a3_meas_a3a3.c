/* ROM6 0xA3A3 MEAS_A3A3 -- 27w.
 * Verified encoding: src/rom6/kernel/a3a3_meas_a3a3.asm (recombine MATCH).
 * ORIGIN 0xA3A3
 * EXPECT: F074 0654 F330 4000 7712 2639 1082 F030 0C00 F84D A3BE F030 0800 F274 40BC 6982 0800 11F8 2634 FC4C 68F8 2639 F3FF F074 3E53 E901 FC00
 *
 * Intent: Measurement gate. Runs dark 0x654 (forward extern); B caller-live (unbound, flagged) masked
 * with 16384; AR2 = 9785; A = *AR2 masked with 3072; zero tail-calls frag_A3BE (bc beq); else A masked
 * with 2048, calld 0x40BC (delay orm #2048,*AR2 runs first -- the 40BC scan sees the set bit),
 * B = cell 0x2634; nonzero returns (rc bneq); cell 0x2639 &= -3073 (andm); runs dark 0x3E53;
 * B = 1; return. Mappings by convention (unverified), flagged.
 */
extern void sub_0654(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_40BC(void); /* joins 40bc_memscan_setup; see docs/evidence/extern-triage.md */
extern void sub_3E53(void); /* joins 3e53_port_seq_sweep; see docs/evidence/extern-triage.md */
extern void frag_A3BE(int a_in, int *par2);

void sub_A3A3(void)
{
    long a;
    long b;      /* caller-live, never set in-span (flagged) */
    int *ar2;


    sub_0654();                                            /* call 0x654 */
    b &= 16384L;                                           /* and #16384,b */
    ar2 = (int *)9785;                                     /* stm #9785,ar2 */
    a = *ar2;                                              /* ld *ar2,a */
    a &= 3072L;                                            /* and #3072,a */
    if (a == 0) {                                          /* bc 0xa3be,beq */
        frag_A3BE(0, ar2);
        return;
    }
    a &= 2048L;                                            /* and #2048,a */
    *ar2 |= 2048;                                          /* calld delay: orm (runs first) */
    sub_40BC();                                            /* calld 0x40bc */
    b = *(volatile int *)0x2634;                          /* ld *(0x2634),b */
    if (b != 0)                                            /* rc bneq */
        return;
    *(volatile int *)0x2639 &= -3073;                       /* andm #-3073 */
    sub_3E53();                                            /* call 0x3e53 */
    b = 1;                                                 /* ld #1,b */
    /* ret @A3BD */
    (void)a; (void)b;
}
