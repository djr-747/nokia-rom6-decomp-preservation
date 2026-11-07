/* ROM6 0xB3B1 ROUTINE_B3B1 -- 49w helper-call fork with cell spill.
 * Verified encoding: src/rom6/kernel/b3b1_routine_b3b1.asm (recombine MATCH).
 * ORIGIN 0xB3B1
 * EXPECT: F074 05A8 7715 B550 7716 B565 F020 B55C F074 AEEC F074 AF40 10F8 3490 F130 0007 F84C B3C7 7712 34C4 F073 B3D1 F130 0001 F84D B3CF 7712 34C5 F073 B3D1 7712 34C6 4A12 7182 262D F074 A654 8A12 7713 B550 7716 B565 F020 B55C 7082 262D F074 AF16 FC00
 *
 * Intent: Runs dark sub_05A8 (call, low-zone,
 * flagged). AR5 = -19120, AR6 = -19099, A = -19108
 * (ld #-19108,a: LD_LK shift 0 per oracle layout).
 * Runs sub_AEEC, then routine_AF40 with caller-live
 * AR1 (dark intake, flagged). A = cell 0x3490; B =
 * A & 7; nonzero selects the bit-0 lane (bc bneq,
 * oracle B != 0), else AR2 = 13508 and joins.
 * Bit-0 lane: B = A & 1; zero selects AR2 = 13510
 * (bc beq), else AR2 = 13509; joins. Join: AR2-save
 * (pshm/popm balanced, caller-live, comment only);
 * cell 0x262D = *(AR2) (mvdk spill); runs pooled
 * A654 (call, no C entry, effects dark, flagged);
 * *(AR2) = cell 0x262D (mvkd restore); AR3 =
 * -19120, AR6 = -19099, A = -19108; runs sub_AF16
 * (joins af16_routine_af16); return. MVKD/MVDK both
 * copy first operand to second (2000/2088/22f3
 * precedents). Out AR2/AR5/AR6/AR3/A.
 * EXPECT from the image.
 */
extern void sub_05A8(void); /* dark, no symbol per b358 */
extern void sub_AEEC(void); /* joins aeec_regfield_helper */
extern void routine_AF40(int *par1_saved);
extern void sub_AF16(void); /* joins af16_routine_af16 */

void routine_B3B1(void)
{
    long a;
    long b;
    int *ar1;   /* live-in (dark, flagged): AF40 intake */
    int *ar2;
    int *ar3;
    int *ar5;
    int *ar6;

    sub_05A8();                                            /* call 0x5a8 */
    ar5 = (int *)(long)-19120;                             /* stm #-19120,ar5 */
    ar6 = (int *)(long)-19099;                             /* stm #-19099,ar6 */
    a = -19108L;                                           /* ld #-19108,a */
    sub_AEEC();                                            /* call 0xaeec */
    routine_AF40(ar1);                                     /* call 0xaf40 */
    a = (long)*(volatile int *)0x3490;                     /* ld *(0x3490),a */
    b = a & 7L;                                            /* and #7,a,b */
    if (b != 0L)                                           /* bc 0xb3c7,bneq */
        goto lane_c7;
    ar2 = (int *)(long)13508;                              /* stm #13508,ar2 */
    goto join_d1;                                          /* b 0xb3d1 */
lane_c7:
    b = a & 1L;                                            /* and #1,a,b */
    if (b == 0L)                                           /* bc 0xb3cf,beq */
        ar2 = (int *)(long)13510;                          /* stm #13510,ar2 */
    else
        ar2 = (int *)(long)13509;                          /* stm #13509,ar2 */
join_d1:
    /* pshm ar2 (balanced by popm; caller-live, comment only) */
    *(volatile int *)0x262D = *ar2;                        /* mvdk *ar2,0x262d */
    /* call 0xa654 (pooled, no C entry; effects dark, flagged) */
    /* popm ar2 (restore entry) */
    ar3 = (int *)(long)-19120;                             /* stm #-19120,ar3 */
    ar6 = (int *)(long)-19099;                             /* stm #-19099,ar6 */
    a = -19108L;                                           /* ld #-19108,a */
    *ar2 = *(volatile int *)0x262D;                        /* mvkd 0x262d,*ar2 */
    sub_AF16();                                            /* call 0xaf16 */
    /* ret */
}
