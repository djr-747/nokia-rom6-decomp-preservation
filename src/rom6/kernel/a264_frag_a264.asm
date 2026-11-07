; ROM6 0xA264 FRAG_A264 -- 5w, symbols.yaml data_word.
; Evidence: Bound A264-A268 (5w, exit FC00@A268 byte-verified); bacc-table arm entry (table slot 2); body F274 A2B9 + stm + ret; HYPOTHESIS.
; ORIGIN 0xA264
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8797,ar5
	ret
