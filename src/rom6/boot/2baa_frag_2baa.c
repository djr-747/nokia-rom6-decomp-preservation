/* ROM6 0x2BAA FRAG_2BAA -- 67w.
 * Verified encoding: src/rom6/boot/2baa_frag_2baa.asm (recombine MATCH).
 * ORIGIN 0x2BAA
 * EXPECT: 7682 0800 F495 7582 0001 EC16 F495 74F8 0008 0038 F030 0008 F845 283D 7714 3490 1084 F030 0070 7712 04D3 7713 3A82 F845 2BCD F014 0001 7712 3493 7713 3A86 F845 2BCD 7712 34A2 F074 39F0 10F8 34BF F845 2BED 10F8 3490 F130 0070 F84D 2BE4 60F8 34BF 0004 F820 2BED F314 0001 F84D 2BE4 F073 2BED 6BF8 3490 0010 7712 0914 F074 39A4 F073 283D
 *
 * Intent: RF gate plus mode-lane select head. *AR2-entry = 2048, strobed to port 1 (23 settle cycles); A = port 56 (portr, AL alias) AND 8, zero tail-enters dark 0x283D (bc aeq; A == 0). A = *(0x3490) AND 112 (Z from A, stm pair preserves it); AR2/AR3 lane pair 1235/14978, A == 0 joins at the in-span call gate 0x2BCD (bc aeq). Else A = (A << 4) - 1 (SUB #lk,SHFT,src form), lane pair 13459/14982, A == 0 joins at 0x2BCD the same way (unreachable for masked A, folded: ((A&112)<<4)-1 never 0). Calls dark SUB_39F0. A = *(0x34BF), zero enters C FRAG_2BAA_SEG2 (bc aeq; second segment, C-bound). A = *(0x3490), B = A AND 112, B == 0 joins the in-span bump at 0x2BE4 (bc beq). *(0x34BF) == 34 mismatch enters SEG2 (bc ntc). Else B = (B << 4) - 1, B == 0 joins 0x2BE4 (likewise unreachable, folded), else falls into SEG2 (b). At 0x2BE4: *(0x3490) += 16, AR2 = 2324, calls dark SUB_39A4, tail-enters dark 0x283D (b). Ports 1/56 direct-mapped (extern ops). AR2 entry cursor threaded as param (overwritten by lane stms). Bound 2BAA-2BEC; SEG2 bound 2BED-2C02 per its header.
 */
extern int port_read_56(void);
extern void port_write_1(int v);
extern void sub_39F0(void);
extern void sub_39A4(void);
extern void frag_2BAA_seg2(void);
extern void frag_283D(void);

void frag_2BAA(int *par2)
{
    int a, b;
    int *ar2, *ar3;
    *par2 = 2048;                                  /* st #2048,*ar2 */
    /* nop */
    port_write_1(*par2);                           /* portw *ar2,1 */
    /* rpt #22 nop: 23 settle cycles */
    a = port_read_56();                            /* portr 56,*(0x8) */
    *(volatile int *)0x8 = a;                  /* AL alias write */
    a &= 8;                                        /* and #8,a */
    if (a == 0) {                                  /* bc 0x283d,aeq */
        frag_283D();
        return;
    }
    ar2 = (int *)(long)0x3490;                     /* stm #13456,ar4 (as base) */
    a = *ar2;                                      /* ld *ar4,a */
    a &= 112;                                      /* and #112,a; Z from A */
    ar2 = (int *)(long)1235;                       /* stm #1235,ar2 */
    ar3 = (int *)(long)14978;                      /* stm #14978,ar3 */
    if (a != 0) {                                  /* bc 0x2bcd,aeq skips */
        a = (a << 4) - 1;                          /* sub #1,4,a */
        ar2 = (int *)(long)13459;                  /* stm #13459,ar2 */
        ar3 = (int *)(long)14982;                  /* stm #14982,ar3 */
    }
/* l2bcd: call gate (both paths join) */
    ar2 = (int *)(long)13474;                      /* stm #13474,ar2 */
    (void)ar3;
    sub_39F0();                                    /* call 0x39f0 */
    a = *(volatile int *)0x34BF;               /* ld *(0x34bf),a */
    if (a == 0) {                                  /* bc 0x2bed,aeq */
        frag_2BAA_seg2();
        return;
    }
    a = *(volatile int *)0x3490;               /* ld *(0x3490),a */
    b = a & 112;                                   /* and #112,a,b */
    if (b != 0) {                                  /* bc 0x2be4,beq skips */
        if (*(volatile int *)0x34BF != 4) {    /* cmpm, bc ntc */
            frag_2BAA_seg2();
            return;
        }
        b = (b << 4) - 1;                          /* sub #1,4,b */
        if (b != 0) {                              /* bc 0x2be4,beq skips */
            frag_2BAA_seg2();                      /* b 0x2bed */
            return;
        }
    }
/* l2be4: bump lane */
    *(volatile int *)0x3490 += 16;              /* addm #16 */
    ar2 = (int *)(long)2324;                       /* stm #2324,ar2 */
    (void)ar2;
    sub_39A4();                                    /* call 0x39a4 */
    frag_283D();                                   /* b 0x283d tail */
}
