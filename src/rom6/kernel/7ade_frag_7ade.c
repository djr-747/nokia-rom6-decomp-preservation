/* ROM6 0x7ADE FRAG_7ADE -- 7w.
 * Verified encoding: src/rom6/kernel/7ade_frag_7ade.asm (recombine MATCH).
 * ORIGIN 0x7ADE
 * EXPECT: 6D90 10F8 34CC F845 7AE5 7713 34BE
 *
 * Intent: Step-plus-gate into port programmer. AR0-live-in steps +1 (mar *ar0+, in-out); A = cell 0x34CC, zero tail-enters PORT_PROGRAMMER_7AE5 0x7AE5 (bc 0x7ae5,aeq, C: port_programmer_7AE5 with AR1 in-out plus AR3 = 13502 plus AR4/AR5 passthrough; the in-span stm #13502,ar3 is its argument setup, noted). Else falls out with A live (int return; AR3 preset noted). AR3/AR4/AR5 untouched in-span. Bound 7ADE-7AE4.
 */
extern void port_programmer_7AE5(int **pp1, int *ar3, int *ar4, int *ar5);

int frag_7ADE(int **ppar0, int **ppar1, int *par4, int *par5)
{
    int a;
    (*ppar0)++;                                 /* mar *ar0+ */
    a = *(volatile int *)0x34CC;            /* ld *(0x34cc),a */
    if (a == 0) {                                /* bc 0x7ae5,aeq */
        /* stm #13502,ar3 (argument setup for the call) */
        port_programmer_7AE5(ppar1, (int *)13502, par4, par5);
        return a;                                /* tail (A == 0) */
    }
    /* stm #13502,ar3 (dead preset, AR3 unused after) */
    return a;                                    /* falls through, A live-out */
}
