/* ROM6 0x3FFA ROUTINE_3FFA -- 13w.
 * Verified encoding: src/rom6/kernel/3ffa_routine_3ffa.asm (recombine MATCH).
 * ORIGIN 0x3FFA
 * EXPECT: F074 064A F495 75F8 0009 0018 4EF8 01FE F495 75F8 0008 0019 FC00
 *
 * Intent: Port snapshot plus double store. Runs 0x64A (A live after, modeled as live-in); PORT[24] = A-high (portw *(0x9),24: DATA 0x9 aliases AH); 32-bit A to cells 0x1FE/0x1FF (dst a: LONG32 store per ti-c54x op_dst, guard bits dropped); PORT[25] = A-low (portw *(0x8),25: AL alias); return.
 */
extern void sub_064A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void port_write_24(int v);                                     /* HW port 24 (per 3ffa span); no ROM definition */
extern void port_write_25(int v);                                     /* HW port 25 (per 3ffa span); no ROM definition */

void routine_3FFA(int a_live)
{
    sub_064A();                                  /* call 0x64a */
    port_write_24((a_live >> 16) & 0xFFFF);      /* portw *(0x9),24 (AH) */
    *(volatile long *)0x1FE = (long)a_live;    /* dst a,*(0x1fe) */
    port_write_25(a_live & 0xFFFF);              /* portw *(0x8),25 (AL) */
    /* ret */
}
