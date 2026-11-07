; ROM6 0x4578 FRAG_4578 -- 7w, symbols.yaml data_word.
; Evidence: Bound 4578-457E (7w; exit RET FC00@457E byte-verified, exit scan clean; minimal cell per A3CE precedent); post-RET head (FC00@4577 = FRAG_456A exit, CODE); zero exterior refs; HYPO
; ORIGIN 0x4578
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar3,b
	call   0x4055
	stl    a,*ar4
	stm    #0,ar6
	ret
