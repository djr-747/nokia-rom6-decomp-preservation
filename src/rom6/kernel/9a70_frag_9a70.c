/* ROM6 0x9A70 FRAG_9A70 -- 18w.
 * Verified encoding: src/rom6/kernel/9a70_frag_9a70.asm (recombine MATCH).
 * ORIGIN 0x9A70
 * EXPECT: 10F8 2510 F030 00F0 F010 00D0 F844 9A82 12F8 20FA F010 0002 F842 9A82 1083 F010 0032 FC43
 *
 * Intent: Triple gate into FRAG_9A82. A = cell0x2510 & 240 - 208,
 * nonzero tail-enters 9A82 (bc aneq); A = unsigned cell0x20FA - 2
 * (ldu, 3691 precedent), non-negative tail-enters 9A82 (bc ageq);
 * A = *AR3 - 50, negative near-returns (rc alt, 454f/ab25 precedent),
 * else falls into 9A82. AND imm zero-extends (imm positive, exact).
 * frag_9A82 has .asm only (forward extern, 89b3 precedent); its head
 * calls dark 0x710 before clobbering A, so 710 may consume the passed
 * A (flagged). Bound 9A70-9A81, falls into 0x9A82.
 */
extern void frag_9A82(long a_live); /* joins 9a82_frag_9a82; see docs/evidence/extern-triage.md */

void frag_9A70(int *par3)
{
    long a;
    a = (long)*(volatile int *)0x2510 & 240;       /* ld; and #240,a */
    a -= 208;                                      /* sub #208,a */
    if (a != 0) {                                  /* bc 0x9a82,aneq */
        frag_9A82(a);
        return;
    }
    a = (unsigned long)(unsigned)*(volatile int *)0x20FA; /* ldu *(0x20fa),a */
    a -= 2;                                        /* sub #2,a */
    if (a >= 0) {                                  /* bc 0x9a82,ageq */
        frag_9A82(a);
        return;
    }
    a = (long)*par3;                               /* ld *ar3,a */
    a -= 50;                                       /* sub #50,a */
    if (a < 0)                                     /* rc alt */
        return;
    frag_9A82(a);                                  /* fall-through to 0x9a82 */
}
