/* ROM6 0xA482 MSG_SETUP_A -- 56w.
 * Verified encoding: src/rom6/msg/a482_msg_setup_a.asm (recombine MATCH).
 * ORIGIN 0xA482
 * EXPECT: F074 0656 10F8 262C FC45 11F8 2615 60F8 250F 0022 F820 A492 F210 0E42 F073 A494 F210 0D48 F843 A4B2 4A0B 74F8 0008 0010 08F8 265A F844 A4B0 76F8 0543 0003 60F8 250F 0022 F820 A4AE 60F8 34BF 0000 F820 A4AE 76F8 0543 0002 F074 3986 E900 8A0B 10F8 262C F274 AB82 7712 000A E801 FC00
 *
 * Intent: Tune-select setup with status return. Runs dark SUB_0656; A = cell 0x262C, zero returns 0 (rc aeq: A live-out 0). B = cell 0x2615; cell 0x250F != 34 selects the 3400 lane (bc ntc) else the 3650 lane (b); A = B - lane (SUB #lk SHFT-0 per ti-c54x op_sub_lk; 16-bit narrowing noted, alt precedent per 6871); A < 0 skips to the calld gate (bc alt). Else saves B-low (pshm bl), A = port 16 (AL alias) minus cell 0x265A, nonzero skips the setup stores (bc aneq to the SUB_3986 gate). Stores 3 to cell 0x543; cell 0x250F != 34 or cell 0x34BF != 0 skips the downgrade to 2 (bc ntc pair). Runs dark SUB_3986. Zeroes B then restores B-low (ld plus popm round-trip: high was zero from the cell load, net B preserved, noted). A = cell 0x262C, then delayed-call into SUB_AB82 (calld, void per A3E1 precedent: delay slots stm #10,ar2 and ld #1,a always run in ROM; AR2 preset dead in C, A = 1 doubles as the return value); returns 1. Bound A482-A4B9.
 */
extern void sub_0656(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern int port_read_16(void);
extern void sub_3986(void);
extern void sub_AB82(void); /* joins ab82_shared_worker_596; see docs/evidence/extern-triage.md */

int sub_A482(void)
{
    int a, b;
    int bl_save;
    sub_0656();                                    /* call 0x656 */
    a = *(volatile int *)0x262C;               /* ld */
    if (a == 0) {
        return 0;                                  /* rc aeq */
    }
    b = *(volatile int *)0x2615;               /* ld */
    if (*(volatile int *)0x250F != 34) {       /* cmpm, bc ntc */
        goto l_a492;
    }
    a = b - 3650;                                  /* sub #3650,b,a */
    goto l_a494;                                   /* b */
l_a492:
    a = b - 3400;                                  /* sub #3400,b,a */
l_a494:
    if (a < 0) {                                   /* bc 0xa4b2,alt */
        goto l_a4b2;
    }
    bl_save = b & 0xFFFF;                          /* pshm bl */
    a = port_read_16();                            /* portr 16,*(0x8) */
    *(volatile int *)0x8 = a;                  /* AL alias write */
    a -= *(volatile int *)0x265A;              /* sub *(0x265a),a */
    if (a != 0) {                                  /* bc 0xa4b0,aneq */
        goto l_a4ae;
    }
    *(volatile int *)0x543 = 3;                /* st */
    if (*(volatile int *)0x250F != 34) {       /* cmpm, bc ntc */
        goto l_a4ae;
    }
    if (*(volatile int *)0x34BF != 0) {         /* cmpm, bc ntc */
        goto l_a4ae;
    }
    *(volatile int *)0x543 = 2;                /* st */
l_a4ae:
    sub_3986();                                    /* call 0x3986 */
l_a4b0:
    b = 0;                                         /* ld #0,b */
    b = bl_save;                                   /* popm bl (net preserve) */
    (void)b;
l_a4b2:
    a = *(volatile int *)0x262C;               /* ld */
    /* calld 0xab82: delay slots always run (ROM); AR2 preset dead in C */
    /* stm #10,ar2 (delay slot, dead) */
    a = 1;                                         /* ld #1,a (delay slot) */
    sub_AB82();                                    /* calld 0xab82 */
    return a;                                      /* ret: 1 done, 0 early */
}
