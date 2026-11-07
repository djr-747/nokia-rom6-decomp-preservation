/* ROM6 0xB16C DISPATCH_B16C -- 11w.
 * Verified encoding: src/rom6/rf/b16c_dispatch_b16c.asm (recombine MATCH).
 * ORIGIN 0xB16C
 * EXPECT: F074 AF92 E900 4812 F000 B177 F030 FFFF 7EF8 000B F5E2
 *
 * Intent: RF dispatch/error-park head (same selector idiom as AFAB, with
 * the deliberate ld #0,b asymmetry). Runs pooled HELPER_AF92 (forward
 * extern void; fixed-cell reads only, no entry-AR dependency; may fall
 * through into AFAB per its xc-skip-ret, opaque inside the pooled
 * callee). B = 0 (ld #0,b). A = AR2 - 20105 masked to low16 (ldm ar2,a;
 * add #-20105,a; and #-1,a). reada *(0xb): Dmem[cell 0xB] <- Pmem[A]
 * (PAR <- A, no accumulator touched, same ground truth as AFAB). bacc b
 * with B == 0: PC := 0x0000, the page-0 word16 sled (PROG 0000-000F =
 * 16x 7C2A = MVPD_DIRECT self-write pair per the catalog row;
 * HYPOTHESIS: trap/halt sled, trace-confirmable).
 */
extern void sub_AF92(void);                          /* pooled; fixed cells only */
extern int prom_read_word(int prog_addr);            /* Pmem16 read for the reada pair leg */
extern void trap_sled_0000(void);                    /* bacc 0: PC := 0x0000 */

void dispatch_b16c(void)
{
    int ar2;                                         /* unbound: HELPER_AF92 AR2 residue */
    int a;
    int b;
    sub_AF92();                                      /* call 0xAF92 */
    b = 0;                                           /* ld #0,b */
    a = (ar2 - 20105) & 0xFFFF;                      /* ldm ar2,a; add #-20105,a; and #-1,a */
    *(volatile int *)0xB = prom_read_word(a);        /* reada *(0xb) */
    (void)b;                                         /* B == 0 here; consumed by the bacc below */
    trap_sled_0000();                                /* bacc b (B == 0 -> PC 0x0000) */
}
