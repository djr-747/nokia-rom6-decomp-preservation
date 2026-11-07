/* ROM6 0x40A1 PORT45_POLL_40A1 -- 27w.
 * Verified encoding: src/rom6/kernel/40a1_port45_poll.asm (recombine MATCH).
 * ORIGIN 0x40A1
 * EXPECT: F074 0652 74F8 0009 002D F063 1000 F844 40A3 F340 0010 F495 75F8 000B 002C EC0E F495 F073 40B4 74F8 0008 002D F130 1000 F84C 40B4 FC00
 *
 * Intent: Port 45 ready-poll plus port 44 strobe. Runs 0x652; re-reads port 45 into AH (portr 45,*(0x9): DATA 0x9 aliases AH) until high bit 12 clears (and #4096,16,a places the constant at A-high; bc 0x40a3,aneq self-loop). Then B-live-in OR 16 out to port 44 (portw *(0xb),44: DATA 0xB aliases BL), 15 idle cycles (rpt #14 nop), and re-reads port 45 into AL (portr 45,*(0x8): DATA 0x8 aliases AL) until low bit 12 clears (and #4096,a,b; bc 0x40b4,bneq self-loop); return. Bound 40A1-40BB.
 */
extern void sub_0652(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern int port_read_45(void);                                        /* HW port 45 (port-45 poll per 40A1 span); no ROM definition */
extern void port_write_44(int v);                                     /* HW port 44 (port-45 poll family per 40A1 span); no ROM definition */

void port45_poll_40A1(int b_live)
{
    int ah;
    int b;
    int i;
    sub_0652();                                  /* call 0x652 */
    do {                                         /* bc 0x40a3,aneq */
        ah = port_read_45();                     /* portr 45,*(0x9) */
        *(volatile int *)0x9 = ah;           /* AH alias write */
    } while ((ah & 4096) != 0);                  /* and #4096,16,a */
    b = b_live | 16;                             /* or #16,b */
    /* nop */
    port_write_44(b);                            /* portw *(0xb),44 */
    for (i = 0; i < 15; i++) {}                  /* rpt #14; nop */
    /* b 0x40b4 */
    do {
        int al = port_read_45();                 /* portr 45,*(0x8) */
        *(volatile int *)0x8 = al;           /* AL alias write */
        b = al & 4096;                          /* and #4096,a,b */
    } while (b != 0);                            /* bc 0x40b4,bneq */
    /* ret */
}
