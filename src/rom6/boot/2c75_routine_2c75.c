/* ROM6 0x2C75 ROUTINE_2C75 -- 19w.
 * Verified encoding: src/rom6/boot/2c75_routine_2c75.asm (recombine MATCH).
 * ORIGIN 0x2C75
 * EXPECT: 76F8 0866 0000 76F8 054C 0000 74F8 0008 0002 F030 FFFD F495 75F8 0008 0002 69F8 0000 0204 FC00
 *
 * Intent: Port 2 handshake. Clears cells 0x866/0x54C; AL = port 2 (portr 2,*(0x8): AL alias); clears low 2 bits (and #-3,a, AL alias cell follows); PORT[2] = AL back; sets bits 2 and 9 of the IMR cell *(0x0) (orm #516), return.
 */
extern int port_read_2(void);
extern void port_write_2(int v);

void routine_2C75(void)
{
    *(volatile int *)0x866 = 0;              /* st #0 */
    *(volatile int *)0x54C = 0;              /* st #0 */
    *(volatile int *)0x8 = port_read_2();        /* portr (AL alias) */
    *(volatile int *)0x8 &= -3;                  /* and #-3,a */
    port_write_2(*(volatile int *)0x8);          /* portw *(0x8),2 */
    *(volatile int *)0x0 |= 516;            /* orm #516,*(0x0) (IMR) */
    /* ret */
}
