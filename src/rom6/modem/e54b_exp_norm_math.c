/* ROM6 0xE54B SUB_E54B -- 56w (span E54B-E582, four entries).
 * Verified encoding: src/rom6/modem/e54b_exp_norm_math.asm (recombine MATCH).
 * ORIGIN 0xE54B
 * EXPECT: F847 E568 F48E E91E 090E 817D 617D 0001 F77F F48F F300 0001 FD20 F47F F477 F784 817D F160 FADA 8312 4808 F47F 807E 4592 428A 337E FE00 307D F68F F062 3FFF FE00 F040 FFFF F847 E581 F48E E91E 090E 817D F48F F477 F160 FAA9 8312 4808 F47F 807E 4592 428A 337E FE00 F650 3C7D E800 FC00
 *
 * Intent: Modem exp/norm/scale engine (callers E08C/E125). Four
 * entries (retd always returns, so post-retd words are separate
 * entries per the 2917 mesh precedent). Head frag_E54B: A <= 0
 * joins LE568 (bc aleq). Else exp/norm lane: T = exp(A)
 * (redundant-sign-bits minus 8 per op_exp: T = lz32 - 1, A == 0
 * gives 0, bf8c derivation); B = 30 (ld); B -= *(0x0E) (sub);
 * MEM[0x7D] = B-low (stl); TC = (MEM[0x7D] & 1) != 0 (bitf
 * direct-cell, 5d38 polarity); B >>= 1 arith (sfta b,-1, exact --
 * SFTA always arithmetic); A <<= T signed (norm a, op_norm_acc,
 * 40-bit wrap flagged); B += 1 (add); TC clear halves A once (xc
 * 1,ntc over sfta a,-1; TC preserved by sfta); A >>= 9 arith
 * (sfta a,-9); B = -B (neg; LONG_MIN edge flagged); MEM[0x7D] =
 * B-low; B = A + (-1318 << 16) (add #-1318,16,a,b); ST1 =
 * B-high (sth b,0x12: HW status write, volatile + emulator
 * ground truth, flagged); A = A-low (ldm al,a: a &= 0xFFFF,
 * exact); A >>= 1 arith; MEM[0x7E] = A-low; B = *AR2++ << 16
 * (ld); A = B - (*AR2-- << 16) (sub dual-shifted, 50B2
 * precedent); B -= MEM[0x7E] x A-high (masa 0x7e,b: B minus Smem
 * times A-high per the op_masa_smem core, FRCT/OVM/40-bit
 * flagged); retd with delays T = MEM[0x7D], A = B << T signed
 * (norm b,a: NORM_ACC row covers src/dst, op_norm_acc), then
 * returns (A/B/T outs lane-computed, void + flagged).
 * LE568 entry (bc target; B/T = entry residues, explicit params):
 * A = B << T (norm b,a); A = 16383 << 16 (ld); retd with delay
 * A = -1 (or #-1,a saturate idiom, exact), returns (A-out = -1).
 * LE56E entry (hypothesis: post-retd word, no fall-through,
 * flagged): A <= 0 joins LE581 (bc aleq, A = entry residue).
 * Else the lane-2 exp/norm/scale (same shape as lane 1 with B =
 * A + (-1367 << 16)); retd with delays A = B >> 16 arith (ld
 * b,-16,a; SXM dark-modem, arith assumed per the modem bfaa
 * convention, flagged) + A += MEM[0x7D] << 16 (add), returns.
 * LE581 entry (bc target; A = lane-2 residue): A += MEM[0x7D]
 * << 16 (dead: overwritten next, faithful sequence); A = 0 (ld);
 * return (A-out = 0). AR2 read-only (*ar2+/- net 0; local copy,
 * no writeback). A-in/B-in/T-in explicit (lane-dependent use,
 * header notes which).
 */
