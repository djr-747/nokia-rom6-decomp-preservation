; ROM6 0x66A7 FRAG_66A7 -- 5w, symbols.yaml data_word.
; Evidence: Bound 66A7-66AB (5w micro-arm: add-lane + exit B F073@66AA->66CB + operand 66AB, byte-verified; exit scan clean); entry bc F843@66A2->66A7 byte-verified (cond alt, chained from FRA
; ORIGIN 0x66A7
	.sect ".text"
	.mmregs
	.global _start
_start:
	add    #18,a,b
	add    *ar6,b
	b      0x66cb
