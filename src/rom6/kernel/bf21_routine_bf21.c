/* ROM6 0xBF21 ROUTINE_BF21 -- 44w butterfly/post section.
 * Verified encoding: src/rom6/kernel/bf21_routine_bf21.asm (recombine MATCH).
 * ORIGIN 0xBF21
 * EXPECT: F074 06DE F074 BE22 ED01 7719 0000 7710 0002 771A 003E 7717 B5DC F070 0005 7197 0012 4492 C8CA 8696 ED00 F272 BF45 7710 0003 A201 0242 868D A145 0342 8796 A001 0242 8694 A35C 0342 878F A145 0342 8796 A001 0242 8694 FC00
 *
 * Intent: Calls sub_06DE (low-zone unsourced, flagged) and
 * BUTTERFLY_BE22; ASM-reg = 1; BK = 0; AR0 = 2 (delay slot
 * value, out flagged); BRC = 62; AR7 = -18980. 6x AR2 =
 * *(AR7++) (rpt #5 long form; MVDK to MMR 0x12 = AR2 per
 * C54x map). A = *(AR2++)<<16 (SXM dark, flagged);
 * parallel *(AR4++) = A-low with A = *(AR2) reloaded (AR2
 * frozen by +0%, BK = 0 per oracle indirect_circular;
 * AR4/AR6/AR2/AR3/AR5/AR7 dark, flagged); *(AR6++) = bits
 * 31-16 of (A<<1) (sth asm-reg = 1, flagged); ASM-reg = 0.
 * RPTBD block, 63x (exact BRC+1 incl. wrap; BRC known 62):
 * A = *(AR2) - *(AR3) (sub dual); A += *(0x42)
 * zero-extended (adds per oracle op_adds_smem; OVM
 * saturation flagged); *(AR5--) = A-high (sth asm-reg 0,
 * ASM dark flagged); B = *(AR2--) + *(AR3--); B += cell;
 * *(AR6++) = B-high; A = *(AR2) + *(AR3); A += cell;
 * *(AR4++) = A-high; B = *(AR3--) - *(AR2) (AR2 frozen %);
 * B += cell; *(AR7--) = B-high; B = *(AR2--) + *(AR3--);
 * B += cell; *(AR6++) = B-high; A = *(AR2) + *(AR3);
 * A += cell; *(AR4++) = A-high; repeat. Net per pass AR2
 * -2, AR3 -3, AR5/AR7 -1, AR4/AR6 +2. ADD/SUB dual
 * sign-extension SXM dark flagged. A/B entry dead; out
 * cells/ARs/ASM-reg.
 * EXPECT from the image.
 */
void routine_BF21(void)
{
    long a;
    long b;
    int *ar2;  /* (dark base, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;  /* live-in (dark, flagged) */
    int *ar5;  /* live-in (dark, flagged) */
    int *ar6;  /* live-in (dark, flagged) */
    int *ar7;
    int asm_reg;
    int i;

    sub_06DE();                                              /* call 0x6de (low-zone, flagged) */
    butterfly_BE22();                                        /* call 0xbe22 */
    asm_reg = 1;                                             /* ld #1,asm */
    /* stm #0,bk; stm #2,ar0 (outs, flagged) */
    /* stm #62,brc */
    ar7 = (int *)-18980;                                     /* stm #-18980,ar7 */
    for (i = 0; i < 6; i++)                                  /* rpt #5 long (k+1) */
        ar2 = (int *)(long)*ar7++;                           /* mvdk *ar7+,0x12 (AR2 = *(AR7++)) */
    a = (long)*ar2++ << 16;                                  /* ld *ar2+,16,a (SXM dark) */
    *ar4++ = (int)(a & 0xFFFFL);                             /* st a,*ar4+ (parallel) */
    a = (long)*ar2;                                          /* ld *ar2+0%,a (frozen, BK = 0) */
    *ar6++ = (int)(((a << 1) >> 16) & 0xFFFFL);              /* sth a,asm,*ar6+ (asm-reg 1, flagged) */
    asm_reg = 0;                                             /* ld #0,asm */
    /* rptbd 0xbf45: stm #3,ar0 delay runs once (out, flagged) */
    for (i = 0; i < 63; i++) {                               /* (BRC+1; BRC known 62) */
        a = (long)*ar2 - (long)*ar3;                         /* sub *ar2,*ar3,a (SXM dark) */
        a += (unsigned int)*(volatile int *)0x42;            /* adds 0x42,a (zero-ext; OVM-sat flagged) */
        *ar5-- = (int)((a >> 16) & 0xFFFFL);                 /* sth a,asm,*ar5- */
        b = (long)*ar2-- + (long)*ar3--;                     /* add *ar2-,*ar3-,b */
        b += (unsigned int)*(volatile int *)0x42;            /* adds 0x42,b */
        *ar6++ = (int)((b >> 16) & 0xFFFFL);                 /* sth b,asm,*ar6+ */
        a = (long)*ar2 + (long)*ar3;                         /* add *ar2,*ar3,a */
        a += (unsigned int)*(volatile int *)0x42;            /* adds 0x42,a */
        *ar4++ = (int)((a >> 16) & 0xFFFFL);                 /* sth a,asm,*ar4+ */
        b = (long)*ar3-- - (long)*ar2;                       /* sub *ar3-,*ar2+0%,b (AR2 frozen) */
        b += (unsigned int)*(volatile int *)0x42;            /* adds 0x42,b */
        *ar7-- = (int)((b >> 16) & 0xFFFFL);                 /* sth b,asm,*ar7- */
        b = (long)*ar2-- + (long)*ar3--;                     /* add *ar2-,*ar3-,b */
        b += (unsigned int)*(volatile int *)0x42;            /* adds 0x42,b */
        *ar6++ = (int)((b >> 16) & 0xFFFFL);                 /* sth b,asm,*ar6+ */
        a = (long)*ar2 + (long)*ar3;                         /* add *ar2,*ar3,a */
        a += (unsigned int)*(volatile int *)0x42;            /* adds 0x42,a */
        *ar4++ = (int)((a >> 16) & 0xFFFFL);                 /* sth a,asm,*ar4+ */
    }
    /* ret */
    (void)asm_reg;
}
