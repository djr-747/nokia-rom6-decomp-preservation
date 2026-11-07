; ROM6 0xA25A FRAG_A25A -- 5w, symbols.yaml data_word.
; Evidence: Bound A25A-A25E (5w, exit FC00@A25E byte-verified); bacc-table arm entry (A255-A259 table slot 0 lists A25A; DISPATCH_A249 table, bytes verified); body F274 A2B9 + stm + ret (calld
; ORIGIN 0xA25A
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8813,ar5
	ret
