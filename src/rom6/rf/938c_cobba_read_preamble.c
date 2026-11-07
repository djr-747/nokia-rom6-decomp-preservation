/* ROM6 0x938C COBBA_READ_PREAMBLE -- 66w.
 * Verified encoding: src/rom6/rf/938c_cobba_read_preamble.asm (recombine MATCH).
 * ORIGIN 0x938C
 * EXPECT: F074 05BA 76F8 20FF 0800 E800 80F8 2202 80F8 2204 76F8 2203 0363 7712 0060 7682 0080 F495 7582 0036 F074 9682 7712 0060 7482 0000 6882 FFEF F495 7582 0000 EC14 F495 7682 0700 F495 7582 0001 EC16 F495 7482 0002 6982 0700 F495 7582 0002 61F8 3EC8 0002 FC20 7482 0000 6982 0010 F495 7582 0000 EC14 F495 7682 0002 F495 7582 0037 FC00
 *
 * Intent: COBBA audio-path read preamble. Runs dark SUB_05BA; cell 0x20FF = 2048; A = 0 stored low to 0x2202/0x2204; cell 0x2203 = 867; AR2 = 96, *AR2 = 128 strobed to port 54. Runs dark SUB_9682. AR2 = 96: cell 96 = port 0 (PORTR to a plain cell: A untouched per op_portr Smem-only) AND -17, strobed back to port 0 (21 settle cycles); cell 96 = 1792 strobed to port 1 (23 settle cycles); cell 96 = port 2 OR 1792 strobed to port 2. Bit 1 of cell 0x3EC8 clear returns (rc ntc). Else cell 96 = port 0 OR 16 strobed to port 0 (21 settle cycles); cell 96 = 2 strobed to port 55; returns. Ports 0/1/2/54/55 direct-mapped (extern ops). Bound 938C-93CD.
 */
extern void sub_05BA(void);
extern void sub_9682(void);
extern int port_read_0(void);
extern int port_read_2(void);
extern void port_write_0(int v);
extern void port_write_1(int v);
extern void port_write_2(int v);
extern void port_write_54(int v);
extern void port_write_55(int v);

void cobba_read_preamble_938C(void)
{
    int a;
    int *ar2;
    sub_05BA();                                    /* call 0x5ba */
    *(volatile int *)0x20FF = 2048;            /* st */
    a = 0;                                         /* ld #0,a */
    *(volatile int *)0x2202 = a & 0xFFFF;      /* stl */
    *(volatile int *)0x2204 = a & 0xFFFF;      /* stl */
    *(volatile int *)0x2203 = 867;             /* st */
    ar2 = (int *)(long)96;                         /* stm #96,ar2 */
    *ar2 = 128;                                    /* st #128,*ar2 */
    /* nop */
    port_write_54(*ar2);                           /* portw *ar2,54 */
    sub_9682();                                    /* call 0x9682 */
    ar2 = (int *)(long)96;                         /* stm #96,ar2 */
    *ar2 = port_read_0();                          /* portr 0,*ar2 */
    *ar2 &= -17;                                   /* andm */
    /* nop */
    port_write_0(*ar2);                            /* portw *ar2,0 */
    /* rpt #20 nop: 21 settle cycles */
    *ar2 = 1792;                                   /* st #1792,*ar2 */
    /* nop */
    port_write_1(*ar2);                            /* portw *ar2,1 */
    /* rpt #22 nop: 23 settle cycles */
    *ar2 = port_read_2();                          /* portr 2,*ar2 */
    *ar2 |= 1792;                                  /* orm */
    /* nop */
    port_write_2(*ar2);                            /* portw *ar2,2 */
    if ((*(volatile int *)0x3EC8 & 2) == 0) {  /* bitf, rc ntc */
        return;
    }
    *ar2 = port_read_0();                          /* portr 0,*ar2 */
    *ar2 |= 16;                                    /* orm */
    /* nop */
    port_write_0(*ar2);                            /* portw *ar2,0 */
    /* rpt #20 nop: 21 settle cycles */
    *ar2 = 2;                                      /* st #2,*ar2 */
    /* nop */
    port_write_55(*ar2);                           /* portw *ar2,55 */
}
