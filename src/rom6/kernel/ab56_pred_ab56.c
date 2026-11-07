/* ROM6 0xAB56 PRED_AB56 -- 34w predicate/classify lane.
 * Verified encoding: src/rom6/kernel/ab56_pred_ab56.asm (recombine MATCH).
 * ORIGIN 0xAB56
 * EXPECT: F3F0 F820 AB76 8914 1083 8812 0983 F685 E725 F010 0096 F843 AB67 4819 FD4E F484 F500 F685 F010 0001 FC47 FD4E 6DD2 FD7E E530 F010 0003 FD4B 6DC2 FD46 E742 4912 8183 FC00
 *
 * Intent: Threshold-classify lane with circular cursor
 * motion. B >>>= 16 (SFTL logical); TC clear exits to the
 * AB76 tail (BC NTC -- skips the body, joins stl/ret);
 * else AR4 = BL; A = *AR3; AR2 = AL; B -= *AR3 << 16;
 * A = |B|; AR5 = AR2; A -= 150; A < 0 joins the ABS leg at
 * AB67 (BC ALT); else A = BK (dark, flagged), XC BGT
 * negates A when B > 0, B += A. ABS leg: A = |B|, A -= 1;
 * RETC ALEQ returns when A <= 0 (immediate, no delays);
 * XC BGT advances AR2 circularly (BK dark, flagged) when
 * B > 0; XC BGT+BOV copies *AR5 to *AR2 when B > 0 (BOV
 * overflow qualifier: no oracle input carrier per
 * op_xc.c -- flagged); A -= 3; XC BLT retreats AR2
 * circularly when B < 0; XC AGT restores AR2 = AR4 when
 * A > 0; B = AR2 (LDM, SXM-dark, flagged). Tail (both
 * paths): store BL to *AR3, return. Entry F3F0 F820 AB76
 * branch-entered; callers F274 @AB48/AB51 (interior to
 * AB2C) per asm header. AR3 live-in (dark, flagged).
 * (Wave-13: XC = execute-when-true; RETC immediate;
 * EXPECT from the image.)
 */
void pred_AB56(void)
{
    long a;
    long b;
    int *ar2;
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;
    int *ar5;
    int tc;  /* TC live-in (dark, flagged) */
    int bk = 0;  /* BK live-in (dark, flagged) */

    b = (long)(((unsigned long)b >> 16) & 0xFFFFL);            /* sftl b,-16 */
    if (!tc)                                                   /* bc 0xab76,ntc */
        goto ltail;
    ar4 = (int)(b & 0xFFFFL);                                  /* stlm b,ar4 */
    a = (long)*ar3;                                            /* ld *ar3,a */
    ar2 = (int)(a & 0xFFFFL);                                  /* stlm a,ar2 */
    b -= (long)*ar3 << 16;                                     /* sub *ar3,b */
    a = (b < 0) ? -b : b;                                      /* abs b,a */
    ar5 = ar2;                                                 /* mvmm ar2,ar5 */
    a -= 150;                                                  /* sub #150,a */
    if (a < 0)                                                 /* bc 0xab67,alt */
        goto labs;
    a = (long)bk;                                              /* ldm bk,a (dark) */
    if (b > 0)                                                 /* xc 1,bgt */
        a = -a;                                                /* neg a */
    b += a;                                                    /* add a,b */
labs:
    a = (b < 0) ? -b : b;                                      /* abs b,a (AB67 join) */
    a -= 1;                                                    /* sub #1,a */
    if (a <= 0)                                                /* rc aleq (RETC, immediate) */
        return;
    if (b > 0)                                                 /* xc 1,bgt */
        ar2++; /* mar *ar2+% (circular BK dark, flagged) */
    if (b > 0) /* + BOV qualifier (oracle-unbound, flagged) */ /* xc 1,bgt,bov */
        *ar2 = *ar5;                                           /* mvdd *ar5,*ar2 */
    a -= 3;                                                    /* sub #3,a */
    if (b < 0)                                                 /* xc 1,blt */
        ar2--; /* mar *ar2-% (circular, flagged) */
    if (a > 0)                                                 /* xc 1,agt */
        ar2 = ar4;                                             /* mvmm ar4,ar2 */
    b = (long)ar2;                                             /* ldm ar2,b (SXM-dark, flagged) */
ltail:
    *ar3 = (int)(b & 0xFFFFL);                                 /* stl b,*ar3 (AB76 tail join) */
    /* ret */
}
