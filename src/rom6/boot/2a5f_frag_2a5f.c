/* ROM6 0x2A5F FRAG_2A5F -- 20w.
 * Verified encoding: src/rom6/boot/2a5f_frag_2a5f.asm (recombine MATCH).
 * ORIGIN 0x2A5F
 * EXPECT: 6183 0200 F820 2AC0 76F8 13D0 0000 7712 0060 7682 3A98 F495 7582 0004 EC14 F495 7192 058E F073 2979
 *
 * Intent: Port 4 strobe plus stage. Bit 9 of *AR3-live-in set jumps away to dark 0x2AC0 (bc ntc, forward extern). Else clears cell 0x13D0; cell 96 = 15000 out to port 4 (portw *ar2,4); 21 idle cycles (rpt #20 nop); moves cell 96 to cell 0x58E (mvdk, AR2 steps to 97, dead after); tail-enters dark 0x2979 (b, forward extern). Bound 2A5F-2A72.
 */
extern void frag_2AC0(void); /* joins 2a8a_frag_2a73 interior @+0x36; see docs/evidence/extern-triage.md */
extern void port_write_4(int v);                                      /* HW port 4 (RF per 3cd2 port4850 seq); no ROM definition */
extern void frag_2979(void); /* joins 296a_frag_296a interior @+0xF; see docs/evidence/extern-triage.md */

void frag_2A5F(int *par3)
{
    int i;
    int cell96;
    if ((*par3 & 512) != 0) {                    /* bitf, bc ntc */
        frag_2AC0();                             /* away, dark */
        return;
    }
    *(volatile int *)0x13D0 = 0;             /* st #0 */
    /* stm #96,ar2 */
    cell96 = 15000;                              /* st #15000,*ar2 */
    /* nop */
    port_write_4(cell96);                        /* portw *ar2,4 */
    for (i = 0; i < 21; i++) {}                  /* rpt #20; nop */
    *(volatile int *)0x58E = cell96;         /* mvdk *ar2+,0x58e */
    frag_2979();                                 /* b 0x2979 tail */
}
