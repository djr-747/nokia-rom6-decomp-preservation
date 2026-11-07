/* ROM6 0xA6AE SUB_A6AE -- 52w measurement-gate fanout.
 * Verified encoding: src/rom6/kernel/a6ae_sub_a6ae.asm (recombine MATCH).
 * ORIGIN 0xA6AE
 * EXPECT: F074 065E 60F8 2510 00C1 FC20 10F8 051C F030 0C00 F010 0800 FC45 76F8 337C 3296 E83F F074 BA56 61F8 2B08 0003 F820 A6E1 61F8 2AFF 8000 F820 A6D1 68F8 2AFF 7FFF E83F F074 B750 F074 9FCF 76F8 337C 3236 F074 C5F9 61F8 0577 1000 FB30 BCFC 7711 3236 F074 A109 FC00
 *
 * Intent: Runs sub_065E (RAM-resident, zero in mask
 * dump per a679). Cell 0x2510 != 193 returns (cmpm,
 * oracle TC = equality; rc ntc). A = cell 0x51C &
 * 3072 - 2048 (and #3072,a then sub #2048,a:
 * SUB_LK shift 0); zero returns (rc aeq). Cell
 * 0x337C = 12950 (st). A = 63 into dark sub_BA56
 * (call, A-live intake per a679, flagged). Bits
 * 0-1 of cell 0x2B08 clear returns (bitf; bc ntc
 * to the ret). Bit 15 of cell 0x2AFF clear skips
 * to the D1 join (bitf #-32768; bc ntc); else the
 * bit clears (andm #32767), A = 63 into dark
 * sub_B750 (call, A-live intake per a679). Join
 * D1: runs dark sub_9FCF (call, asm-only forward
 * extern per a8d4); cell 0x337C = 12854; runs
 * pooled C5F9 (call, no C entry, effects dark,
 * flagged). Bit 12 of cell 0x577 set runs the ccd
 * delay (AR1 = 12854, always) then the pooled
 * BCFC call (ccd 0xbcfc,tc, no C entry, dark,
 * flagged; a7eb always-delay shape). Runs
 * audio_select_A109; return. Entry A/B dead (set
 * in-span); out cells/AR1.
 * EXPECT from the image.
 */
/* call 0xc5f9: pooled, no C entry (see c5f9_config_dispatch_c5f9 Pool note) */
/* ccd 0xbcfc: pooled target, no C entry (see bcfc_frame_dispatch_bcfc Pool note) */
extern void sub_065E(void); /* RAM-resident, zero in mask dump per a679 */
extern void sub_BA56(void); /* joins ba56_bkmax_ba56; A-live intake per a679 */
extern void sub_B750(void); /* dark per a679; A-live intake */
extern void sub_9FCF(void); /* asm-only, forward extern per a8d4 */
extern void audio_select_A109(void);

void sub_A6AE(void)
{
    long a;
    int *ar1;

    sub_065E();                                            /* call 0x65e */
    if (*(volatile int *)0x2510 != 193)                    /* cmpm; rc ntc */
        return;
    a = (long)*(volatile int *)0x51C;                      /* ld *(0x51c),a */
    a &= 3072L;                                            /* and #3072,a */
    a -= 2048L;                                            /* sub #2048,a */
    if (a == 0L)                                           /* rc aeq */
        return;
    *(volatile int *)0x337C = 12950;                       /* st #12950,*(0x337c) */
    a = 63L;                                               /* ld #63,a */
    sub_BA56();                                            /* call 0xba56 */
    if ((*(volatile int *)0x2B08 & 3) == 0)                /* bitf; bc ntc */
        return;                                            /* b 0xa6e1 (ret) */
    if ((*(volatile int *)0x2AFF & 0x8000) == 0)           /* bitf; bc ntc */
        goto lane_d1;
    *(volatile int *)0x2AFF &= 32767;                      /* andm #32767 */
    a = 63L;                                               /* ld #63,a */
    sub_B750();                                            /* call 0xb750 */
lane_d1:
    sub_9FCF();                                            /* call 0x9fcf */
    *(volatile int *)0x337C = 12854;                       /* st #12854,*(0x337c) */
    /* call 0xc5f9 (pooled; effects dark, flagged) */
    if ((*(volatile int *)0x577 & 4096) != 0) {            /* bitf; ccd tc */
        ar1 = (int *)(long)12854;                          /* ccd delay (always) */
        /* call 0xbcfc (pooled; dark, flagged) */
    } else {
        ar1 = (int *)(long)12854;                          /* delay slot: always */
    }
    audio_select_A109();                                   /* call 0xa109 */
    /* ret */
}
