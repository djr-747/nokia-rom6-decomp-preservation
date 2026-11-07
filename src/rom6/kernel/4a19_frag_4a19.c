/* ROM6 0x4A19 FRAG_4A19 -- 45w.
 * Verified encoding: src/rom6/kernel/4a19_frag_4a19.asm (recombine MATCH).
 * ORIGIN 0x4A19
 * EXPECT: 60F8 0008 000F F820 4A4B 7684 3A98 F495 7584 0005 EC16 F495 F495 7584 0006 EC16 F495 F495 7584 002F EC16 F495 F495 7584 0007 EC16 F495 F495 7584 0008 EC10 F495 60F8 250F 0022 F820 4A46 76F8 366F 0000 76F8 37B0 0000 F073 4ADF
 *
 * Intent: Multi-port strobe with select tails. AL-alias cell != 15 runs C FRAG_4A4B with entry B and entry AR5 (bc ntc, C-bound; neither touched in-span, threaded as params). Else *AR4-entry = 15000 (AR4 threaded as param, unstepped) strobed to ports 5/6/47/7/8 with settle gaps; cell 0x250F != 34 runs C FRAG_4A46 with entry AR2 (bc ntc, C-bound; AR2 untouched in-span, threaded). Else clears cells 0x366F/0x37B0, tail-enters C FRAG_4ADF (b, C-bound). Ports 5/6/7/8/47 direct-mapped (extern ops). Bound 4A19-4A45.
 */
extern void frag_4A4B(int b_live, int *par5);
extern void frag_4A46(int *par2);
extern void frag_4ADF(void);
extern void port_write_5(int v);                                      /* HW port 5 (RF sweep per 3EE1 span); no ROM definition */
extern void port_write_6(int v);                                      /* HW port 6 (per 4a19 span); no ROM definition */
extern void port_write_7(int v);                                      /* HW port 7 (RF sweep per 3EE1 span); no ROM definition */
extern void port_write_8(int v);                                      /* HW port 8 (RF per 389c/3EE1 spans); no ROM definition */
extern void port_write_47(int v);                                     /* HW port 47 (RF per 3EE1/4a19 spans); no ROM definition */

void frag_4A19(int b_live, int *par4, int *par5, int *par2)
{
    if (*(volatile int *)0x8 != 15) {          /* cmpm *(0x8),#15, bc ntc */
        frag_4A4B(b_live, par5);                    /* away, C-bound */
        return;
    }
    *par4 = 15000;                                 /* st #15000,*ar4 */
    /* nop */
    port_write_5(*par4);                           /* portw *ar4,5 */
    /* rpt #22 nop: 23 settle cycles */
    /* nop; nop */
    port_write_6(*par4);                           /* portw *ar4,6 */
    /* rpt #22 nop */
    /* nop; nop */
    port_write_47(*par4);                          /* portw *ar4,47 */
    /* rpt #22 nop */
    /* nop; nop */
    port_write_7(*par4);                           /* portw *ar4,7 */
    /* rpt #16 nop: 17 settle cycles */
    /* nop; nop */
    port_write_8(*par4);                           /* portw *ar4,8 */
    /* rpt #16 nop */
    if (*(volatile int *)0x250F != 34) {       /* cmpm, bc ntc */
        frag_4A46(par2);                            /* away, C-bound */
        return;
    }
    *(volatile int *)0x366F = 0;               /* st */
    *(volatile int *)0x37B0 = 0;               /* st */
    frag_4ADF();                                   /* b 0x4adf tail */
}
