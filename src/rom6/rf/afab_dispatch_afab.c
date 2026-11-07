/* ROM6 0xAFAB DISPATCH_AFAB -- 10w.
 * Verified encoding: src/rom6/rf/afab_dispatch_afab.asm (recombine MATCH).
 * ORIGIN 0xAFAB
 * EXPECT: F074 B0F5 4812 F000 AFB5 F030 FFFF 7EF8 000B F5E2
 *
 * Intent: RF dispatch head (same selector idiom as B16C/AF57/B11C).
 * Runs pooled SUB_B0F5 (forward extern void; reads *AR3-entry, B/AR2
 * outs are path-dependent dark residues, carried as unbound locals).
 * A = AR2 - 20555 masked to low16 (ldm ar2,a; add #-20555,a;
 * and #-1,a with the and-#imm zero-extend rule). reada *(0xb):
 * Dmem[cell 0xB] <- Pmem[A] (PAR <- A; touches no accumulator per
 * ti-c54x op_reada + smem_program_pair prepare/commit ground truth,
 * corroborated by the emu READA/WRITA PAR-seed). B is untouched since
 * the call; bacc b dispatches via the B0F5 residue (dark target,
 * emulator/trace ground truth). The 10-word jtab AFB5-AFBE follows the
 * span (bytes verified in the .asm header).
 */
extern void sub_B0F5(void);                          /* pooled; *AR3-entry in, B/AR2 dark out */
extern int prom_read_word(int prog_addr);            /* Pmem16 read for the reada pair leg */
extern void dark_afab_target(int addr);              /* bacc b (B0F5 residue, dark) */

void dispatch_afab(int ar3_in)
{
    int ar2;                                         /* unbound: SUB_B0F5 AR2 residue */
    int a;
    int b;                                           /* unbound: SUB_B0F5 B residue */
    (void)ar3_in;                                    /* consumed inside pooled SUB_B0F5 (*AR3 read) */
    sub_B0F5();                                      /* call 0xB0F5 */
    a = (ar2 - 20555) & 0xFFFF;                      /* ldm ar2,a; add #-20555,a; and #-1,a */
    *(volatile int *)0xB = prom_read_word(a);        /* reada *(0xb) */
    dark_afab_target(b & 0xFFFF);                    /* bacc b */
}
