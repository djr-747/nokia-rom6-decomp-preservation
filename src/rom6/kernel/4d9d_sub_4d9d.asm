; ROM6 0x4D9D SUB_4D9D -- 10w, symbols.yaml data_word.
; Evidence: Bound 4D9D-4DA6 (FC00@4DA6); callers F274 @4BBD/4D07 (gap-internal, survey-verified); nested as interior calld target of SPAN_4BA8, coexists as callee; HYPOTHESIS.
; ORIGIN 0x4D9D
	.sect ".text"
	.mmregs
	.global _start
_start:
	rptbd  0x4da4
	stm    #12160,ar2
	ldu    *ar2+,a
	mvdk   *ar2-,0x9
	stl    a,asm,*ar2+
	mar    *ar2-
	ret
