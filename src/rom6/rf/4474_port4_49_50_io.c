/* ROM6 0x4474 PORT4_49_50_IO -- 50w.
 * Verified encoding: src/rom6/rf/4474_port4_49_50_io.asm (recombine MATCH).
 * ORIGIN 0x4474
 * EXPECT: 69F8 13D0 0400 4BF8 263A F074 3EE1 F000 000A F110 1387 68F8 263A FF9F 7716 0000 FD4E E80A 74F8 000B 0004 F495 7584 0031 F495 F495 75F8 0013 0032 F495 F495 75F8 0008 0004 EC16 F495 61F8 13D0 0400 F830 4498 8BF8 263A F495 75F8 000B 0004 EC16 F495 FC00
 *
 * Intent: Port 4/49/50 strobe with poll loop. Sets bit 10 of cell 0x13D0; saves cell 0x263A (pshd: C local); runs C PORT13_STABLE_READ (call, C-bound; A-OUT proven by the 3EE3 loop shape -- the stable reading overwrites entry A, fixed this wave). A = reading + 10 (ADD #lk SHFT-0); B = A - 4999 (SUB #lk per ti-c54x op_sub_lk); B > 0 presets A = 10 (xc 1,bgt over a plain slot, exact skip per 4EBC precedent; 16-bit narrowing noted). B = port 4 (BL alias); *AR4-entry out to port 49 (AR4 threaded as param, unstepped); MMR 0x13 out to port 50; A (AL alias) out to port 4 (23 settle cycles); spins while bit 10 of cell 0x13D0 stays set (bitf plus bc-to-self at 0x4498: busy-wait, terminates in hardware); restores cell 0x263A (popd: the interim andm #-97 is dead, cell net preserved, modeled exactly); BL out to port 4 (23 settle cycles); returns. Ports 4/49/50 direct-mapped. Bound 4474-44A5.
 */
extern int port13_stable_read(void);
extern int port_read_4(void);                                         /* HW port 4 (RF per 3cd2 port4850 seq); no ROM definition */
extern void port_write_4(int v);                                      /* HW port 4 (RF per 3cd2 port4850 seq); no ROM definition */
extern void port_write_49(int v);                                     /* HW port 49 (RF per 22F3/3cd2 spans); no ROM definition */
extern void port_write_50(int v);                                     /* HW port 50 (RF per 22F3/3cd2 spans); no ROM definition */

void port4_49_50_io_4474(int a_live, int *par4)
{
    int a = a_live;
    int b;
    int save263a;
    *(volatile int *)0x13D0 |= 1024;        /* orm */
    save263a = *(volatile int *)0x263A;  /* pshd *(0x263a) */
    a = port13_stable_read();              /* call 0x3ee1 (A-out) */
    a += 10;                                       /* add #10,a */
    b = a - 4999;                                  /* sub #4999,a,b */
    *(volatile int *)0x263A &= -97;          /* andm (dead: popd restores) */
    /* stm #0,ar6 (dead preset, no use in span, noted) */
    if (b > 0) {                                   /* xc 1,bgt */
        a = 10;                                    /* ld #10,a (slot) */
    }
    b = port_read_4();                             /* portr 4,*(0xb) */
    *(volatile int *)0xB = b;                  /* BL alias write */
    /* nop */
    port_write_49(*par4);                          /* portw *ar4,49 */
    /* nop; nop */
    port_write_50(*(volatile int *)0x13);    /* portw *(0x13),50 */
    /* nop; nop */
    port_write_4(a);                               /* portw *(0x8),4 */
    /* rpt #22 nop: 23 settle cycles */
    while ((*(volatile int *)0x13D0 & 1024) != 0) { /* bitf; bc 0x4498,tc */
        /* re-poll: branch targets the bitf itself */
    }
    *(volatile int *)0x263A = save263a;      /* popd *(0x263a) */
    /* nop */
    port_write_4(b);                               /* portw *(0xb),4 */
    /* rpt #22 nop: 23 settle cycles */
}
