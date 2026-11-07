/* ROM6 0x9682 ROUTINE_9682 -- 52w table-fill with port-bit exits.
 * Verified encoding: src/rom6/kernel/9682_routine_9682.asm (recombine MATCH).
 * ORIGIN 0x9682
 * EXPECT: F074 05C4 F7BB F020 2000 7712 21FA 8092 8092 F020 2100 8092 8082 7712 20FA F071 0004 8092 7712 21FE EC03 8092 7712 20FF 6882 0FFF 6182 0200 F830 96B6 6182 0100 F830 96B6 74F8 000B 0036 F330 0080 E800 6182 0002 FD4D E802 80F8 20FC E801 FD30 E800 FE00 80F8 2201
 *
 * Intent: Runs sub_05C4 (low-zone mini-kernel,
 * trace-evidenced, flagged); INTM set (ssbx,
 * hardware, no C form). Table fill: *(8698) =
 * *(8699) = 8192; A = 8448, *(8700) = *(8701) =
 * 8448; AR2 = 8442, A = 0, 5x *(AR2++) = 0 (rptz
 * a,#4; RPT N + 1); AR2 = 8702, 4x *(AR2++) = 0
 * (rpt #3); AR2 = 8447, *(AR2) &= 4095 (andm).
 * Bit 9 of *(AR2) set tail-calls frag_96B6 and
 * returns (bitf; bc tc); else bit 8 set tail-calls
 * frag_96B6 and returns. Cell 0xB = port 54
 * (portr, port-address extension 0036 per 9760,
 * extern op). B = B-entry & 128 (and #128,b:
 * src/dst B per oracle layout; B entry-dark,
 * flagged); A = 0; B == 0 loads A = 2 (xc 1,beq,
 * execute-when-true); cell 0x20FC = A-low. A = 1;
 * bit 1 of *(AR2) set loads A = 0 (xc 1,tc).
 * Retd with its 2 delay words owned by the next
 * span (96B4-96B5 run there). Out cells/AR2/A/B.
 * EXPECT from the image.
 */
extern void sub_05C4(void); /* low-zone mini-kernel, trace-evidenced, flagged */
extern void frag_96B6(void);
extern void portr_port54_cell0B(void); /* HW port alias, emulator-provided */

void routine_9682(void)
{
    long a;
    long b;   /* live-in (dark, flagged): read by and #128,b */
    int *ar2;
    int i;

    sub_05C4();                                            /* call 0x5c4 */
    /* ssbx st1,intm (hardware, no C form) */
    a = 8192L;                                             /* ld #8192,a */
    ar2 = (int *)(long)8698;                               /* stm #8698,ar2 */
    *ar2++ = (int)(a & 0xFFFFL);                           /* stl a,*ar2+ */
    *ar2++ = (int)(a & 0xFFFFL);                           /* stl a,*ar2+ */
    a = 8448L;                                             /* ld #8448,a */
    *ar2++ = (int)(a & 0xFFFFL);                           /* stl a,*ar2+ */
    *ar2 = (int)(a & 0xFFFFL);                             /* stl a,*ar2 */
    ar2 = (int *)(long)8442;                               /* stm #8442,ar2 */
    a = 0L;                                                /* rptz a,#4 */
    for (i = 0; i < 5; i++)                                /* RPT N + 1 */
        *ar2++ = (int)(a & 0xFFFFL);                       /* stl a,*ar2+ */
    ar2 = (int *)(long)8702;                               /* stm #8702,ar2 */
    for (i = 0; i < 4; i++)                                /* rpt #3 */
        *ar2++ = (int)(a & 0xFFFFL);                       /* stl a,*ar2+ */
    ar2 = (int *)(long)8447;                               /* stm #8447,ar2 */
    *ar2 &= 4095;                                          /* andm #4095,*ar2 */
    if ((*ar2 & 512) != 0) {                               /* bitf; bc tc */
        frag_96B6();                                       /* b 0x96b6 (tail) */
        return;
    }
    if ((*ar2 & 256) != 0) {                               /* bitf; bc tc */
        frag_96B6();                                       /* b 0x96b6 (tail) */
        return;
    }
    portr_port54_cell0B();                                 /* portr 54,*(0xb) */
    b &= 128L;                                             /* and #128,b */
    a = 0L;                                                /* ld #0,a */
    if (b == 0L)                                           /* xc 1,beq */
        a = 2L;                                            /* ld #2,a */
    *(volatile int *)0x20FC = (int)(a & 0xFFFFL);          /* stl a,*(0x20fc) */
    a = 1L;                                                /* ld #1,a */
    if ((*ar2 & 2) != 0)                                   /* xc 1,tc */
        a = 0L;                                            /* ld #0,a */
    /* retd (delays 96B4-96B5 owned by next span, run before return) */
}
