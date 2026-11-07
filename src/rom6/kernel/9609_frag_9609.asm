; ROM6 0x9609 FRAG_9609 -- 10w, symbols.yaml data_word.
; Evidence: Bound 9609-9612 (10w; exit BD F273@960F->9667 + operand 9610 + delays 9611-9612 (mvmd 2w), byte-verified; exit scan clean); entry bc F84B@95FB->9609 byte-verified (cond blt, from d
; Pool: bit-reversed AR4-advance store (*ar4+%, advance ungrounded) + delayed branch; stays .asm, bytes verified.
; ORIGIN 0x9609
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,*ar4+%
	add    #2,a
	stl    a,*(0x20fd)
	ld     #5,a
	bd     0x9667
	mvmd   ar4,0x21fa
