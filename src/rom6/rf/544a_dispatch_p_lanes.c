/* ROM6 0x544A DISPATCH_P_LANES_544A -- 33w.
 * Verified encoding: src/rom6/rf/544a_dispatch_p_lanes.asm (recombine MATCH).
 * ORIGIN 0x544A
 * EXPECT: F074 06E4 68F8 0537 FC97 68F8 051D FFFB 68F8 263A FDFF 70F8 057B 3F14 10F8 2477 7712 051C 6882 FF7F FF45 6982 0080 76F8 0B67 0001 60F8 0573 B11C F820 546B F073 54BB
 *
 * Intent: P-lane store pair with unconditional compare. Runs dark SUB_06E4 (call). AND-masks cells; cell 0x57B = cell 0x3F14 (mvdk); A = cell 0x2477; AR2 = 0x51C, cell &= -129. A == 0 skips the store slots (xc 2,aeq over orm plus st: neither slot sets status, and the cmpm below runs unconditionally, so entry TC is dead and no param is needed). Mismatch runs C FRAG_546B with the 0x51C AR2 (bc ntc, C-bound, interior join); else tail-enters dark 0x54BB (b). Bound 544A-546A.
 */
extern void sub_06E4(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_546B(int *par2);
extern void frag_54BB(void);

void frag_544A(void)
{
    int a;
    int *ar2;
    sub_06E4();                                    /* call 0x6e4 */
    *(volatile int *)0x537 &= -873;            /* andm */
    *(volatile int *)0x51D &= -5;             /* andm */
    *(volatile int *)0x263A &= -513;          /* andm */
    *(volatile int *)0x57B = *(volatile int *)0x3F14; /* mvdk */
    a = *(volatile int *)0x2477;               /* ld */
    ar2 = (int *)(long)0x51C;                      /* stm #1308,ar2 */
    *ar2 &= -129;                                  /* andm #-129,*ar2 */
    if (a != 0) {                                  /* xc 2,aeq */
        *ar2 |= 128;                               /* orm (slot 1) */
        *(volatile int *)0x0B67 = 1;           /* st (slot 2) */
    }
    if (*(volatile int *)0x573 != -20196) {    /* cmpm, bc ntc */
        frag_546B(ar2);                            /* away, C-bound */
        return;
    }
    frag_54BB();                                   /* b 0x54bb tail */
}
