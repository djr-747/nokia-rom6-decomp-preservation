/* ROM6 0xB11C DISPATCH_B11C -- 13w.
 * Verified encoding: src/rom6/rf/b11c_dispatch_b11c.asm (recombine MATCH).
 * ORIGIN 0xB11C
 * EXPECT: F074 0686 F074 AF92 E900 4812 F000 B129 F030 FFFF 7EF8 000B F5E2
 *
 * Intent: RF dispatch park head (b16c family). Runs dark SUB_0686 then
 * pooled HELPER_AF92 (fixed-cell reads only, no entry-AR dependency;
 * may fall through into AFAB per its xc-skip-ret, opaque inside the
 * pooled callee). B = 0 (ld #0,b -- deliberate, the AFAB asymmetry).
 * A = AR2 - 20183 masked to low16 (ldm ar2,a; add #-20183,a;
 * and #-1,a; selects the table at B129 per the .asm header).
 * reada *(0xb): Dmem[cell 0xB] <- Pmem[A] (PAR <- A, AFAB ground
 * truth). bacc b with B == 0: PC := 0x0000, the page-0 trap sled
 * (B16C ground truth).
 */
extern void sub_0686(void);                          /* dark, no symbol */
extern void sub_AF92(void);                          /* pooled; fixed cells only */
extern int prom_read_word(int prog_addr);            /* Pmem16 read for the reada pair leg */
extern void trap_sled_0000(void);                    /* bacc 0: PC := 0x0000 */

void dispatch_b11c(void)
{
    int ar2;                                         /* unbound: HELPER_AF92 AR2 residue */
    int a;
    int b;
    sub_0686();                                      /* call 0x686 */
    sub_AF92();                                      /* call 0xaf92 */
    b = 0;                                           /* ld #0,b */
    a = (ar2 - 20183) & 0xFFFF;                      /* ldm ar2,a; add #-20183,a; and #-1,a */
    *(volatile int *)0xB = prom_read_word(a);        /* reada *(0xb) */
    (void)b;                                         /* B == 0 here; consumed by the bacc below */
    trap_sled_0000();                                /* bacc b (B == 0 -> PC 0x0000) */
}
