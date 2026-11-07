/* ROM6 0x27EB FRAME_ISR_HEAD_27EB -- 21w.
 * Verified encoding: src/rom6/boot/27eb_frame_isr_head_27eb.asm (recombine MATCH).
 * ORIGIN 0x27EB
 * EXPECT: 4807 F030 2000 F040 4900 8807 7712 021E 7482 0002 1082 F493 7482 0001 1882 F130 1000 F84C 296A F130 001C
 *
 * Intent: FRAME_ISR sample-combine head (V17/V18/V24 entry via 27CD prologue;
 * ST1 mode prologue identical to the SAMPLE/STATE templates). Sample combine
 * A = ~(port2) & (port1) per roms/rom6/ivt.md: portr pa2 stores port2 to the
 * 0x21E cell (portr is memory-only, A untouched), ld/cmpl form ~port2, portr
 * pa1 refreshes the cell, and *ar2 lanes combine. B = A & 4096 (bit 12) joins
 * the owned 296a frag tail (bc bneq; call+return per 2000 precedent); B = A &
 * 28 (0x1C lane) falls through 27FF into rf/2800_stretch_2800 (bc bneq head,
 * evidenced by its header). Entry by fallthrough from the abutting 27E9 slot
 * (27EA-27EB instruction boundary).
 */
extern void frag_296A(int *par2);
extern int port_read_2(void);                                         /* HW port 2 (FRAME sample combine per 27EB span); no ROM definition */
extern int port_read_1(void);                                         /* HW port 1 (FRAME sample combine per 27EB span); no ROM definition */

void frame_head_27EB(void)
{
    long a;
    long b;
    int *ar2;

    /* ldm st1,a; and #8192,a; or #18688,a; stlm a,st1 (FRCT-class mode set) */
    ar2 = (int *)542;                                      /* stm #542,ar2 */
    *(volatile int *)0x21E = port_read_2();                /* portr 2,*ar2 */
    a = (long)*(volatile int *)0x21E;                      /* ld *ar2,a */
    a = ~a;                                                /* cmpl a */
    *(volatile int *)0x21E = port_read_1();                /* portr 1,*ar2 */
    a &= (long)*(volatile int *)0x21E;                     /* and *ar2,a */
    b = a & 4096L;                                         /* and #4096,a,b */
    if (b != 0) {                                          /* bc 0x296a,bneq */
        frag_296A(ar2);
        return;
    }
    b = a & 28L;                                           /* and #28,a,b */
    /* bc 0x2875,bneq lives in the 2800 head; falls into 2800_stretch_2800 */
    (void)b;
}
