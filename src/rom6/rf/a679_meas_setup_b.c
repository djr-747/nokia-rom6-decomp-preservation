/* ROM6 0xA679 MEAS_SETUP_B -- 53w.
 * Verified encoding: src/rom6/rf/a679_meas_setup_b.asm (recombine MATCH; Entry-1 words ride the a687 vehicle src/rom6/kernel/a687_sub_a687.asm).
 * ORIGIN 0xA679
 * EXPECT: F074 065C 10F8 262E FC45 E901 F074 4BA8 E900 81F8 262E FE00 81F8 2614 F074 065E 60F8 2510 00C1 FC20 7712 051C 6182 0003 FC30 F074 AB2C 10F8 051C F030 0C00 F010 0800 FC45 76F8 337C 3236 E85F F074 BA56 76F8 337D 3236 70F8 337B 054A E85F F074 B750 69F8 2AFF 8000 FC00
 *
 * Intent: Measurement setup pair (two entries, one file per 53EB convention). Entry 0 (0xA679): runs dark SUB_065C; A = cell 0x262E, zero returns (rc aeq). Else B = 1, calls SUB_4BA8 with (A = cell, B = 1); B = 0 stored low to cell 0x262E; delayed return with cell 0x2614 = B-low in the slot (retd: slot always runs per 4238, then return). Entry 1 (0xA687, symbols SUB_A687): runs dark SUB_065E; cell 0x2510 != 193 returns (rc ntc). AR2 = 0x51C; *AR2 bit 0-1 set returns (bitf plus rc tc). Runs unbound FANOUT_AB2C (call, has .asm with bcd inside, forward extern void). A = cell 0x51C AND 3072 minus 2048 (SUB #lk,src form), zero returns (rc aeq). Else cell 0x337C = 12854, A = 95 into dark SUB_BA56; cell 0x337D = 12854, cell 0x337B = cell 0x54A (mvdk, dmad is destination), A = 95 into dark SUB_B750; sets bit 15 of cell 0x2AFF (orm); returns. Bound A679-A6AD.
 */
extern void sub_065C(void);
extern void sub_4BA8(int a_live, int b_live);
extern void sub_065E(void);
extern void fanout_AB2C(void);
extern void sub_BA56(void);
extern void sub_B750(void);

void sub_A679(void)
{
    int a, b;
    sub_065C();                                    /* call 0x65c */
    a = *(volatile int *)0x262E;               /* ld */
    if (a == 0) {
        return;                                    /* rc aeq */
    }
    b = 1;                                         /* ld #1,b */
    sub_4BA8(a, b);                                /* call 0x4ba8 */
    b = 0;                                         /* ld #0,b */
    *(volatile int *)0x262E = b & 0xFFFF;      /* stl b,*(0x262e) */
    *(volatile int *)0x2614 = b & 0xFFFF;      /* retd delay slot */
    /* retd: return */
}

void sub_A687(void)
{
    int a;
    int *ar2;
    sub_065E();                                    /* call 0x65e */
    if (*(volatile int *)0x2510 != 193) {      /* cmpm, rc ntc */
        return;
    }
    ar2 = (int *)(long)0x51C;                      /* stm #1308,ar2 */
    if ((*ar2 & 3) != 0) {                         /* bitf, rc tc */
        return;
    }
    fanout_AB2C();                                 /* call 0xab2c */
    a = *(volatile int *)0x51C;                /* ld */
    a &= 3072;                                     /* and #3072,a */
    a -= 2048;                                     /* sub #2048,a */
    if (a == 0) {                                  /* rc aeq */
        return;
    }
    *(volatile int *)0x337C = 12854;           /* st */
    a = 95;                                        /* ld #95,a */
    sub_BA56();                                    /* call 0xba56 */
    *(volatile int *)0x337D = 12854;           /* st */
    *(volatile int *)0x337B = *(volatile int *)0x54A; /* mvdk */
    a = 95;                                        /* ld #95,a */
    (void)a;                                       /* live into sub_B750, unobservable */
    sub_B750();                                    /* call 0xb750 */
    *(volatile int *)0x2AFF |= -32768;         /* orm #-32768 */
    /* ret */
}
