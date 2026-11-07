/* ROM6 0x2A0E FRAG_2A0E -- 14w.
 * Verified encoding: src/rom6/boot/2a0e_frag_2a0e.asm (recombine MATCH).
 * ORIGIN 0x2A0E
 * EXPECT: 6183 0010 F820 2A1C F020 3A98 F495 75F8 0008 0004 EC0E F495 F073 2AC0
 *
 * Intent: Port 4 strobe. Bit 4 of *AR3-live-in set jumps away to FRAG_2A1C (bc 0x2a1c,ntc: has .asm, no C yet, forward extern). Else A = 15000 out to port 4 (portw *(0x8),4: AL alias, value direct), 15 idle cycles (rpt #14 nop), tail-enters dark 0x2AC0 (b, forward extern). Bound 2A0E-2A1B.
 */
extern void frag_2A1C(void);
extern void port_write_4(int v);                                      /* HW port 4 (RF per 3cd2 port4850 seq); no ROM definition */
extern void frag_2AC0(void); /* joins 2a8a_frag_2a73 interior @+0x36; see docs/evidence/extern-triage.md */

void frag_2A0E(int *par3)
{
    int i;
    if ((*par3 & 16) != 0) {                     /* bitf, bc ntc */
        frag_2A1C();                             /* away, unbound C */
        return;
    }
    /* ld #15000,a (AL alias, value direct) */
    /* nop */
    port_write_4(15000);                         /* portw *(0x8),4 */
    for (i = 0; i < 15; i++) {}                  /* rpt #14; nop */
    frag_2AC0();                                 /* b 0x2ac0 tail */
}