void sub_E54B(long a_in, long b_in, int *ar2_in, int t_in)
{
    long a = a_in;
    long b = b_in;
    int *ar2 = ar2_in;
    int t = t_in;
    int tc;
    int lz;
    int k;
    unsigned long ub;
    if (a <= 0)                                      /* bc 0xe568,aleq */
        goto le568;
    /* lane 1 */
    if (b == 0) {                                    /* exp a (op_exp: 0 -> 0) */
        t = 0;
    } else {
        ub = (unsigned long)(a >= 0 ? a : -a);
        lz = 0;
        for (k = 31; k >= 0; k--) {
            if ((ub >> k) & 1UL)
                break;
            lz++;
        }
        t = lz - 1;
    }
    b = 30;                                          /* ld #30,b */
    b -= (long)*(volatile int *)0xE;                 /* sub 0x0e,b */
    *(volatile int *)0x7D = (int)(b & 0xFFFF);       /* stl b,0x7d */
    tc = (*(volatile int *)0x7D & 1) != 0;           /* bitf 0x7d,#1 */
    b >>= 1;                                         /* sfta b,-1 (arith, exact) */
    if (t >= 0) {                                    /* norm a */
        a <<= t;
    } else {
        a = (long)((unsigned long)a >> (unsigned)(-t));
    }
    b += 1;                                          /* add #1,b */
    if (!tc)                                         /* xc 1,ntc */
        a >>= 1;                                     /* sfta a,-1 (arith) */
    a >>= 9;                                         /* sfta a,-9 (arith) */
    b = -b;                                          /* neg b (edge flagged) */
    *(volatile int *)0x7D = (int)(b & 0xFFFF);       /* stl b,0x7d */
    b = a + (-1318L << 16);                          /* add #-1318,16,a,b */
    *(volatile int *)0x12 = (int)((b >> 16) & 0xFFFF); /* sth b,0x12 (ST1 write) */
    a &= 0xFFFFL;                                    /* ldm al,a */
    a >>= 1;                                         /* sfta a,-1 */
    *(volatile int *)0x7E = (int)(a & 0xFFFF);       /* stl a,0x7e */
    b = (long)*ar2++ << 16;                          /* ld *ar2+,16,b */
    a = b - ((long)*ar2-- << 16);                    /* sub *ar2-,16,b,a */
    b -= (long)*(volatile int *)0x7E * (a >> 16);    /* masa 0x7e,b (FRCT/OVM flagged) */
    t = *(volatile int *)0x7D;                       /* retd delay 1: ld 0x7d,t */
    if (t >= 0) {                                    /* retd delay 2: norm b,a */
        a = b << t;
    } else {
        a = (long)((unsigned long)b >> (unsigned)(-t));
    }
    return;                                          /* retd */
le568:
    if (t >= 0) {                                    /* norm b,a (entry B/T) */
        a = b << t;
    } else {
        a = (long)((unsigned long)b >> (unsigned)(-t));
    }
    a = 16383L << 16;                                /* ld #16383,16,a */
    a = -1;                                          /* retd delay: or #-1,a */
    return;                                          /* retd (A-out = -1) */
le56e:
    if (a <= 0)                                      /* bc 0xe581,aleq (entry A) */
        goto le581;
    /* lane 3: lane-2 exp/norm/scale (no bitf/xc/neg steps) */
    if (b == 0) {
        t = 0;
    } else {
        ub = (unsigned long)(a >= 0 ? a : -a);
        lz = 0;
        for (k = 31; k >= 0; k--) {
            if ((ub >> k) & 1UL)
                break;
            lz++;
        }
        t = lz - 1;
    }
    b = 30;                                          /* ld #30,b */
    b -= (long)*(volatile int *)0xE;                 /* sub 0x0e,b */
    *(volatile int *)0x7D = (int)(b & 0xFFFF);       /* stl b,0x7d */
    if (t >= 0) {                                    /* norm a */
        a <<= t;
    } else {
        a = (long)((unsigned long)a >> (unsigned)(-t));
    }
    a >>= 9;                                         /* sfta a,-9 */
    b = a + (-1367L << 16);                          /* add #-1367,16,a,b */
    *(volatile int *)0x12 = (int)((b >> 16) & 0xFFFF); /* sth b,0x12 (ST1 write) */
    a &= 0xFFFFL;                                    /* ldm al,a */
    a >>= 1;                                         /* sfta a,-1 */
    *(volatile int *)0x7E = (int)(a & 0xFFFF);       /* stl a,0x7e */
    b = (long)*ar2++ << 16;                          /* ld *ar2+,16,b */
    a = b - ((long)*ar2-- << 16);                    /* sub *ar2-,16,b,a */
    b -= (long)*(volatile int *)0x7E * (a >> 16);    /* masa 0x7e,b (FRCT/OVM flagged) */
    a = b >> 16;                                     /* retd delay 1: ld b,-16,a (arith assumed) */
    a += (long)*(volatile int *)0x7D << 16;          /* retd delay 2: add 0x7d,16,a */
    return;                                          /* retd */
le581:
    a += (long)*(volatile int *)0x7D << 16;          /* add 0x7d,16,a (dead, faithful) */
    a = 0;                                           /* ld #0,a */
    /* ret (A-out = 0) */
}
