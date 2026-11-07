/* ROM6 0xA843 FRAG_A843 -- 60w message-buffer setup + dispatch.
 * Verified encoding: src/rom6/kernel/a843_frag_a843.asm (recombine MATCH).
 * ORIGIN 0xA843
 * EXPECT: F074 067C E802 08F8 2EFE F844 A84C 80F8 2EFE 60F8 2510 00C0 FC20 61F8 051C 0003 FC30 61F8 051F 1800 FC30 61F8 051C 0040 F920 AB2C 7711 3196 EC9F 7091 32E5 10F8 2EFE FB44 AB7E 7712 3196 10F8 2EFE F945 9E2F F074 A8FE 76F8 337C 3236 76F8 337D 3236 E89F F074 BA56 F274 BAC2 7712 3196 76F8 2EFE 0000 FC00
 *
 * Intent: Post-RET head (A842 = ROUTINE_A815 exit) entered by call
 * (void; all regs seated in-span). Runs dark SUB_067C (low-zone
 * mini-kernel, no symbol, opaque). A = 2 - cell 0x2EFE; zero stores
 * cell 0x2EFE = 0 (bc aneq skips the store when nonzero). TC = (cell
 * 0x2510 == 192) (cmpm); rc ntc clears carry when unequal. Two
 * bitf/rc-tc pairs over cells 0x51C#3 and 0x51F#6144 set carry when
 * set. bitf cell 0x51C#64 with TC clear calls fanout_AB2C (cc ntc).
 * AR1 = 12694; rpt #159 broadcasts cell 0x32E5 into 160 cells (mvkd
 * dmad=source, k+1 = 160). A = cell 0x2EFE; AR2 = 12694 (ccd delay,
 * always runs); nonzero calls the AB7E rptz lane inside LEAF_AB78
 * (frag_AB7E forward extern, ab78 @+0x6 interior join per the 28d6
 * precedent: skips 06A4/bitf, fills 160x from AR2, returns). A = cell
 * 0x2EFE re-read volatile; zero calls pooled 9E2F (cc aeq; no C entry,
 * effects dark, flagged). Runs dispatch_A8FE_A8FE. Cells 0x337C/0x337D
 * = 12854 (st). A = 159; runs bkmax_BA56 (asm-only). AR2 = 12694
 * (calld delay, always runs); runs routine_BAC2(AR2). Cell 0x2EFE = 0
 * (st); ret. B never set (dark in/out, noted); T untouched (dark);
 * carry 0-modeled unread. Out cells/A/ARs/TC/C. EXPECT from the image.
 */
extern void sub_067C(void);    /* dark, no symbol (low-zone mini-kernel) */
extern void fanout_AB2C(void);
extern void frag_AB7E(int *ar2_in); /* joins ab78_leaf_ab78 interior @+0x6 (rptz lane) */
extern void dispatch_A8FE_A8FE(void);
extern void bkmax_BA56(void);  /* asm-only, joins ba56_bkmax_ba56 */
extern void routine_BAC2(int *ar2_in);
/* cc 0x9e2f: pooled, no C entry (see Pool note in 9e2f_leaf_9e2f.c) */

void frag_A843(void)
{
    long a;
    int tc;
    int carry = 0;  /* C54x carry in (dark, flagged); never read in-span */
    int *ar1;
    int *ar2;
    int i;

    sub_067C();                                              /* call 0x67c */
    a = 2L;                                                  /* ld #2,a */
    a -= (long)*(volatile int *)0x2EFE;                      /* sub *(0x2efe),a */
    if (a == 0)                                              /* bc 0xa84c,aneq not taken */
        *(volatile int *)0x2EFE = (int)(a & 0xFFFFL);        /* stl a,*(0x2efe) */
    tc = (*(volatile int *)0x2510 == 192);                   /* cmpm *(0x2510),#192 */
    if (!tc)                                                 /* rc ntc */
        carry = 0;
    if ((*(volatile int *)0x51C & 3) != 0)                   /* bitf *(0x51c),#3 */
        carry = 0;                                           /* rc tc */
    if ((*(volatile int *)0x51F & 6144) != 0)                /* bitf *(0x51f),#6144 */
        carry = 0;                                           /* rc tc */
    tc = ((*(volatile int *)0x51C & 64) != 0);               /* bitf *(0x51c),#64 */
    if (!tc)                                                 /* cc 0xab2c,ntc */
        fanout_AB2C();
    ar1 = (int *)(long)12694;                                /* stm #12694,ar1 */
    for (i = 0; i < 160; i++)                                /* rpt #159 */
        *ar1++ = *(volatile int *)0x32E5;                    /* mvkd 0x32e5,*ar1+ */
    a = (long)*(volatile int *)0x2EFE;                       /* ld *(0x2efe),a */
    ar2 = (int *)(long)12694;                                /* ccd delay: stm (always) */
    if (a != 0)                                              /* ccd 0xab7e,aneq */
        frag_AB7E(ar2);
    a = (long)*(volatile int *)0x2EFE;                       /* ld *(0x2efe),a */
    if (a == 0) {                                            /* cc 0x9e2f,aeq */
        /* call 0x9e2f (pooled; effects dark, flagged) */
    }
    dispatch_A8FE_A8FE();                                    /* call 0xa8fe */
    *(volatile int *)0x337C = 12854;                         /* st #12854,*(0x337c) */
    *(volatile int *)0x337D = 12854;                         /* st #12854,*(0x337d) */
    a = 159L;                                                /* ld #159,a */
    bkmax_BA56();                                            /* call 0xba56 */
    ar2 = (int *)(long)12694;                                /* calld delay: stm (always) */
    routine_BAC2(ar2);                                       /* calld 0xbac2 */
    *(volatile int *)0x2EFE = 0;                             /* st #0,*(0x2efe) */
    (void)carry;
}
