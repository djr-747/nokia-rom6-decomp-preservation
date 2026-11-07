/* ROM6 0x3779 SUB_3779A -- 14w fixed-count bitrev fill, one EXPECT.
 * Verified encoding: src/rom6/kernel/3779_sub_3779a.asm (recombine MATCH).
 * ORIGIN 0x3779
 * EXPECT: 7714 2BFE EC4F E5CA 76F8 058A 0000 69F8 0589 0002 F074 2E2F F073 2E64
 *
 * Intent: 80-word bit-reversed fill plus flag set into the dispatch loop.
 * AR4 = 11262 (stm); RPT #79 re-arms an 80-iteration MVDD
 * (RPT #k runs k + 1, 4EBC precedent): *AR4++ = *(AR2-bitrev++)
 * (mvdd *ar2+0%,*ar4+: source bit-reversed advance unmodelable, dest
 * plain -- AR2 position unknown after, noted); *(0x58A) = 0 (st);
 * *(0x589) |= 2 (orm). Then runs DISPATCHER_ENTRY_2E2F (call 0x2e2f);
 * tail-enters DISPATCH_MATCH_LOOP (b 0x2e64, bare extern per 361C).
 * Bound 3779-3786 (header-claimed 8w is stale: span is 14w per ROM slice
 * and recombine MATCH; the 3779 entry head with TRACE x2 lives here).
 */
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void sub_3779A(int *par2)
{
    int *par4 = (int *)11262;                        /* stm ar4 */
    int k;

    for (k = 0; k < 80; k++)                         /* rpt #79 + mvdd */
        *par4++ = *par2;         /* dest++; source brev-advance unmod. */
    *(volatile int *)0x58A = 0;                          /* st #0 */
    *(volatile int *)0x589 |= 2;                         /* orm #2 */
    /* AR2 live-out unknown (bitrev); AR4 = 11342 dead */
    dispatcher_entry_2E2F();                             /* call 0x2e2f */
    dispatch_match_loop();                               /* b 0x2e64 */
}
