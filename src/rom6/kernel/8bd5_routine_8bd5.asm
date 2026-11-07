; ROM6 0x8BD5 ROUTINE_8BD5 -- 9w, symbols.yaml data_word.
; Evidence: Bound 8BD5-8BDD (FC00@8BDD objdump); caller F074@8643 (objdump call 0x8bd5); interior rptbd@8BD8->8BDC; HYPOTHESIS.
; ORIGIN 0x8BD5
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,a
	stm    #139,brc
	rptbd  0x8bdc
	stm    #4096,ar2
	stl    a,*ar2+
	ret
