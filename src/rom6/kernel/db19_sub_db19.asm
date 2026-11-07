; ROM6 0xDB19 SUB_DB19 -- 37w, symbols.yaml data_word.
; Evidence: Entry 7711 EB3F 771A 005D; first exit ret FC00 @DB3D; caller F074 @D30D verified; HYPOTHESIS.
; ORIGIN 0xDB19
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-5313,ar1
	stm    #93,brc
	ldm    ar2,a
	add    *ar1,-8,a
	stlm   a,ar3
	ld     *ar1+,t
	stm    #0,ar0
	rptbd  0xdb2f
	bitt   *ar3
	ldm    ar2,a
	add    *ar1,-8,a
	stlm   a,ar3
	xc     1,ntc
	mar    *ar0+
	ld     *ar1+,t
	bitt   *ar3
	ldm    ar2,a
	nop
	xc     1,ntc
	mar    *ar0+
	ldm    ar0,b
	sub    #2,b
	ld     #2,a
	rc     blt
	sub    #14,b
	ld     #1,a
	rc     blt
	ld     #0,a
	ret
