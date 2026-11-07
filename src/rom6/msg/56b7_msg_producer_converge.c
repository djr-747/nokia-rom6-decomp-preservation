/* ROM6 0x56B7 MSG_PRODUCER_CONVERGE -- 6w.
 * Verified encoding: src/rom6/msg/56b7_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x56B7
 * EXPECT: F074 56A2 E800 F074 56DE FC00
 *
 * Intent: Producer converge step. Runs worker 0x56A2, then the 0x56DE port-transaction entry with A = 0, returns.
 */
extern void msg_producer_converge_56A2(void);
extern void portxact_entry_56DE(int a_in);

void msg_producer_converge_56B7(void)
{
    msg_producer_converge_56A2();                                  /* call 0x56a2 */
    portxact_entry_56DE(0);                      /* ld #0,a; call 0x56de */
    /* ret */
}
