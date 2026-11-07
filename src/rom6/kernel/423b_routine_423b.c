/* ROM6 0x423B ROUTINE_423B -- 36w.
 * Verified encoding: src/rom6/kernel/423b_routine_423b.asm (recombine MATCH).
 * ORIGIN 0x423B
 * EXPECT: 720E 051F 68F8 000E 000F F166 0050 F600 8813 7714 008B 1083 7313 1234 7308 1235 10F8 051F F030 000F 11F8 263B F330 00F0 F2A0 8083 F274 2C88 7715 00A2 7213 1234 F495 7083 1235 FC00
 *
 * Intent: T-scaled accumulate with cell snapshot. T = cell 0x51F (mvdm); cell 0xE &= 15 (andm to MMR); B = T times 80 (MPY #lk,dst per 84CF precedent; 16-bit narrowing noted); A = A-live-in plus B (ADD src,dst). AR3 = A low (stlm); AR4 = 139; A = *AR3; cell 0x1234 = AR3 value, cell 0x1235 = A low (mvmd pair). A = cell 0x51F AND 15; B = cell 0x263B AND 240; A |= B; *AR3 = A low. Delayed-call into dark ROUTINE_2C88 (calld, void per 36B0; delay stm #162,ar5 preset dead in C, noted). AR3 = cell 0x1234; *AR3 = cell 0x1235 (mvdm/mvkd restore); returns. Bound 423B-425E.
 */
extern void routine_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */

void frag_423B(int a_live)
{
    int a = a_live;
    int b;
    int t;
    int *ar3;
    t = *(volatile int *)0x51F;                /* mvdm 0x51f,t */
    *(volatile int *)0xE &= 15;              /* andm */
    b = t * 80;                                    /* mpy #80,b */
    a += b;                                        /* add b,a */
    ar3 = (int *)(long)(a & 0xFFFF);               /* stlm a,ar3 */
    /* stm #139,ar4 (dead preset, no use in span, noted) */
    a = *ar3;                                      /* ld *ar3,a */
    *(volatile int *)0x1234 = (int)(long)ar3;  /* mvmd ar3 */
    *(volatile int *)0x1235 = a & 0xFFFF;      /* mvmd al */
    a = *(volatile int *)0x51F;                /* ld */
    a &= 15;                                       /* and #15,a */
    b = *(volatile int *)0x263B;               /* ld */
    b &= 240;                                      /* and #240,b */
    a |= b;                                        /* or b,a */
    *ar3 = a & 0xFFFF;                             /* stl a,*ar3 */
    /* stm #162,ar5 (calld delay slot, dead preset, noted) */
    routine_2C88();                                /* calld 0x2c88 */
    ar3 = (int *)(long)*(volatile int *)0x1234; /* mvdm */
    /* nop */
    *ar3 = *(volatile int *)0x1235;            /* mvkd */
    /* ret */
}
