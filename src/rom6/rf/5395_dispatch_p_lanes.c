/* ROM6 0x5395 DISPATCH_P_LANES_5395 -- 37w.
 * Verified encoding: src/rom6/rf/5395_dispatch_p_lanes.asm (recombine MATCH).
 * ORIGIN 0x5395
 * EXPECT: F495 F074 0672 68F8 0537 FC97 68F8 051D FFFB 68F8 263A FDFF F020 023C 7712 2ED4 EC1D 8092 82F8 2EFD 7712 051C 6882 FF7F 76F8 2EFE 0001 70F8 057B 3F13 60F8 0573 AFAB F820 53BA F073 54BB
 *
 * Intent: P-lane zero-fill plus select head. Runs dark SUB_0672 (call, per 53D9). AND-masks cells 0x537/0x51D/0x263A. A = 572; 30 copies (rpt #29) of A low into 0x2ED4 up (stl loop); high word of A (zero) into cell 0x2EFD (sth to absolute: (A >> 16) & 0xFFFF per 3A8E). AR2 = 0x51C, cell &= -129; cell 0x2EFE = 1; cell 0x57B = cell 0x3F13 (mvdk, dmad is destination). Cell 0x573 != -20565 runs unbound FRAG_53BA (bc ntc, has .asm, forward extern); else tail-enters dark 0x54BB (b, forward extern per 53D9). Bound 5395-53B9.
 */
extern void sub_0672(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_53BA(void);
extern void frag_54BB(void);

void frag_5395(void)
{
    int a, i;
    int *ar2;
    /* nop */
    sub_0672();                                    /* call 0x672 */
    *(volatile int *)0x537 &= -873;            /* andm */
    *(volatile int *)0x51D &= -5;             /* andm */
    *(volatile int *)0x263A &= -513;          /* andm */
    a = 572;                                       /* ld #572,a */
    ar2 = (int *)(long)0x2ED4;                     /* stm */
    for (i = 0; i < 30; i++) {                     /* rpt #29 */
        *ar2++ = a & 0xFFFF;                       /* stl a,*ar2+ */
    }
    *(volatile int *)0x2EFD = (a >> 16) & 0xFFFF; /* sth a,*(0x2efd) */
    ar2 = (int *)(long)0x51C;                      /* stm #1308,ar2 */
    *ar2 &= -129;                                  /* andm #-129,*ar2 */
    *(volatile int *)0x2EFE = 1;               /* st */
    *(volatile int *)0x57B = *(volatile int *)0x3F13; /* mvdk */
    if (*(volatile int *)0x573 != -20565) {    /* cmpm, bc ntc */
        frag_53BA();                               /* away, unbound C */
        return;
    }
    frag_54BB();                                   /* b 0x54bb tail */
}
