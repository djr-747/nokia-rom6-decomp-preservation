/* ROM6 0x9DDD STUB_9DDD -- 23w.
 * Verified encoding: src/rom6/kernel/9ddd_stub_9ddd.asm (recombine MATCH).
 * ORIGIN 0x9DDD
 * EXPECT: F074 06C0 76F8 057D 2900 76F8 057E 3236 76F8 2A69 3236 76F8 057C 0000 76F8 0861 0000 7711 3236 E800 EC9F 8091 FC00
 *
 * Intent: Constant-block plus zero-fill. Runs 0x6C0; five constant stores (cells 0x57D = 10496, 0x57E/0x2A69 = 12854, 0x57C/0x861 = 0); AR1 = 12854; A = 0 with 160 stores (rpt #159) through AR1; return.
 */
extern void sub_06C0(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void stub_9DDD(void)
{
    int i;
    int *ar1;
    sub_06C0();                                  /* call 0x6c0 */
    *(volatile int *)0x57D = 10496;          /* st */
    *(volatile int *)0x57E = 12854;          /* st */
    *(volatile int *)0x2A69 = 12854;         /* st */
    *(volatile int *)0x57C = 0;              /* st */
    *(volatile int *)0x861 = 0;              /* st */
    ar1 = (int *)12854;                          /* stm #12854,ar1 */
    for (i = 0; i < 160; i++)                    /* ld #0,a; rpt #159 */
        *ar1++ = 0;                              /* stl a,*ar1+ */
    /* ret */
}
