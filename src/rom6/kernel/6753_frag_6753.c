/* ROM6 0x6753 FRAG_6753 -- 23w.
 * Verified encoding: src/rom6/kernel/6753_frag_6753.asm (recombine MATCH).
 * ORIGIN 0x6753
 * EXPECT: 60F8 0008 0002 F820 676A 7711 053D E833 F274 6976 7712 2FD7 6FF8 2FDD 0E20 F842 676A F074 697F F274 6987 7712 053D
 *
 * Intent: Subtract-compare with save fallthrough. AL-alias cell != 2 tail-enters dark 0x676A (bc ntc). Else AR1 = 0x53D, A = 51; delayed-call into dark SUB_6976 (calld, void; delay stm dead as in 6679). A = B-live-in minus *(0x2FDD) (SUB Xmem,SHFT,src,dst SHFT 0, B threaded as param), non-negative tail-enters 0x676A (bc ageq). Else runs C DARAM_SAVE_RESTORE; AR2 = 0x53D into DARAM_CELL_STORE (calld with delay-slot src, per 6679); falls into dark 0x676A (fallthrough tail). Bound 6753-6769.
 */
extern void frag_676A(void);
extern void sub_6976(void);
extern void daram_save_restore(void);
extern void daram_cell_store(int *src);

void frag_6753(int b_live)
{
    int a;
    int b = b_live;
    int *ar2;
    if (*(volatile int *)0x8 != 2) {            /* cmpm, bc ntc */
        frag_676A();                                 /* tail, dark */
        return;
    }
    /* stm #1341,ar1 (dead preset, noted) */
    a = 51;                                        /* ld #51,a */
    /* stm #12247,ar2 (calld delay slot, dead preset, noted) */
    sub_6976();                                    /* calld 0x6976 */
    a = b - *(volatile int *)0x2FDD;           /* sub *(0x2fdd),b,a */
    if (a >= 0) {                                  /* bc 0x676a,ageq */
        frag_676A();                               /* tail, dark */
        return;
    }
    daram_save_restore();                          /* call 0x697f */
    ar2 = (int *)(long)0x53D;                      /* stm (delay slot: src) */
    daram_cell_store(ar2);                         /* calld 0x6987 */
    frag_676A();                                   /* fallthrough tail */
}
