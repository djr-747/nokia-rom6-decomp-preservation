/* ROM6 0x5BD9 SUB_5BD9 -- 24w table-scatter engine, one EXPECT.
 * Verified encoding: src/rom6/kernel/5bd9_sub_5bd9.asm (recombine MATCH).
 * ORIGIN 0x5BD9
 * EXPECT: F074 0674 771A 0038 F072 5BEF F55E 8913 F130 0003 F742 890E 320B E90F 6DB3 F782 F793 1983 0584 8183 5694 1095 0017 FC00
 *
 * Intent: Per-pass table scatter over a caller-provided window. Runs dark
 * SUB_0674 (call). BRC = 56 re-arms a 57-iteration RPTB. Per iteration:
 * B = A-live-in >> 2 (ld a,-2,b: LD src,SHFT per op_ld_src_shift,
 * SXM-arithmetic assumed, flagged); AR3 = B-low (stlm); B = A & 3
 * (and #3,a,b: A kept; immediate zero-extended per op_logical_immediate);
 * B <<= 2 (ld b,2,b); T = B-low, so T in {0, 4, 8, 12} from entry-A
 * bits 1:0; ASM = *(DP+0x0B) (ld Smem,ASM; DP = 0 assumed from the
 * SEG_5B26 path -- other callers trace-confirmable; 5-bit field read as
 * signed -16..15, HYPOTHESIS); B = 15; AR3 += AR0 (mar *ar3+0, by-AR0
 * per 4EBC; AR0 caller-live); B = B << ASM (ld b,asm: LD src,ASM[,dst]
 * shifts the copied source by the signed ASM count per op_ld_src_asm;
 * SXM/OVM per 4EBC precedent, flagged); B = ~B (cmpl: full-40-bit NOT
 * per op_cmpl; `& 0xFFFF` keeps low16 exact per 2ACC -- exact here
 * because the following AND clears B-high anyway); B &= *(AR3)
 * (and *ar3,b: Smem zero-extended, high cleared); B += (*(AR4) << T)
 * (add *ar4,ts,b: Xmem SXM-sign-extended per op_add_xmem, flagged);
 * *(AR3) = B-low (stl); AR4 += 1 (dld *ar4+,a post-increment: +1
 * HYPOTHESIS -- dual-access single-modifier reading; result dead, the
 * next op overwrites A); A = *(AR5++) (ld); A += *(DP+0x17)
 * (DP = 0 assumed, flagged). A-live-out (stream tail) unused by the
 * SEG_5B26-path callers (other callers 5B6D/76 trace-confirmable); B/T
 * dead at RET @5BF0; ASM/AR3/AR4/AR5/AR0 caller-live across the call.
 * Callers: calld F274 @5B4D/56 (SEG_5B26 twin tail) + @5B6D/76
 * (FRAG_5B5C/68 twin, interior). Bound 5BD9-5BF0.
 */
extern void sub_0674(void);

void sub_5BD9(long a_live, int *par4, int *par5, int ar0_live)
{
    long a = a_live;
    long b;
    int t;
    int asm_count;
    int ar3;
    int ar0 = ar0_live;
    int k;

    sub_0674();                                        /* call 0x674 */
    /* stm #56,brc re-armed below as the 57-count */
    for (k = 0; k < 57; k++) {                   /* rptb 0x5bef */
        b = a >> 2;                          /* ld a,-2,b (SXM?) */
        ar3 = (int)(b & 0xFFFF);                   /* stlm b,ar3 */
        b = a & 3L;                              /* and #3,a,b */
        b <<= 2;                                 /* ld b,2,b */
        t = (int)(b & 0xFFFF);                     /* stlm b,t */
        asm_count = *(volatile int *)0x0B; /* ld DP+0x0b,asm (DP=0?) */
        asm_count &= 0x1F;                 /* 5-bit field (signed?) */
        if (asm_count >= 16)                       /* HYPOTHESIS */
            asm_count -= 32;
        b = 15;                                            /* ld #15,b */
        ar3 = (ar3 + ar0) & 0xFFFF;                /* mar *ar3+0 */
        b = (asm_count >= 0) ? (b << asm_count) :  /* ld b,asm */
            (b >> -asm_count);                     /* (SXM/OVM noted) */
        b = ~b & 0xFFFF;               /* cmpl (low16 exact per 2ACC) */
        b &= (long)(unsigned)*(volatile int *)ar3; /* and *ar3,b */
        b += (long)*(volatile int *)par4 << t; /* add *ar4,ts,b (SXM?) */
        *(volatile int *)ar3 = (int)(b & 0xFFFF);   /* stl b,*ar3 */
        par4++;                          /* dld *ar4+,a (+1 HYPOTHESIS) */
        a = (long)*par5++;                         /* ld *ar5+,a */
        a += (long)*(volatile int *)0x17;      /* add DP+0x17,a (DP=0?) */
    }
    /* ret @5BF0 (A-live-out noted above) */
}
