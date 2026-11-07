/* ROM6 0x4BA8 SUB_4BA8 -- 47w A-gated fill plus call chain.
 * Verified encoding: src/rom6/kernel/4ba8_sub_4ba8.asm (recombine MATCH).
 * ORIGIN 0x4BA8
 * EXPECT: F074 059C 80F8 2F1F 81F8 2F1E F110 0040 F84C 4BD7 7712 0080 7713 2F80 EC4D E589 F274 9268 7713 2F82 ED17 F274 4D9D 771A 0002 F274 4F3A 6882 007F F274 4EE0 771A 0001 F074 51D8 F84C 4D9C 7715 000E 7714 0080 F274 2C88 7713 2F5B F073 4D9C
 *
 * Intent: Runs dark SUB_059C (call, void per 4EE0/4FF6). Cells 0x2F1F/
 * 0x2F1E = A/B-live-in low (stl pair). B = A - 64 (sub, A kept); B != 0
 * tail-enters the 0x4BD7 fill (bc bneq; C: fill_2F5D_4BD7 with entry
 * AR3/AR7 unbound in this frame, flagged). Else AR2 = 128, AR3 = 12160;
 * 78 DARAM moves *AR3++ = *AR2++ (rpt #77 + mvdd; cursors to 206/12238).
 * Runs SUB_9268 with AR3 = 12162 (calld; C: sub_9268(par3); delay-slot stm
 * is callee-visible pre-branch state per 836D, so the callee stores to
 * *12162, overwriting one fill word -- transcribed literally). ASM = -9
 * (ld #-9,asm: shift-mode control, no C form, noted as unmodeled machine
 * state for the cl500 pass). Runs SUB_4D9D (calld, C: sub_4D9D(2, -9);
 * delay BRC = 2 and ASM = -9 ride in as constants). Masks *(AR2 = 206)
 * &= 127 (andm: calld delay slot,
 * executes before the callee). Runs opaque SUB_4F3A (calld, void; has
 * .asm with rptb, unmodelable) then SUB_4EE0 (calld, C: sub_4EE0(1);
 * delay BRC = 1 rides in as a constant) then dark SUB_51D8 (call, void).
 * B rides A - 64 = 0
 * through the void chain per the callee-preservation convention, so the
 * 0x4D9C retest (bc bneq) falls through in the model -- noted as
 * trace-oracle confirmable (any callee B-out would take the dark tail).
 * AR5 = 14, AR4 = 128; runs ROUTINE_2C88 (calld, void per 423B, delay AR3
 * = 12123 rides in) and tail-enters dark 0x4D9C (b, forward extern void).
 * A/B entry-live; AR cursors dead at the tail. Bound 4BA8-4BD6.
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void fill_2F5D_4BD7(long a_live_in, int *ar3_in, int ar7_in);
extern void sub_9268(int *par3);
extern void sub_4D9D(int brc_live, int asm_live);
extern void sub_4F3A(void);
extern void sub_4EE0(int brc_live_in);
extern void frag_51D8(void);
extern void routine_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */
extern void frag_4D9C(void); /* joins 4cb4_frag_4cb4 interior @+0xE8; see docs/evidence/extern-triage.md */

void sub_4BA8(int a_live, int b_live)
{
    long b = (long)a_live - 64L;                   /* sub #64,a,b */
    int *par2;
    int *par3;
    int *ar3_unbound;
    int ar7_unbound;
    int i;

    sub_059C();                                        /* call 0x59c */
    *(volatile int *)0x2F1F = a_live & 0xFFFF;         /* stl a */
    *(volatile int *)0x2F1E = b_live & 0xFFFF;         /* stl b */
    if (b != 0) {                                      /* bc 0x4bd7,bneq */
        /* AR3/AR7 = entry registers (untouched on this path): unbound
           in this (a,b) frame (b_dark-class convention, flagged). */
        fill_2F5D_4BD7((long)a_live, ar3_unbound, ar7_unbound);
        return;
    }
    par2 = (int *)128;                                 /* stm #128,ar2 */
    par3 = (int *)12160;                               /* stm #12160,ar3 */
    for (i = 0; i < 78; i++)                           /* rpt #77 + mvdd */
        *par3++ = *par2++;
    /* calld 0x9268 (delay AR3 = 12162, callee-visible) */
    sub_9268((int *)12162);
    /* ld #-9,asm (shift-mode control, unmodeled, noted) */
    /* calld 0x4d9d (delay BRC = 2 rides in; asm = -9 from ld above) */
    sub_4D9D(2, -9);
    /* andm #127,*(206): calld delay slot, runs before the callee */
    *(volatile int *)206 &= 127;
    /* calld 0x4f3a */
    sub_4F3A();
    /* calld 0x4ee0 (delay BRC = 1 rides in) */
    sub_4EE0(1);
    /* call 0x51d8 */
    frag_51D8();
    if (b != 0) {                                      /* bc 0x4d9c,bneq */
        frag_4D9C();                                   /* (dead in model) */
        return;
    }
    /* stm #14,ar5; stm #128,ar4 (dead post presets, not modeled) */
    /* calld 0x2c88 (delay AR3 = 12123 rides in, noted) */
    routine_2C88();
    /* stm #12123,ar2 (dead post-tail preset, not modeled) */
    frag_4D9C();                                       /* b 0x4d9c tail */
}
