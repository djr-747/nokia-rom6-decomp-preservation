/* ROM6 0x37C0 FRAG_37C0 -- 24w.
 * Verified encoding: src/rom6/kernel/37c0_frag_37c0.asm (recombine MATCH).
 * ORIGIN 0x37C0
 * EXPECT: F340 8000 68F8 0549 FFDF F495 75F8 000B 0002 F495 74F8 000B 0037 F330 FFEF F495 75F8 000B 0037 F6BB F074 2E2F F073 2E64
 *
 * Intent: Dual-port relay with unlock. B-live-in |= 0x8000 (or #-32768,b); clears bit 5 of cell 0x549 (andm #-33); BL out to port 2 (portw *(0xb),2: DATA 0xB aliases BL); BL = port 55 (portr 55,*(0xb)) AND -17 (clears bit 4) out to port 55; clears INTM (rsbx st1,intm, hardware state per 399e); calls dispatcher_entry_2E2F; tail-enters DISPATCH_MATCH_LOOP (b 0x2e64, forward extern). Only BL observed downstream, int model exact. Bound 37C0-37D7.
 */
extern int port_read_55(void);                                        /* HW port 55 (codec ctrl per 938c/37c0 spans); no ROM definition */
extern void port_write_55(int v);                                     /* HW port 55 (codec ctrl per 938c/37c0 spans); no ROM definition */
extern void port_write_2(int v);                                      /* HW port 2 (supervisor per 2875 precedent); no ROM definition */
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void frag_37C0(int b_live)
{
    int b;
    b = b_live | -32768;                         /* or #-32768,b */
    *(volatile int *)0x549 &= -33;           /* andm #-33,*(0x549) */
    /* nop */
    port_write_2(b);                             /* portw *(0xb),2 */
    /* nop */
    b = port_read_55();                          /* portr 55,*(0xb) */
    *(volatile int *)0xB = b;                /* BL alias write */
    b &= -17;                                    /* and #-17,b */
    /* nop */
    port_write_55(b);                            /* portw *(0xb),55 */
    /* rsbx st1,intm: INTM clear (hardware state, no C form) */
    dispatcher_entry_2E2F();                     /* call 0x2e2f */
    dispatch_match_loop();                       /* b 0x2e64 tail */
}
