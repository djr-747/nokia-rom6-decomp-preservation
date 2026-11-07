/* ROM6 0xAEA0 FRAG_AEA0 -- 8w.
 * Verified encoding: src/rom6/kernel/aea0_frag_aea0.asm (recombine MATCH).
 * ORIGIN 0xAEA0
 * EXPECT: 7213 265E F495 6DEB FFFE FE00 7313 265E
 *
 * Intent: FRAG_AEA0 cursor rewind with delayed return (8w). AR3 = cell 0x265E (mvdm, local); AR3 -= 2 (mar *+ar3(0xfffe), plain linear offset, no circular flags); cell 0x265E = AR3 in the retd delay slot (always runs); returns. Bound AEA0-AEA7.
 */
void frag_AEA0(void)
{
    int *ar3 = (int *)(long)*(volatile int *)0x265E; /* mvdm */
    /* nop */
    ar3 -= 2;                                      /* mar *+ar3(0xfffe) */
    *(volatile int *)0x265E = (int)(long)ar3;  /* retd delay slot */
    /* retd: return */
}
