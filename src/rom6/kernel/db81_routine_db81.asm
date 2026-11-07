; ROM6 0xDB81 ROUTINE_DB81 -- 11w, symbols.yaml data_word.
; Evidence: Bound DB81-DB8B (11w; exit retd FE00@DB89 + delays DB8A-DB8B included per convention; exit scan clean); entries call F074@D4C4 + calld F274@D519->DB81 byte-verified (both head+2) +
; ORIGIN 0xDB81
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdm   0xa63,ar0
	cmpm   0x63,#27
	stl    a,*ar0(0xb14)
	addm   #1,0x63
	retd
	xc     1,tc
	sth    a,0x63
