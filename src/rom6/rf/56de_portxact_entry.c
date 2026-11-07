/* ROM6 0x56DE PORTXACT_ENTRY -- 30w.
 * Verified encoding: src/rom6/rf/56de_portxact_entry.asm (recombine MATCH).
 * ORIGIN 0x56DE
 * EXPECT: 11F8 2658 F600 F7BB 11F8 053B F500 81F8 053B 76F8 0557 FFFF F845 56EF 74F8 0557 0010 F000 1387 F495 75F8 0008 000E EC0E F495 76F8 2658 0000 F6BB FC00
 *
 * Intent: accumulate-and-post port transaction. Add cell 0x2658
 * into A under INTM lock, fold into the poster cell 0x53B, flag
 * 0x557, then: unless A is zero, sample port 16 into the flag
 * cell (bc 0x56ef,aeq skips only that read). Add the 4999 bias,
 * write cell 0x8 to port 14, hold 15 cycles, clear the source
 * cell, unlock, return.
 */
extern int port_read_16(void);    /* portr pa16 (into 0x557) */
extern void port_write_14(int v); /* portw *(0x8),pa14 */

void portxact_entry_56DE(int a_in)
{
    int a = a_in + *(volatile int *)0x2658;   /* ld, add b,a */
    /* ssbx st1,intm: INTM lock (hardware state, no C form) */
    *(volatile int *)0x53B += a;              /* ld, add, stl */
    *(volatile int *)0x557 = -1;              /* st #-1 */
    if (a != 0)                               /* bc 0x56ef,aeq */
        *(volatile int *)0x557 = port_read_16();
    a += 4999;                                /* L_56EF: add #4999,a */
    port_write_14(*(volatile int *)0x8);      /* portw, nop */
    { int i; for (i = 0; i < 15; i++) {} }   /* rpt #14, nop */
    *(volatile int *)0x2658 = 0;              /* st #0 */
    /* rsbx st1,intm: unlock; ret */
}
