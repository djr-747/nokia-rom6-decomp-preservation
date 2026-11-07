/* ROM6 0x2B53 COBBA_CMD_ISR_ENTRY -- 1w.
 * Verified encoding: src/rom6/boot/2b53_cobba_cmd_isr_entry.asm (recombine MATCH).
 * ORIGIN 0x2B53
 * EXPECT: 4A07
 *
 * Intent: V25 HPI-word request ISR entry (runtime IVT V25 FB 0x2B53 per
 * roms/rom6/ivt.md; mask vector FFE4 fb 0x2B53 in kernel/ffc0_vectors_ffc0.asm).
 * Single-word head: PSHM ST1 (caller-live, comment only per 2D5E precedent);
 * falls into the 2B54 ISR body (abuts at 0x2B54, owned by
 * boot/2b54_isr_ctxsave_2b54.asm).
 */
void cobba_cmd_2B53(void)
{
    /* pshm st1 (caller-live, comment only) */
    /* falls into 2b54_isr_ctxsave (abuts at 0x2B54) */
}
