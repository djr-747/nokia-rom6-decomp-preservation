; ROM6 0x9B67 ROUTINE_9B67 -- 8w, symbols.yaml data_word.
; Evidence: Bound 9B67-9B6E (exit retd FE00@9B6C + slots 9B6D-9B6E objdump); caller F074@9B3D; interior banz@9B67->9B6F (sub-leaf 9B6F-9B74 own retd@9B73 noted); HYPOTHESIS.
; ORIGIN 0x9B67
	.sect ".text"
	.mmregs
	.global _start
_start:
	banz   0x9b6f,*ar4
	ld     *ar2,-8,b
	mar    *ar4+
	retd
	and    #255,b
