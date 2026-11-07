/* ROM6 0xA249 MSG_DISPATCH_A249 -- 12w.
 * Verified encoding: src/rom6/msg/a249_msg_dispatch_a249.asm (recombine MATCH).
 * ORIGIN 0xA249
 * EXPECT: F074 068E E900 10F8 0574 F000 A255 F030 FFFF 7EF8 000B F5E2
 *
 * Intent: Message-dispatch park head (b16c/af57/b11c family). Runs dark
 * SUB_068E (forward extern void; no symbol, opaque). B = 0 (ld #0,b --
 * deliberate). A = *(0x574) - 23979 masked to low16 (ld *(0x574),a;
 * add #-23979,a; and #-1,a; cell 0x574 in [0,4] selects table A255-A259
 * per the .asm header). reada *(0xb): Dmem[cell 0xB] <- Pmem[A]
 * (PAR <- A, no accumulator touched, AFAB ground truth). bacc b with
 * B == 0: PC := 0x0000, the page-0 trap sled (B16C ground truth).
 */
extern void sub_068E(void);                          /* dark, no symbol */
extern int prom_read_word(int prog_addr);            /* Pmem16 read for the reada pair leg */
extern void trap_sled_0000(void);                    /* bacc 0: PC := 0x0000 */

void dispatch_a249(void)
{
    int a;
    int b;
    sub_068E();                                      /* call 0x68e */
    b = 0;                                           /* ld #0,b */
    a = (*(volatile int *)0x574 - 23979) & 0xFFFF;   /* ld *(0x574),a; add #-23979,a; and #-1,a */
    *(volatile int *)0xB = prom_read_word(a);        /* reada *(0xb) */
    (void)b;                                         /* B == 0 here; consumed by the bacc below */
    trap_sled_0000();                                /* bacc b (B == 0 -> PC 0x0000) */
}
