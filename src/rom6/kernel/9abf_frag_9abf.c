/* ROM6 0x9ABF 9ABF_FRAG_9ABF -- 19w (Pool).
 * Verified encoding: src/rom6/kernel/9abf_frag_9abf.asm (recombine MATCH).
 * ORIGIN 0x9ABF
 * EXPECT: F77F FA08 9ACD 7710 0001 69F8 20FF 8000 47F8 000B E5C9 6DC2 F073 9AD2 F310 0001 47F8 000B E5C9
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: BCD on carry flag (carry unbound) + RPTBD lane
 * (see src/rom6/kernel/9abf_frag_9abf.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
