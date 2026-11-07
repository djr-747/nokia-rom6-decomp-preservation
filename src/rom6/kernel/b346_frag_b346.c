/* ROM6 0xB346 FRAG_B346 -- 18w.
 * Verified encoding: src/rom6/kernel/b346_frag_b346.asm (recombine MATCH).
 * ORIGIN 0xB346
 * EXPECT: F074 A2C3 F074 A361 FC44 F074 A4DE F074 A482 F074 A5E1 F074 A679 F074 A7B7 F074 A7EB FC00
 *
 * Intent: Straight worker chain. Runs 0xA2C3 then 0xA361; nonzero A361 result runs 0xA4DE (rc aneq skips only that call); then 0xA482, the 0xA5E1 measure setup, 0xA679, and audio workers 0xA7B7/0xA7EB, return.
 */
extern void msg_worker_A2C3(void);
extern int sub_A361(void);
extern void msg_setup_C_A4DE(void);
extern void msg_setup_A_A482(void);
extern void meas_setup_A_A5E1(void);
extern void sub_A679(void);
extern void audio_A_A7B7(void);
extern void audio_B_A7EB(void);

void frag_B346(void)
{
    msg_worker_A2C3();                           /* call 0xa2c3 */
    if (sub_A361() != 0)                         /* call 0xa361; rc aneq */
        msg_setup_C_A4DE();                      /* call 0xa4de */
    msg_setup_A_A482();                          /* call 0xa482 */
    meas_setup_A_A5E1();                         /* call 0xa5e1 */
    sub_A679();                                  /* call 0xa679 */
    audio_A_A7B7();                              /* call 0xa7b7 */
    audio_B_A7EB();                              /* call 0xa7eb */
    /* ret */
}
