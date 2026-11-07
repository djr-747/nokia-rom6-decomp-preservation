; ROM6 0x95E2 FRAG_95E2 -- 8w, symbols.yaml data_word.
; Evidence: Bound 95E2-95E9 (8w; exit B F073@95E8->9667 + operand 95E9, byte-verified; exit scan clean); entry bc F84D@95DA->95E2 byte-verified (cond, from dark arm 95CA-95E1 — thin dark-src e
; ORIGIN 0x95E2
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #-1,*(0x20fd)
	sftl   a,8
	stl    a,*ar4
	ld     #1,a
	b      0x9667
