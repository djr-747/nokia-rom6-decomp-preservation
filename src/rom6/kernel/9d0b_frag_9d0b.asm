; ROM6 0x9D0B FRAG_9D0B -- 11w, symbols.yaml data_word.
; Evidence: Bound 9D0B-9D15 (exit RET FC00@9D15); entry bc@9CEC->9D0B (interior branch of FRAG_9CE7 span; nesting noted); HYPOTHESIS.
; ORIGIN 0x9D0B
	.sect ".text"
	.mmregs
	.global _start
_start:
	add    #2,b
	sftl   b,1
	ld     #40,a
	stm    #243,ar0
	calld  0x93ce
	stm    #10696,ar2
	ret
