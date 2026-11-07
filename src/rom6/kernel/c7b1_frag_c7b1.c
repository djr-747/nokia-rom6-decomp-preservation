/* ROM6 0xC7B1 FRAG_C7B1 -- 56w init gate with masked-compare arm (DROM lane).
 * Verified encoding: src/rom6/kernel/c7b1_frag_c7b1.asm (recombine MATCH).
 * ORIGIN 0xC7B1
 * EXPECT: F074 05EC 76F8 0008 0200 F495 75F8 0008 0001 EC16 F495 74F8 0008 0035 76F8 20FA 0000 7717 20F6 7716 20F3 7715 20F4 7214 054A 6087 0000 F830 C7D2 7719 0278 F073 C7F6 6185 0400 F830 C7E9 6185 0200 F830 C7E2 F110 0002 F84D C8F8 F110 0102 F84D C8FE F130 0100 F84D C7F8 8086 F073 C878
 *
 * Intent: Runs dark SUB_05EC (call, forward extern, void per opaque-callee
 * convention). Cell(DP 8) = 512, kicked to port 1 (portw, extern op; reuse
 * of portw_alias08_port1), 22-nop settle (rpt #22 timing only). Cell(DP 8)
 * = port 53 (portr, extern op). Cell 0x20FA = 0. AR7/AR6/AR5 = 8438/8435/
 * 8436 (stm); AR4 = cell 0x54A (mvdm, dead in-span, noted). Cell 8438 != 0
 * (cmpm *ar7,#0, TC-only; bc ntc fall-through): BK = 632 (dead at tail,
 * noted) and tail-enters dark 0xC7F6 (b, forward extern void + return; the
 * C7F6 continuation lies past the C7E8 bound). Else (0xC7D2): bit 10 of
 * cell 8436 set terminal-calls FRAG_C7E9 with A-live-in (bc tc; C:
 * frag_C7E9(a_live, par5, par6) with (int *)8436/(int *)8435; never
 * returns -- its tails are C7F8/283D, so return after the call). Else bit 9
 * set rejoins 0xC7E2 (bc tc). Else B = A-live-in - 2 (sub #2,a,b, A kept):
 * B == 0 (A == 2) tail-enters dark FRAG_C8F8 (bc beq, forward extern void);
 * B = A - 258: B == 0 (A == 258) tail-enters dark FRAG_C8FE (forward extern
 * void); falls into 0xC7E2. At 0xC7E2: B = A-live-in & 256 (and #256,a,b):
 * B == 0 tail-enters dark FRAG_C7F8 (bc beq, forward extern void, shared
 * with the C7E9 arm); else cell 8436 = A-low (stl a,*ar6) and tail-enters
 * dark 0xC878 (b, forward extern void). A entry-live throughout (no in-span
 * A write). Bound C7B1-C7E8 (exit F073@C7E7->C878 + operand C7E8; abuts the
 * separate FRAG_C7E9 span at C7E9 with zero overlap).
 */
extern void sub_05EC(void);
extern void portw_alias08_port1(void);
extern void portr_port53_cell08(void);
extern void frag_C7F6(void);
extern void frag_C7E9(int a_live, int *par5, int *par6);
extern void frag_C8F8(void);
extern void frag_C8FE(void);
extern void frag_C7F8(void);
extern void frag_C878(void);

void frag_C7B1(int a_live)
{
    sub_05EC();                                        /* call 0x5ec */
    *(volatile int *)0x8 = 512;                        /* st #512,*(0x8) */
    /* nop */
    portw_alias08_port1();                             /* portw *(0x8),1 */
    /* rpt #22 + nop: 22-cycle settle (timing only) */
    portr_port53_cell08();                             /* portr 53,*(0x8) */
    *(volatile int *)0x20FA = 0;                       /* st #0,*(0x20fa) */
    /* stm AR7/AR6/AR5 = 8438/8435/8436; AR4 = cell 0x54A (dead, noted) */
    if (*(volatile int *)8438 != 0) {                  /* cmpm; bc c7d2,ntc */
        /* stm #632,bk (dead post-tail preset, not modeled) */
        frag_C7F6();                                   /* b 0xc7f6 tail */
        return;
    }
    /* 0xc7d2: bitf *ar5,#1024 (cell 8436) */
    if (*(volatile int *)8436 & 1024) {                /* bc 0xc7e9,tc */
        frag_C7E9(a_live, (int *)8436, (int *)8435);   /* terminal arm */
        return;
    }
    if ((*(volatile int *)8436 & 512) == 0) {          /* bc 0xc7e2,tc */
        long b = (long)a_live - 2L;                    /* sub #2,a,b */
        if (b == 0) {                                  /* bc 0xc8f8,beq */
            frag_C8F8();
            return;
        }
        b = (long)a_live - 258L;                       /* sub #258,a,b */
        if (b == 0) {                                  /* bc 0xc8fe,beq */
            frag_C8FE();
            return;
        }
    }
    /* 0xc7e2: and #256,a,b */
    if (((long)a_live & 256L) == 0) {                  /* bc 0xc7f8,beq */
        frag_C7F8();
        return;
    }
    *(volatile int *)8436 = a_live & 0xFFFF;           /* stl a,*ar6 */
    frag_C878();                                       /* b 0xc878 tail */
}
