; ROM6 0x95B8 FRAG_95B8 -- 7w, symbols.yaml data_word.
; Evidence: Bound 95B8-95BE (7w; exit BD F273@95BB->9667 + operand 95BC + delays 95BD-95BE (stl 2w), byte-verified; exit scan clean); entry bc F84D@95B3->95B8 byte-verified (cond, from dark ar
; ORIGIN 0x95B8
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,*ar4
	ld     #1,a
	neg    a,b
	bd     0x9667
	stl    b,*(0x20fd)
