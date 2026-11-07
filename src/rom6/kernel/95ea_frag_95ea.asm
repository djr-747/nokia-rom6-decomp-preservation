; ROM6 0x95EA FRAG_95EA -- 9w, symbols.yaml data_word.
; Evidence: Bound 95EA-95F2 (9w; exit BD F273@95EF->9667 + operand 95F0 + delays 95F1-95F2 (mvmd 2w), byte-verified; exit scan clean); entry bc F84D@95D0->95EA byte-verified (cond, from dark a
; Pool: bit-reversed AR4-advance store (*ar4+%, advance ungrounded) + delayed branch; stays .asm, bytes verified.
; ORIGIN 0x95EA
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #-1,*(0x20fd)
	stl    a,*ar4+%
	ld     #3,a
	bd     0x9667
	mvmd   ar4,0x21fa
