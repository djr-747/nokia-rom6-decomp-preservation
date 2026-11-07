; ROM6 0x965F FRAG_965F -- 8w, symbols.yaml data_word.
; Evidence: Bound 965F-9666 (8w; exit BD F273@9663->9667 + operand 9664 + delays 9665-9666 (mvmd 2w), byte-verified; exit scan clean); entry bc F830@9654->965F byte-verified (cond tc, from dar
; Pool: bit-reversed AR4-advance store (*ar4+%, advance ungrounded) + delayed branch; stays .asm, bytes verified.
; ORIGIN 0x965F
	.sect ".text"
	.mmregs
	.global _start
_start:
	sftl   a,-8
	or     *ar4,a
	stl    a,*ar4+%
	ld     #6,a
	bd     0x9667
	mvmd   ar4,0x21fa
