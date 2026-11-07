; ROM6 0x3640 FRAG_3640 -- 34w, symbols.yaml data_word.
; Evidence: Bound 3640-3661 (34w + operand word; exit F073@3660->3664 + operand 3661; +1 fix applied); caller F074@35B5 (slice-verified, consistent with LEAF_35C5 note); branch-entered fragmen
; ORIGIN 0x3640
	.sect ".text"
	.mmregs
	.global _start
_start:
	and    #8,a
	stm    #9536,ar0
	xc     2,aneq
	stm    #9591,ar0
	bitf   *ar3,#4
	bc     0x3667,ntc
	bitf   *ar3,#8
	bc     0x3652,ntc
	orm    #16,*(0x54f)
	and    #8,a
	stm    #9535,ar0
	xc     2,aneq
	stm    #9590,ar0
	ld     *ar4,b
	bitf   *ar3,#2
	bc     0x3662,tc
	and    #-257,b
	b      0x3664
