; ROM6 0xB41C FRAG_B41C -- 21w, symbols.yaml data_word.
; Evidence: Bound B41C-B430 (21w; exit RET FC00@B430 objdump-aligned); 3x INTERIOR F074 call entries B3F2/B405/B419 (inside ROUTINE_B3E2 span: B3F2 byte-verified, B405/B419 team+critic-verifie
; ORIGIN 0xB41C
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-19120,ar5
	stm    #-19099,ar6
	ld     #-19108,a
	call   0xaeec
	call   0xaf40
	call   0xa582
	stm    #-19120,ar3
	stm    #-19099,ar6
	ld     #-19108,a
	call   0xaf16
	ret
