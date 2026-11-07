/* ROM6 0x6679 FRAG_6679 -- 26w.
 * Verified encoding: src/rom6/kernel/6679_frag_6679.asm (recombine MATCH).
 * ORIGIN 0x6679
 * EXPECT: 60F8 000B 0002 F820 6693 7711 053D E833 F274 6976 7712 2FD7 F200 0003 0885 F846 676A 8185 F074 697F F274 6987 7712 053D F073 676A
 *
 * Intent: Add-compare store with save tail. BL-alias cell != 2 runs C FRAG_6693 with entry AR5/AR6 (bc ntc, C-bound passthrough pair). Else AR1 = 0x53D, A = 51; delayed-call into dark SUB_6976 (calld, void; delay stm #12247,ar2 preset dead, AR2 unused after, noted). A = B-live-in plus 3 (ADD #lk,src,dst); A -= *AR5-entry (SUB Xmem,src, 16-bit narrowing noted), positive tail-enters dark 0x676A (bc agt, signed per 6871). Else *AR5 = B low; runs C DARAM_SAVE_RESTORE (call, C-bound); AR2 = 0x53D into DARAM_CELL_STORE (calld, C-bound with src param: the delay-slot stm IS the argument); tail-enters dark 0x676A (b). Bound 6679-6692.
 */
extern void frag_6693(int *par5, int *par6);
extern void sub_6976(void);
extern void daram_save_restore(void);
extern void daram_cell_store(int *src);
extern void frag_676A(void);

void frag_6679(int b_live, int *par5, int *par6)
{
    int a;
    int b = b_live;
    int *ar2;
    if (*(volatile int *)0xB != 2) {            /* cmpm, bc ntc */
        frag_6693(par5, par6);                       /* away, C-bound */
        return;
    }
    /* stm #1341,ar1 (dead preset, AR1 unused after, noted) */
    a = 51;                                        /* ld #51,a */
    /* stm #12247,ar2 (calld delay slot, dead preset, noted) */
    sub_6976();                                    /* calld 0x6976 */
    a = b + 3;                                     /* add #3,b,a */
    a -= *par5;                                    /* sub *ar5,a */
    if (a > 0) {                                   /* bc 0x676a,agt */
        frag_676A();                               /* tail, dark */
        return;
    }
    *par5 = b & 0xFFFF;                            /* stl b,*ar5 */
    daram_save_restore();                          /* call 0x697f */
    ar2 = (int *)(long)0x53D;                      /* stm (delay slot: src) */
    daram_cell_store(ar2);                         /* calld 0x6987 */
    frag_676A();                                   /* b 0x676a tail */
}
