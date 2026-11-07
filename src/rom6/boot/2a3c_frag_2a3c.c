/* ROM6 0x2A3C FRAG_2A3C -- 27w.
 * Verified encoding: src/rom6/boot/2a3c_frag_2a3c.asm (recombine MATCH).
 * ORIGIN 0x2A3C
 * EXPECT: 6183 0040 F820 2A57 F074 3EE1 00F8 3EE7 6FF8 036A 0D20 7683 0080 7713 1274 7712 126E FD4E F640 57F8 3EF8 4F83 7692 0100 808A F073 2A8A
 *
 * Intent: Boot flag-lane (chained from FRAG_2A1C interior via 2A1F/2A23
 * bc entries). TC = (*AR3-entry & 64) != 0 (bitf; 5d38 polarity
 * precedent); clear exits to FRAG_2A57 (bc 0x2a57,ntc; C: frag_2A57).
 * Else A = port-13 stable reading (call 0x3ee1; C:
 * port13_stable_read; B-out 0; ARs preserved per its C signature, so
 * the st below targets entry AR3 -- noted). A += *(0x3EE7) (add;
 * SXM assumed per the ADD-Smem convention, flagged); B = A -
 * *(0x36A) (sub Smem,src,dst; fits long: 14-bit reading + 16-bit
 * cells). MEM[*AR3-entry] = 128 (st). AR3 = 4724, AR2 = 4718 (stm
 * reseats, caller-derivable constants, not carried). B > 0 reloads A
 * (xc 1,bgt over ld b,a: 1-word skip, exact). B = 32-bit MEM[0x3EF8]
 * (dld, MSW-first per the 56fc precedent). MEM[4724] = B-high,
 * MEM[4725] = B-low (dst b,*ar3, no step per the 3d79 order
 * precedent). MEM[4718] = 256 then MEM[4719] = A-low, AR2 back to
 * 4718 (st/stl pair). Tails into the 2A8A span at 2A8A (b 0x2a8a;
 * mid-span entry, frag_2A8A per the 5371 precedent).
 */
extern int port13_stable_read(void);                 /* C: 3ee1_port13_stable_read */
extern void frag_2A57(void);                         /* C name, linked later */
extern void frag_2A8A(void);                         /* mid-span entry */

void frag_2A3C(int *ar3_in)
{
    long a;
    long b;
    int *ar3 = ar3_in;
    int *ar2;
    if ((*ar3 & 64) == 0) {                          /* bitf *ar3,#64; bc ntc */
        frag_2A57();
        return;
    }
    a = (long)port13_stable_read();                  /* call 0x3ee1 */
    a += (long)*(volatile int *)0x3EE7;              /* add *(0x3ee7),a */
    b = a - (long)*(volatile int *)0x36A;            /* sub *(0x36a),a,b */
    *ar3 = 128;                                      /* st #128,*ar3 */
    ar3 = (int *)(long)4724;                         /* stm #4724,ar3 */
    ar2 = (int *)(long)4718;                         /* stm #4718,ar2 */
    if (b > 0)                                       /* xc 1,bgt */
        a = b;                                       /* ld b,a */
    b = ((long)*(volatile int *)0x3EF8 << 16) |      /* dld *(0x3ef8),b */
        ((unsigned)*(volatile int *)0x3EF9 & 0xFFFF);
    *ar3 = (int)((b >> 16) & 0xFFFF);                /* dst b,*ar3 (high) */
    *(ar3 + 1) = (int)(b & 0xFFFF);                  /* dst (low) */
    *ar2++ = 256;                                    /* st #256,*ar2+ */
    *ar2-- = (int)(a & 0xFFFF);                      /* stl a,*ar2- */
    frag_2A8A();                                     /* b 0x2a8a */
}
