; ROM6 0x43CD FRAG_43CD -- 6w, symbols.yaml data_word.
; Evidence: Bound 43CD-43D2 (6w; exit RET FC00@43D2 byte-verified, exit scan clean; micro-span); entries FOUR B F073@02/14/16/18->43CD byte-verified (block08 head branch sled — 4 dispatch bran
; ORIGIN 0x43CD
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x2e2f
	ld     #8,b
	call   0x4590
	ret
