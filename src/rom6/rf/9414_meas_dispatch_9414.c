/* ROM6 0x9414 MEAS_DISPATCH_9414 -- 26w.
 * Verified encoding: src/rom6/rf/9414_meas_dispatch_9414.asm (recombine MATCH).
 * ORIGIN 0x9414
 * EXPECT: 7714 20FF 7213 21FC 7719 00FA 6184 0400 FC30 6184 0200 F830 9429 6184 0100 F830 9429 F074 99A4 F073 942B F074 9A11 F074 96BD FC00
 *
 * Intent: measurement dispatch on COBBA status bits. Load the status
 * cell (*AR4 = 0x20FF) and a DARAM pointer, then: bit 10 gates the
 * bit-9 test (rc tc conditional prefix, exact skip semantics in the
 * .asm); bit 9 or bit 8 set takes the tail path (call 0x9A11);
 * otherwise call 0x99A4 first. Both paths end calling 0x96BD
 * (MEAS_RSSI_POSTER) and return.
 */
extern void msg_header_builder_99A4(void);
extern void sub_9A11(void);
extern void meas_rssi_poster_96BD(void);

void meas_dispatch_9414(void)
{
    int st = *(volatile int *)0x20FF;   /* stm/mvdm/bk setup, bitf source */
    if ((st & 1024) && (st & 512))      /* bitf #1024, rc tc, bitf #512 */
        goto tail;                      /* bc 0x9429,tc */
    if (st & 256)                       /* bitf #256 */
        goto tail;                      /* bc 0x9429,tc */
    msg_header_builder_99A4();          /* call 0x99a4 */
    goto done;                          /* b 0x942b */
tail:
    sub_9A11();                         /* 0x9429: call 0x9a11 */
done:
    meas_rssi_poster_96BD();            /* 0x942b: call 0x96bd, ret */
}
