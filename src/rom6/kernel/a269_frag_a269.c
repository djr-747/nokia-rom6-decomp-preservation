/* ROM6 0xA269 FRAG_A269 -- 67w.
 * Verified encoding: src/rom6/kernel/a269_frag_a269.asm (recombine MATCH).
 * ORIGIN 0xA269
 * EXPECT: F074 A2C3 F074 A3A3 FC4C 71F8 022D 265B F074 A3F0 F074 A5C6 11F8 2615 F310 0D48 F84B A281 F074 A4DE F074 A482 F073 A291 F074 A482 11F8 262C F84D A28F 11F8 2615 F310 0320 F84B A28F F074 E64C F074 A4DE F274 A2B9 7715 DDAD 11F8 262C FA4D A2A9 7715 DDB3 11F8 2615 F310 0320 F84B A2A9 11F8 2615 F310 0D48 F84A A2A9 7715 DDB4 F074 A2B9 FC00
 *
 * Intent: identity dispatcher. Worker calls, then a conditioned
 * cell move (rc bneq: copy 0x22D to 0x265B when B nonzero).
 * Measure cell 0x2615 against 3400: below goes the A281 arm (call
 * A482, optional E64C call via the 0x262C-zero / 0x2615-800 gates),
 * else A482 then join at A291. The A291 tail runs the A2B9
 * table-walker primitive (AR5 preset -8787 in the calld delay
 * slot), then picks the final AR5 preset (-8781/-8780) through the
 * 0x262C-zero and 0x2615-800/3400 compare gates, and calls A2B9
 * once more before returning.
 */
extern void msg_worker_A2C3(void);
extern void sub_A3A3(void);
extern void sub_A3F0(void);
extern void sub_A5C6(void);
extern void msg_setup_C_A4DE(void);
extern void msg_setup_A_A482(void);
extern void sub_E64C(void);
extern void msg_primitive_A2B9(int ***ppp5);

static int *G_AR5;

void frag_A269(int b_in, int ***ppp5)
{
    int b = b_in;
    msg_worker_A2C3();                            /* call 0xa2c3 */
    sub_A3A3();                                   /* call 0xa3a3 */
    if (b != 0)                                   /* rc bneq */
        *(volatile int *)0x265B =
            *(volatile int *)0x22D;              /* mvdk */
    sub_A3F0();                                   /* call 0xa3f0 */
    sub_A5C6();                                   /* call 0xa5c6 */
    if ((*(volatile int *)0x2615 - 3400) < 0)     /* ld, sub, bc blt */
        goto L_A281;
    msg_setup_C_A4DE();                           /* call 0xa4de */
    msg_setup_A_A482();                           /* call 0xa482 */
    goto L_A291;                                  /* b 0xa291 */
L_A281:
    msg_setup_A_A482();                           /* call 0xa482 */
    b = *(volatile int *)0x262C;                 /* ld */
    if (b != 0) {                                 /* bc 0xa28f beq */
        if ((*(volatile int *)0x2615 - 800) >= 0)/* ld, sub, bc blt */
            sub_E64C();                           /* call 0xe64c */
    }
    msg_setup_C_A4DE();                           /* A28F: call 0xa4de */
L_A291:
    G_AR5 = (int *)-8787;                         /* calld delay slot */
    msg_primitive_A2B9(ppp5);                     /* calld 0xa2b9 */
    b = *(volatile int *)0x262C;                 /* ld (delay + live) */
    G_AR5 = (int *)-8781;                         /* bcd delay slot */
    if (b == 0)                                   /* bcd 0xa2a9 beq */
        goto L_A2A9;
    if ((*(volatile int *)0x2615 - 800) < 0)      /* ld, sub, bc blt */
        goto L_A2A9;
    if ((*(volatile int *)0x2615 - 3400) >= 0)    /* ld, sub, bc bgeq */
        goto L_A2A9;
    G_AR5 = (int *)-8780;                         /* stm #-8780,ar5 */
L_A2A9:
    msg_primitive_A2B9(ppp5);                     /* call 0xa2b9, ret */
}
