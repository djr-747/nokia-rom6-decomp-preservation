/* ROM6 0x2A1C FRAG_2A1C -- 32w.
 * Verified encoding: src/rom6/boot/2a1c_frag_2a1c.asm (recombine MATCH).
 * ORIGIN 0x2A1C
 * EXPECT: 60F8 250F 0022 F820 2A3C 6183 0020 F820 2A3C F074 3EE1 00F8 3EE7 6FF8 036A 0D20 7683 0040 7713 1274 7712 126E FD4E F640 57F8 3EF6 4F83 7692 0100 808A F073 2A8A
 *
 * Intent: Boot flag-lane vestibule (2a3c twin; chained from FRAG_2A0E
 * interior via the 2A10 bc entry). TC = (*(0x250F) == 34) (cmpm, 3691
 * precedent); mismatch exits to FRAG_2A3C (bc 0x2a3c,ntc; linked C).
 * TC = (*AR3-entry & 32) != 0 (bitf; 5d38 polarity precedent); clear
 * exits to FRAG_2A3C (bc ntc). Else the 2a3c lane with st #64 (vs
 * 128) and the 32-bit DLD from 0x3EF6 (vs 0x3EF8): A = port-13
 * stable reading (call 0x3ee1; C: port13_stable_read; ARs preserved
 * per its C signature); A += *(0x3EE7) (SXM assumed, flagged);
 * B = A - *(0x36A); MEM[*AR3-entry] = 64; AR3 = 4724, AR2 = 4718
 * (stm reseats, caller-derivable, not carried); B > 0 reloads A (xc
 * 1,bgt, 1-word skip); B = DLD(0x3EF6) MSW-first (56fc precedent);
 * DST B to MEM[4724/4725] (3d79 high-then-low order, no step);
 * MEM[4718] = 256, MEM[4719] = A-low (st/stl pair, AR2 back to
 * 4718). Tails into the 2A8A span (b 0x2a8a; mid-span entry,
 * frag_2A8A per the 5371 precedent). A/B dead after (void).
 */
extern int port13_stable_read(void);                 /* C: 3ee1_port13_stable_read */
extern void frag_2A3C(void);                         /* linked C */
extern void frag_2A8A(void);                         /* mid-span entry */

void frag_2A1C(int *ar3_in)
{
    long a;
    long b;
    int *ar3 = ar3_in;
    int *ar2;
    if (*(volatile int *)0x250F != 34) {              /* cmpm; bc 0x2a3c,ntc */
        frag_2A3C();
        return;
    }
    if ((*ar3 & 32) == 0) {                          /* bitf *ar3,#32; bc ntc */
        frag_2A3C();
        return;
    }
    a = (long)port13_stable_read();                  /* call 0x3ee1 */
    a += (long)*(volatile int *)0x3EE7;              /* add *(0x3ee7),a */
    b = a - (long)*(volatile int *)0x36A;            /* sub *(0x36a),a,b */
    *ar3 = 64;                                       /* st #64,*ar3 */
    ar3 = (int *)(long)4724;                         /* stm #4724,ar3 */
    ar2 = (int *)(long)4718;                         /* stm #4718,ar2 */
    if (b > 0)                                       /* xc 1,bgt */
        a = b;                                       /* ld b,a */
    b = ((long)*(volatile int *)0x3EF6 << 16) |      /* dld *(0x3ef6),b */
        ((unsigned)*(volatile int *)0x3EF7 & 0xFFFF);
    *ar3 = (int)((b >> 16) & 0xFFFF);                /* dst b,*ar3 (high) */
    *(ar3 + 1) = (int)(b & 0xFFFF);                  /* dst (low) */
    *ar2++ = 256;                                    /* st #256,*ar2+ */
    *ar2-- = (int)(a & 0xFFFF);                      /* stl a,*ar2- */
    frag_2A8A();                                     /* b 0x2a8a */
}
