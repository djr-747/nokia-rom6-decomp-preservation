/* ROM6 0xAE71 SUB_AE71 -- 47w dispatch-prologue stub fan.
 * Verified encoding: src/rom6/kernel/ae71_sub_ae71.asm (recombine MATCH).
 * ORIGIN 0xAE71
 * EXPECT: 10F8 260F F073 388C 10F8 260E F073 388C 10F8 2613 61F8 2628 0200 F830 388C 61F8 2629 1000 F830 388C F073 389C F074 0596 60F8 262B 0000 F830 AEA0 10F8 2613 7713 3F00 F110 0200 F84B AE9D F010 03CF F495 F495 FF43 7713 3F02 E598 E598 FC00
 *
 * Intent: Six entry lanes (unconditional b's shadow the
 * fall-through, so each head is its own lane; TRACE
 * histogram shows AE71-AE89 heads plus a rare AE8E
 * lane). Lanes 71/75/79: A = cell 0x260F/0x260E/
 * 0x2613, tail-call frag_388C, return. Lane 7B: TC =
 * cell 0x2628 & 512 (bitf); set tail-calls frag_388C
 * and returns; else TC = cell 0x2629 & 4096; set
 * tail-calls frag_388C and returns; else tail-calls
 * frag_389C with caller-live A/AR2/AR3. Lane 87: runs
 * sub_0596 (low-zone, flagged); TC = (cell 0x262B ==
 * 0) (cmpm, oracle TC = equality); set tail-calls
 * frag_AEA0 and returns; else falls into lane 8E.
 * Lane 8E: A = cell 0x2613; AR3 = 16128; B = A - 512;
 * B < 0 skips to the stores (bc blt); A -= 975; the
 * two nops run always (xc delay); xc 2,alt runs stm
 * #16130,ar3 only when A < 0 (execute-when-true);
 * *(AR2++) = *(AR3++) twice (mvdd pair, AR2
 * caller-live); return. Entry A/AR2/AR3 caller-live
 * dark on lanes 7B/87, flagged.
 * EXPECT from the image.
 */
extern void frag_388C(void);
extern void frag_389C(long a_live, int *ar2_in, int *ar3_live);
extern void frag_AEA0(void);
extern void sub_0596(void); /* low-zone, flagged per 72e3 */

void sub_AE71(void)
{
    long a;

    a = (long)*(volatile int *)0x260F;                     /* ld *(0x260f),a */
    (void)a;
    frag_388C();                                           /* b 0x388c */
}

void lane_AE75(void)
{
    long a;

    a = (long)*(volatile int *)0x260E;                     /* ld *(0x260e),a */
    (void)a;
    frag_388C();                                           /* b 0x388c */
}

void lane_AE79(void)
{
    long a;

    a = (long)*(volatile int *)0x2613;                     /* ld *(0x2613),a */
    (void)a;
    frag_388C();                                           /* b 0x388c */
}

void lane_AE7B(long a_live, int *ar2_in, int *ar3_live)
{
    if ((*(volatile int *)0x2628 & 512) != 0) {            /* bitf; bc tc */
        frag_388C();                                       /* b 0x388c */
        return;
    }
    if ((*(volatile int *)0x2629 & 4096) != 0) {           /* bitf; bc tc */
        frag_388C();                                       /* b 0x388c */
        return;
    }
    frag_389C(a_live, ar2_in, ar3_live);                   /* b 0x389c */
}

void lane_AE8E(int *ar2_in)
{
    long a;
    long b;
    int *ar2 = ar2_in;   /* entry AR2 (caller-live, flagged) */
    int *ar3;

    a = (long)*(volatile int *)0x2613;                     /* ld *(0x2613),a */
    ar3 = (int *)(long)16128;                              /* stm #16128,ar3 */
    b = a - 512L;                                          /* sub #512,a,b */
    if (b < 0L)                                            /* bc 0xae9d,blt */
        goto stores;
    a -= 975L;                                             /* sub #975,a */
    /* nop; nop (xc delay, always run) */
    if (a < 0L)                                            /* xc 2,alt */
        ar3 = (int *)(long)16130;                          /* stm #16130,ar3 */
stores:
    *ar2++ = *ar3++;                                       /* mvdd *ar3+,*ar2+ */
    *ar2++ = *ar3++;                                       /* mvdd *ar3+,*ar2+ */
    /* ret */
}

void lane_AE87(long a_live, int *ar2_in, int *ar3_live)
{
    (void)a_live;
    (void)ar3_live;
    sub_0596();                                            /* call 0x596 */
    if (*(volatile int *)0x262B == 0) {                    /* cmpm; bc tc */
        frag_AEA0();                                       /* b 0xaea0 */
        return;
    }
    lane_AE8E(ar2_in);
}
