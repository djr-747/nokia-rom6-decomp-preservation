/* ROM6 0x82B7 TRAMP_82B7 -- 20w.
 * Verified encoding: src/rom6/kernel/82b7_tramp_82b7.asm (recombine MATCH).
 * ORIGIN 0x82B7
 * EXPECT: F074 066E 7712 2A84 61F8 264F 0001 FA30 82CB 7710 2A8C F274 82D4 7716 DCFA F274 82FF 7716 DCFA FC00
 *
 * Intent: Conditional dispatch trampoline. Runs dark 0x66E (forward extern);
 * AR2 = 10884; TC = bit 0 of cell 0x264F (bitf any-bit TC per ti-c54x
 * op_bitf; a109 precedent); bcd 0x82CB,tc taken tail-calls the 82CB twin
 * launcher (82CB returns to our caller, flagged) with delay AR0 = 10892
 * always run first; else AR6 = -8966, calld 0x82D4 (delay runs first),
 * AR6 = -8966, calld 0x82FF, return. AR0/AR2/AR6 presets feed dark callees
 * (file-static globals, 82cb.c G_AR6 precedent, flagged). A/B untouched.
 * Exterior caller call @81CD (810A gap region, objdump-verified), flagged.
 */
extern void sub_066E(void);
extern void sub_82CB(void);
extern void sub_82D4(void);
extern void sub_82FF(void);

static int *G_AR0;
static int *G_AR2;
static int *G_AR6;

void tramp_82B7(void)
{
    int taken;

    sub_066E();                                            /* call 0x66e */
    G_AR2 = (int *)10884;                                  /* stm #10884,ar2 */
    taken = (*(volatile int *)0x264F & 1) != 0;            /* bitf; bcd tc */
    G_AR0 = (int *)10892;                                  /* bcd delay (always runs) */
    if (taken) {                                           /* bcd taken: tail to 82CB */
        sub_82CB();
        return;
    }
    G_AR6 = (int *)-8966;                                  /* calld delay */
    sub_82D4();                                            /* calld 0x82d4 */
    G_AR6 = (int *)-8966;                                  /* calld delay */
    sub_82FF();                                            /* calld 0x82ff */
    /* ret */
    (void)G_AR0; (void)G_AR2; (void)G_AR6;
}
