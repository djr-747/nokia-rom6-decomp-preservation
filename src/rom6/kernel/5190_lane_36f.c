/* ROM6 ORIGIN 0x5190 (60w): LANE_36F -- two tune-cell scan lanes.
 * Verified encoding: src/rom6/kernel/5190_lane_36f.asm (recombine MATCH).
 * ORIGIN 0x5190
 * EXPECT: 10F8 036F F845 51AD 8811 7712 0370 11F8 2F62 F330 00FF 6D89 6F82 0C58 F030 00FF F620 F845 51AD 1092 F030 00FF F620 F845 51AD 6C89 519C F073 51D4 10F8 0375 F845 51CC 8811 7712 0376 6FF8 2F61 0D48 F330 FF00 6FF8 2F62 0C58 F030 00FF 6D89 F500 F330 FFFF 1292 F620 F845 51D0 6C89 51C2 10F8 0374 F845 51D4
 *
 * Intent: Lane 36F scans table 0x370 for the low byte of cell 0x2F62.
 * A = *0x36F; nonzero (bc aeq) chains to lane 375. Else AR1 = A-low
 * (stlm a,ar1; 16-bit wrap modeled unsigned-exact), AR2 = 880,
 * B = *0x2F62 & 255; pre-step AR1 (mar *ar1-), then per pass:
 * A = (*AR2)>>8 & 255 (LD-shifted load; low 8 exact under either SXM
 * extension, oracle op_ld_smem shift forms), A -= B, match chains to
 * lane 375; A = (*AR2++) & 255, A -= B, match chains to lane 375;
 * banz *ar1- tests-then-decrements (taken = nonzero, always decrements,
 * 3306 precedent; unsigned models the 16-bit AR wrap exactly).
 * Exhaustion falls to b 0x51d4 (miss sink, tail-called). Lane 375:
 * A = *0x375; zero jumps to the hit tail (bc 0x51cc,aeq, tail-called).
 * Else AR1 = A-low, AR2 = 886, B = (*0x2F61)<<8 & 0xFF00 (LD-shift left;
 * low 16 extension-independent, oracle op_logical_immediate zero-extend
 * clears high/guard at the AND); per pass: A = (*0x2F62)>>8 & 255,
 * AR1 pre-step, B += A (add a,b), B &= 0xFFFF (and #-1,b),
 * A = zero-extended *AR2++ (ldu, oracle op_ldu), A -= B, match chains
 * to FRAG_51D0 (tail-called); banz as above. Exhaustion: A = *0x374,
 * zero goes to the miss sink, else falls to the hit tail (both
 * tail-called). No own RET: every exit is a taken branch. A/B internal;
 * AR4 caller-live (never set in-span): explicit par4 passed through to
 * the hit/sink tails. No SXM flag: every shifted load is AND-masked
 * before any test, so the masked low bits are extension-independent and
 * the ANDs clear guard/high (full-40 zero-extended immediate, oracle
 * op_logical_immediate). B-out modeled as int return, matching the
 * frag_51D0 cluster convention.
 * Bound 5190-51CB (falls/abuts HIT_51CC at 51CC). Entry 5190 from
 * ROUTINE_516A (bc F845@518A).
 */
extern int hit_51CC(int *par4);
extern int miss_sink_51D4(int *par4);
extern int frag_51D0(int *par4);

int lane_36F(int *par4)
{
    long a;
    long b;
    unsigned ar1;
    int *ar2;

    a = (long)*(volatile int *)0x036F;                    /* ld *(0x36f),a */
    if (a != 0)                                           /* bc aeq */
        goto lane_375_51AD;
    ar1 = (unsigned)(a & 0xFFFF);                         /* stlm a,ar1 */
    ar2 = (int *)880;                                     /* stm #880,ar2 */
    b = (long)*(volatile int *)0x2F62;                    /* ld *(0x2f62),b */
    b &= 255L;                                            /* and #255,b */
    ar1--;                                                /* mar *ar1- */
    for (;;) {                                            /* 519C scan */
        a = (long)*ar2 >> 8;                              /* ld *ar2,-8,a */
        a &= 255L;                                        /* and #255,a */
        a -= b;                                           /* sub b,a */
        if (a == 0)                                       /* bc aeq */
            goto lane_375_51AD;
        a = (long)*ar2++;                                 /* ld *ar2+,a */
        a &= 255L;                                        /* and #255,a */
        a -= b;                                           /* sub b,a */
        if (a == 0)                                       /* bc aeq */
            goto lane_375_51AD;
        {                                                 /* banz */
            int taken = (ar1 != 0);
            ar1--;
            if (!taken)
                break;
        }
    }
    return miss_sink_51D4(par4);                           /* b 0x51d4 */
lane_375_51AD:                                            /* 51AD lane */
    a = (long)*(volatile int *)0x0375;                    /* ld *(0x375),a */
    if (a == 0)                                           /* bc 0x51cc,aeq */
        return hit_51CC(par4);
    ar1 = (unsigned)(a & 0xFFFF);                         /* stlm a,ar1 */
    ar2 = (int *)886;                                     /* stm #886,ar2 */
    b = (long)*(volatile int *)0x2F61 << 8;               /* ld *(0x2f61),8,b */
    b &= 0xFF00L;                                         /* and #-256,b */
    for (;;) {                                            /* 51C2 scan */
        a = (long)*(volatile int *)0x2F62 >> 8;           /* ld -8 */
        a &= 255L;                                        /* and #255,a */
        ar1--;                                            /* mar *ar1- */
        b += a;                                           /* add a,b */
        b &= 0xFFFFL;                                     /* and #-1,b */
        a = (long)(unsigned)*ar2++;                       /* ldu *ar2+,a */
        a -= b;                                           /* sub b,a */
        if (a == 0)                                       /* bc 0x51d0,aeq */
            return frag_51D0(par4);
        {                                                 /* banz */
            int taken = (ar1 != 0);
            ar1--;
            if (!taken)
                break;
        }
    }
    a = (long)*(volatile int *)0x0374;                    /* 51C8 ld */
    if (a == 0)                                           /* bc 0x51d4,aeq */
        return miss_sink_51D4(par4);
    return hit_51CC(par4);                                /* fall to 51CC */
}
