/* ROM6 0x5BF1 HUB_5BF1 -- 67w eight-call scatter hub, one EXPECT.
 * Verified encoding: src/rom6/kernel/5bf1_hub_5bf1.asm (recombine MATCH).
 * ORIGIN 0x5BF1
 * EXPECT: F074 0674 F6BE EA00 E800 8817 8811 7660 0040 7661 000F 7616 0003 7710 2B1C F274 5C34 7715 DCC3 E896 F274 5C34 7711 0039 E801 7711 0156 6D97 F274 5C34 7715 DCC3 E897 F274 5C34 7711 018F E800 6D8F 7711 0072 7710 2B55 F274 5C34 7715 DCC3 E896 F274 5C34 7711 00AB E801 7711 00E4 6D97 F274 5C34 7715 DCC3 E897 F274 5C34 7711 011D F7BE FC00
 *
 * Intent: Eight-call SUB_5C34 driver over staggered windows. Entry via
 * call F074@4CD3 (objdump-verified). Runs dark SUB_0674 (call);
 * CPL = 0, DP = 0 (hardware, no C form); AR7 = AR1 = 0 (stlm);
 * *(0x60) = 64, *(0x61) = 15, *(0x16) = 3 (st DP cells: the 5C34 shift
 * bias/mask set). AR0 = 11036. Eight calld SUB_5C34 (delays are
 * callee-visible pre-branch state per 4BA8, passed as arguments here):
 *   1: A = 0,   AR1 = 0,   (delay AR5 = -9021)
 *   2: A = 150, AR1 = 57,  (delay AR1 = 57; AR5 rides -9021)
 *   3: A = 1,   AR1 = 342, AR7++ (delay AR5 = -9021)
 *   4: A = 151, AR1 = 399, (delay AR1 = 399)
 *   5: A = 0,   AR1 = 114, AR0 = 11093, AR7-- (delay AR5 = -9021)
 *   6: A = 150, AR1 = 171, (delay AR1 = 171)
 *   7: A = 1,   AR1 = 228, AR7++ (delay AR5 = -9021)
 *   8: A = 151, AR1 = 285, (delay AR1 = 285)
 * AR5 = -9021 for every call (re-armed in each odd-call delay);
 * AR0 = 11036 for calls 1-4, 11093 for 5-8; AR7 = 0,0,1,1,0,0,1,1
 * (mar *ar7+/-; set but never read in the callee span: live-out, noted).
 * CPL = 1 restores at the end (hardware); RET @5C33.
 * Bound 5BF1-5C33.
 */
extern void sub_0674(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_5C34(long a_live, int ar1_live, int *par5, int ar0_live);

void hub_5BF1(void)
{
    int ar0 = 11036;
    int ar1 = 0;
    int ar7 = 0;

    sub_0674();                                        /* call 0x674 */
    /* rsbx cpl; ld #0,dp (hardware, no C form) */
    /* stlm a,ar7/ar1 with A = 0 (ld #0,a) */
    *(volatile int *)0x60 = 64;    /* st #64,DP+0x60 (DP = 0) */
    *(volatile int *)0x61 = 15;    /* st #15,DP+0x61 */
    *(volatile int *)0x16 = 3;     /* st #3,DP+0x16 */
    /* calld 0x5c34 (delay stm #-9021,ar5 rides in) */
    sub_5C34(0L, ar1, (int *)0xDCC3, ar0);              /* call 1 */
    /* calld 0x5c34 (delay stm #57,ar1 rides in) */
    ar1 = 57;
    sub_5C34(150L, ar1, (int *)0xDCC3, ar0);           /* call 2 */
    ar1 = 342;
    ar7++;                                             /* mar *ar7+ */
    /* calld 0x5c34 (delay stm #-9021,ar5 rides in) */
    sub_5C34(1L, ar1, (int *)0xDCC3, ar0);              /* call 3 */
    /* calld 0x5c34 (delay stm #399,ar1 rides in) */
    ar1 = 399;
    sub_5C34(151L, ar1, (int *)0xDCC3, ar0);            /* call 4 */
    ar0 = 11093;
    ar1 = 114;
    ar7--;                                             /* mar *ar7- */
    /* calld 0x5c34 (delay stm #-9021,ar5 rides in) */
    sub_5C34(0L, ar1, (int *)0xDCC3, ar0);              /* call 5 */
    /* calld 0x5c34 (delay stm #171,ar1 rides in) */
    ar1 = 171;
    sub_5C34(150L, ar1, (int *)0xDCC3, ar0);            /* call 6 */
    ar1 = 228;
    ar7++;                                             /* mar *ar7+ */
    /* calld 0x5c34 (delay stm #-9021,ar5 rides in) */
    sub_5C34(1L, ar1, (int *)0xDCC3, ar0);              /* call 7 */
    /* calld 0x5c34 (delay stm #285,ar1 rides in) */
    ar1 = 285;
    sub_5C34(151L, ar1, (int *)0xDCC3, ar0);            /* call 8 */
    /* ssbx st1,cpl (hardware, no C form) */
    /* ret @5C33 (AR7-live-out noted above) */
}
