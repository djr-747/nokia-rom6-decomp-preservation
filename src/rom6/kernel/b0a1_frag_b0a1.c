/* ROM6 0xB0A1 FRAG_B0A1 -- 28w.
 * Verified encoding: src/rom6/kernel/b0a1_frag_b0a1.asm (recombine MATCH).
 * ORIGIN 0xB0A1
 * EXPECT: 7714 09C8 FB81 A8FD 7713 2F2A F981 A260 F074 A679 F074 A5E1 60F8 2510 00C0 F820 B0B8 10F8 2EFE F844 B0B8 F981 80A7 F074 A7B7 F074 A7EB FC00
 *
 * Intent: Far-call chain with shared tail. AR4 = 2504 feeds far call 0x1A8FD (fcalld, AR3 = 12074 preset in the delay slot, always executes), then far call 0x1A260, 0xA679, the 0xA5E1 measure setup (C: meas_setup_A_A5E1); cell 0x2510 != 192 jumps to the shared B0B8 tail (bc ntc: bytes call 0xa7b7, call 0xa7eb, ret). Else A = cell 0x2EFE, nonzero jumps there too (bc aneq); else far call 0x180A7 first. Fall-through runs the audio workers 0xA7B7 and 0xA7EB (C: audio_B_A7EB for the latter); return.
 */
extern void far_1A8FD(void);
extern void far_1A260(void);
extern void sub_A679(void);
extern void meas_setup_A_A5E1(void);
extern void far_180A7(void);
extern void audio_A_A7B7(void);
extern void audio_B_A7EB(void);

static int *G_AR3;
static int *G_AR4;

void frag_B0A1(void)
{
    int a;
    G_AR4 = (int *)2504;                         /* stm #2504,ar4 */
    G_AR3 = (int *)12074;                        /* fcalld delay slot */
    far_1A8FD();                                 /* fcalld 0x1a8fd */
    far_1A260();                                 /* fcall 0x1a260 */
    sub_A679();                                  /* call 0xa679 */
    meas_setup_A_A5E1();                         /* call 0xa5e1 */
    if (*(volatile int *)0x2510 != 192)          /* cmpm, bc ntc */
        goto L_TAIL;
    a = *(volatile int *)0x2EFE;             /* ld */
    if (a != 0)                                  /* bc aneq */
        goto L_TAIL;
    far_180A7();                                 /* fcall 0x180a7 */
L_TAIL:
    audio_A_A7B7();                              /* B0B8 shared tail */
    audio_B_A7EB();                              /* call 0xa7eb; ret */
}
