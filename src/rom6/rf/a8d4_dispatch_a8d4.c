/* ROM6 0xA8D4 DISPATCH_A8D4 -- 42w.
 * Verified encoding: src/rom6/rf/a8d4_dispatch_a8d4.asm (recombine MATCH).
 * ORIGIN 0xA8D4
 * EXPECT: F074 0666 61F8 051C 0040 F830 A8FD 61F8 2B08 0003 F820 A8F9 76F8 337D 3236 70F8 337B 054A E89F F074 B750 F074 9FCF 76F8 337C 3236 F074 C5F9 61F8 0577 1000 FB30 BCFC 7711 3236 F074 A109 F274 AB78 7712 3236 FC00
 *
 * Intent: RF dispatch driver (caller AFEC). Runs dark SUB_0666 (no
 * symbol, opaque). TC = (*(0x51C) & 64) != 0 (bitf, 5d38 polarity);
 * set returns (bc 0xa8fd,tc to the ret word). TC = (*(0x2B08) & 3)
 * != 0; clear skips the A109 call (bc 0xa8f9,ntc lands on the
 * calld word). MEM[0x337D] = 12854 (st); MEM[0x337B] = MEM[0x54A]
 * (mvkd dmad->Smem per the 3d79 precedent). A = 159 (ld; for the
 * pooled B750 call, opaque -- local, flagged). Runs pooled
 * SUB_B750 (forward extern void sub_B750, address-based per the
 * 9453 precedent; no file, symbol FILL112_RPTBD_B750) then pooled
 * SUB_9FCF (forward extern void sub_9FCF). MEM[0x337C] = 12854
 * (st). Runs pooled CONFIG_DISPATCH_C5F9 (forward extern void
 * config_dispatch_C5F9). TC = (*(0x577) & 4096) != 0 (bitf). ccd
 * 0xbcfc,tc: the 2-word stm (AR1 = 12854 local, dies at ret --
 * caller-observable, not carried) fills the window and always runs
 * (520C word-count rule); TC-taken calls pooled FRAME_DISPATCH_BCFC
 * (forward extern void frame_dispatch_BCFC, returns, then joins).
 * Fall path same join. Runs linked AUDIO_SELECT_A109 (C:
 * audio_select_A109; AR1 dead across, noted). calld 0xab78 with
 * delay stm AR2 = 12854 first (delay runs before the call):
 * leaf_AB78(&ar2-local) (linked C; AR2 writeback to the local,
 * carried out via ppar2 -- AR2-entry never read in-span, write-only
 * out-param). return (ret). A = 159 dead after the B750 call; B
 * never used (rides); void, dark outs flagged.
 */
extern void sub_0666(void);                          /* dark, no symbol */
extern void sub_B750(void);                          /* pooled (9453 precedent) */
extern void sub_9FCF(void);                          /* asm-only, forward extern */
extern void config_dispatch_C5F9(void);              /* asm-only, forward extern */
extern void frame_dispatch_BCFC(void);               /* asm-only, forward extern */
extern void audio_select_A109(void);                 /* linked C */
extern void leaf_AB78(int **ppar2);                  /* linked C */

void frag_A8D4(int **ppar2)
{
    long a = 159;                                    /* ld #159,a (B750 call setup) */
    int *ar1;
    int *ar2;
    (void)a;
    sub_0666();                                      /* call 0x666 */
    if ((*(volatile int *)0x51C & 64) != 0)          /* bitf; bc 0xa8fd,tc */
        return;
    if ((*(volatile int *)0x2B08 & 3) == 0)          /* bitf; bc 0xa8f9,ntc */
        goto la8f9;
    *(volatile int *)0x337D = 12854;                 /* st #12854,*(0x337d) */
    *(volatile int *)0x337B = *(volatile int *)0x54A; /* mvkd 0x54a,*(0x337b) */
    sub_B750();                                      /* call 0xb750 */
    sub_9FCF();                                      /* call 0x9fcf */
    *(volatile int *)0x337C = 12854;                 /* st #12854,*(0x337c) */
    config_dispatch_C5F9();                           /* call 0xc5f9 */
    ar1 = (int *)(long)12854;                        /* ccd delay: stm (always) */
    (void)ar1;                                       /* AR1 dead after (not carried) */
    if ((*(volatile int *)0x577 & 4096) != 0)        /* bitf; ccd 0xbcfc,tc */
        frame_dispatch_BCFC();                       /* taken call (returns, joins) */
    audio_select_A109();                             /* call 0xa109 */
la8f9:
    ar2 = (int *)(long)12854;                        /* calld delay: stm (runs first) */
    leaf_AB78(&ar2);                                 /* calld 0xab78 */
    *ppar2 = ar2;                                    /* AR2-out (leaf-advanced) */
}
