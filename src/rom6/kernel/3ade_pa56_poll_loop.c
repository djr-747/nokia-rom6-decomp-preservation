/* ROM6 0x3ADE PA56_POLL_LOOP -- 15w.
 * Verified encoding: src/rom6/kernel/3ade_pa56_poll_loop.asm (recombine MATCH).
 * ORIGIN 0x3ADE
 * EXPECT: F074 0632 74F8 0008 0038 F030 0080 F844 3ADE 74F8 0008 0038 F030 0060 FC00
 *
 * Intent: PA56 ready-poll plus mask. Runs 0x632; polls port 56 into AL (portr 56,*(0x8): DATA 0x8 aliases AL) until bit 7 clears (and #128,a; bc 0x3ade,aneq self-loop); then A = fresh port 56 masked to bits 5-6 (and #96,a), return it.
 */
extern void sub_0632(void);
extern int port_read_56(void);

int pa56_poll_loop_3ADE(void)
{
    int a;
    sub_0632();                                  /* call 0x632 */
    do {
        a = port_read_56();                      /* portr (AL alias) */
        *(volatile int *)0x8 = a;
        a &= 128;                                /* and #128,a */
    } while (a != 0);                            /* bc 0x3ade,aneq */
    a = port_read_56();                          /* portr 56,*(0x8) */
    *(volatile int *)0x8 = a;
    return a & 96;                               /* and #96,a; ret */
}
