; ROM6 0x7EBE BD_7EBE -- 10w (overlap-split wave-12).
; Evidence: Entry frag_7EBE at 0x7EBC (HYPOTHESIS: no in-span caller; direct-entry shape; bacc-lane fall-through possible). T = 0; delayed call to dark 0x7F55 (calld, single complete 2-word delay stm #-20125,ar6, WORD-count clean); T = -12; BRC = -12 (stm pair); unconditional delayed branch to dark 0x7F95 (bd, delay words in the following span, executed, abut). Bound 7EBC-7EC5, exits via the bd.
; ORIGIN 0x7EBC
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #0,t
	calld  0x7f55
	stm    #-20125,ar6
	stm    #-12,t
	bd     0x7f95
