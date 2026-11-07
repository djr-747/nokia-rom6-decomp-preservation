/* ROM6 0x33D8 FRAG_33D8 -- 16w flag-set bitrev copy, one EXPECT.
 * Verified encoding: src/rom6/kernel/33d8_frag_33d8.asm (recombine MATCH).
 * ORIGIN 0x33D8
 * EXPECT: 69F8 054F 0040 7713 2A86 EC27 E5C9 6983 FFFF 76F8 2A84 2A86 F074 2E2F F073 2E64
 *
 * Intent: Flag-set 40-word bit-reversed copy into the dispatch loop.
 * Post-RET head (thin: AR2 = source). *(0x54F) |= 64 (orm);
 * AR3 = 10886 (stm); RPT #39 re-arms a 40-iteration MVDD
 * (RPT #k runs k + 1): *AR3++ = *(AR2-bitrev++) (source advance
 * unmodelable, dest plain); *(AR3-end) |= 0xFFFF (orm #-1,*ar3: AR3
 * has advanced 40 past the block, so the mask lands just past it);
 * *(0x2A84) = 10886 (st). Then runs DISPATCHER_ENTRY_2E2F (call 0x2e2f);
 * tail-enters DISPATCH_MATCH_LOOP (b 0x2e64, bare extern per 361C).
 * Bound 33D8-33E7.
 */
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void frag_33D8(int *par2)
{
    int *par3 = (int *)10886;                        /* stm ar3 */
    int k;

    *(volatile int *)0x54F |= 64;                        /* orm #64 */
    for (k = 0; k < 40; k++)                         /* rpt #39 + mvdd */
        *par3++ = *par2;         /* dest++; source brev-advance unmod. */
    *par3 |= 0xFFFF;                             /* orm #-1,*ar3 */
    *(volatile int *)0x2A84 = 10886;                     /* st */
    /* AR2 live-out unknown (bitrev) */
    dispatcher_entry_2E2F();                             /* call 0x2e2f */
    dispatch_match_loop();                               /* b 0x2e64 */
}
