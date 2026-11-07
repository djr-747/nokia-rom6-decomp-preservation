/* ROM6 0x3D1B FRAG_3D1B -- 32w.
 * Verified encoding: src/rom6/kernel/3d1b_frag_3d1b.asm (recombine MATCH).
 * ORIGIN 0x3D1B
 * EXPECT: 7683 0002 7713 1274 7712 126E F495 7592 0030 F495 F495 7593 0031 F495 F495 7593 0032 F495 F495 7582 0004 EC11 F495 7192 058E 6BF8 2660 FFFE 6BF8 265E FFFE FC00
 *
 * Intent: RF port program with cursor writeback. *AR3-entry = 2, AR3 = 0x1274, AR2 = 0x126E (entry AR3 threaded as param, overwritten); *AR2++ out to port 48 (settle nops); *AR3++ out to ports 49 then 50; *AR2 out to port 4 (18 settle cycles); cell 0x58E = stepped AR2 (mvdk, dmad is destination); cells 0x2660/0x265E decremented by 2 (addm); returns. Ports 4/48/49/50 direct-mapped. Bound 3D1B-3D3A.
 */
extern void port_write_4(int v);                                      /* HW port 4 (RF per 3cd2 port4850 seq); no ROM definition */
extern void port_write_48(int v);                                     /* HW port 48 (RF per 22F3/3cd2 spans); no ROM definition */
extern void port_write_49(int v);                                     /* HW port 49 (RF per 22F3/3cd2 spans); no ROM definition */
extern void port_write_50(int v);                                     /* HW port 50 (RF per 22F3/3cd2 spans); no ROM definition */

void frag_3D1B(int *par3)
{
    int *ar2, *ar3;
    *par3 = 2;                                     /* st #2,*ar3 */
    ar3 = (int *)(long)0x1274;                     /* stm #4724,ar3 */
    ar2 = (int *)(long)0x126E;                     /* stm #4718,ar2 */
    /* nop */
    port_write_48(*ar2++);                         /* portw *ar2+,48 */
    /* nop; nop */
    port_write_49(*ar3++);                         /* portw *ar3+,49 */
    /* nop; nop */
    port_write_50(*ar3++);                         /* portw *ar3+,50 */
    /* nop; nop */
    port_write_4(*ar2);                            /* portw *ar2,4 */
    /* rpt #17 nop: 18 settle cycles */
    *(volatile int *)0x58E = *ar2++;              /* mvdk *ar2+,0x58e */
    *(volatile int *)0x2660 -= 2;              /* addm */
    *(volatile int *)0x265E -= 2;              /* addm */
    /* ret */
}
