; ROM6 0x2D8B FRAG_2D8B -- 4w, symbols.yaml data_word.
; Evidence: Bound 2D8B-2D8E (4w; exit RET FC00@2D8E byte-verified, exit scan clean; micro-span); entries bc F844@2D80->2D8B byte-verified (from ISR_2D5E [2D5E-2D8A] tail — abuts at 2D8A|2D8B, 
; ORIGIN 0x2D8B
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #17,b
	call   0x4590
	ret
