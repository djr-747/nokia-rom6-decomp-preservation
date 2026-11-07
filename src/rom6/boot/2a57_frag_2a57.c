/* ROM6 0x2A57 FRAG_2A57 -- 8w.
 * Verified encoding: src/rom6/boot/2a57_frag_2a57.asm (recombine MATCH).
 * ORIGIN 0x2A57
 * EXPECT: 6183 0080 F820 2A5F 7683 0000 F073 2993
 *
 * Intent: Clear gate. Bit 7 of *AR3-live-in set tail-enters FRAG_2A5F (bc 0x2a5f,ntc, C: frag_2A5F). Else clears *AR3, tail-enters dark 0x2993 (b, forward extern). Bound 2A57-2A5E.
 */
extern void frag_2A5F(void);
extern void frag_2993(void); /* joins 2983_frag_2983 interior @+0x10; see docs/evidence/extern-triage.md */

void frag_2A57(int *par3)
{
    if ((*par3 & 128) != 0) {                    /* bitf, bc ntc */
        frag_2A5F();                             /* tail call */
        return;
    }
    *par3 = 0;                                   /* st #0,*ar3 */
    frag_2993();                                 /* b 0x2993 tail */
}
