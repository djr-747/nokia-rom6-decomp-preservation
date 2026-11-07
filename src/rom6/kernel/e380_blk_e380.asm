; ROM6 0xE380 BLK_E380 -- 10w, symbols.yaml data_word.
; Evidence: Post-RET head; first-RET @E389 (10w); no callers listed; HYPOTHESIS.
; ORIGIN 0xE380
	.sect ".text"
	.mmregs
	.global _start
_start:
	popm   ar2
	stm    #4352,ar1
	rpt    #10
	mvkd   0xc57,*ar2+
	rptz   a,#3
	stl    a,*ar1+
	ret
