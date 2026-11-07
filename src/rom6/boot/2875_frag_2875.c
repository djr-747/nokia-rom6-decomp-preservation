/* ROM6 0x2875 FRAG_2875 -- 48w.
 * Verified encoding: src/rom6/boot/2875_frag_2875.asm (recombine MATCH).
 * ORIGIN 0x2875
 * EXPECT: F074 05F6 7682 001C F495 7582 0001 EC0E F495 F130 0010 F84D 2890 69F8 0552 0040 74F8 0008 0002 F040 0010 F495 75F8 0008 0002 F073 2899 F130 0008 F84D 283D 61F8 2639 0200 F830 28A5 7682 3A98 F495 7582 000F EC0E F495 69F8 263A 0002 F073 283D
 *
 * Intent: Strobe-then-clock gate. Runs dark SUB_05F6 (call, forward extern); *AR2-entry = 28, strobed to port 1 (15 settle cycles); B = A-live-in & 16 (AND preserves A, Z from B), zero detours to the in-span check at 0x2890 (bc beq, rejoins). Else sets bit 6 of cell 0x552; A = port 2 (portr 2,*(0x8): AL alias) OR 16, alias-updated, out to port 2, then jumps to the in-span clock at 0x2899 (b, rejoins). At 0x2890: B = A & 8, zero tail-enters dark 0x283D (bc beq; B == 0, A = entry live-in along this path). Bit 9 (512) of cell 0x2639 set runs FRAG_28A5 (bc tc: has .asm, no C yet, forward extern; AR2 cursor live but unused inside). Else *AR2-entry = 15000 clocked to port 15 (15 settle cycles), bit 1 of cell 0x263A raised, tail-enters dark 0x283D (b). Ports 1/2/15 direct-mapped (extern ops). Bound 2875-28A4.
 */
extern void sub_05F6(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern int port_read_2(void);                                         /* HW port 2 (FRAME sample combine per 27EB span); no ROM definition */
extern void port_write_1(int v);                                      /* HW port 1 (RF/codec per 3EE1 sweep); no ROM definition */
extern void port_write_2(int v);                                      /* HW port 2 (supervisor per 2875 precedent); no ROM definition */
extern void port_write_15(int v);
extern void frag_28A5(void);
extern void frag_283D(void); /* joins 2800_stretch_2800 interior @+0x3D; see docs/evidence/extern-triage.md */

void frag_2875(int a_live, int *par2)
{
    int a = a_live;
    int b;
    sub_05F6();                                    /* call 0x5f6 */
    *par2 = 28;                                    /* st #28,*ar2 */
    /* nop */
    port_write_1(*par2);                           /* portw *ar2,1 */
    /* rpt #14 nop: 15 settle cycles */
    b = a & 16;                                    /* and #16,a,b; Z from B */
    if (b == 0) {
        goto l2890;                                /* bc 0x2890,beq */
    }
    *(volatile int *)0x552 |= 64;              /* orm #64,*(0x552) */
    a = port_read_2();                             /* portr 2,*(0x8) */
    *(volatile int *)0x8 = a;                  /* AL alias write */
    a |= 16;                                       /* or #16,a */
    *(volatile int *)0x8 = a;                  /* AL alias write */
    /* nop */
    port_write_2(a);                               /* portw *(0x8),2 */
    goto l2899;                                    /* b 0x2899 */
l2890:
    b = a & 8;                                     /* and #8,a,b; Z from B */
    if (b == 0) {
        frag_283D();                               /* bc 0x283d,beq */
        return;
    }
    if ((*(volatile int *)0x2639 & 512) != 0) {    /* bitf, bc tc */
        frag_28A5();                               /* away, unbound C */
        return;
    }
l2899:
    *par2 = 15000;                                 /* st #15000,*ar2 */
    /* nop */
    port_write_15(*par2);                           /* portw *ar2,15 */
    /* rpt #14 nop: 15 settle cycles */
    *(volatile int *)0x263A |= 2;              /* orm #2,*(0x263a) */
    frag_283D();                                   /* b 0x283d tail */
}
