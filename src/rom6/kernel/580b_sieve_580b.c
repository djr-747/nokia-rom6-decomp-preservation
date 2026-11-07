/* ROM6 0x580B SIEVE_580B -- 24w.
 * Verified encoding: src/rom6/kernel/580b_sieve_580b.asm (recombine MATCH).
 * ORIGIN 0x580B
 * EXPECT: F074 059C 7713 000B 6083 001A F830 5821 6083 0051 F830 5821 F330 00F0 6083 0010 F830 5823 6083 0050 F830 5823 F4BC FC00
 *
 * Intent: Sieve with tail calls and TC clear. Runs 0x59C; AR3 = 11; cell == 26 or == 81 joins the own tail (bc 0x5821,tc lands on the rsbx plus ret at the span end, exact); B = live-in AND 240 (dead, cmpm is TC-only); cell != 16 tail-calls FRAG_5823 (C: frag_5823_tc_set); cell != 80 same; else clears TC (rsbx st0,tc, hardware state); return.
 */
extern void sub_059C(void);
extern void frag_5823_tc_set(void);

void sieve_580B(int b_live)
{
    int cell;
    sub_059C();                                  /* call 0x59c */
    cell = *(volatile int *)11;              /* stm #11,ar3 (address) */
    if (cell == 26 || cell == 81) {              /* cmpm, bc 0x5821,tc */
        /* taken: joins own tail (rsbx st0,tc; ret @5821) */
        return;
    }
    cell = b_live & 240;                        /* and #240,b */
    (void)cell;
    cell = *(volatile int *)11;              /* (AR3 unchanged) */
    if (cell != 16) {                            /* cmpm, bc tc */
        frag_5823_tc_set(); return;              /* tail */
    }
    if (cell != 80) {                            /* cmpm, bc tc */
        frag_5823_tc_set(); return;              /* tail */
    }
    /* rsbx st0,tc: TC clear (hardware state, no C form); ret */
}
