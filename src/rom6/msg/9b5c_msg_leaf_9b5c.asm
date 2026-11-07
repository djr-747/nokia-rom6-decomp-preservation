; ROM6 0x9B5C MSG_LEAF_9B5C -- 7w, symbols.yaml data_word.
; Evidence: Entry 6D95 6C83 9B63 6D93 FE00 6F81; bound 9B5C-9B62 (exit FE00 retd@9B60 + slots 9B61-9B62); 5x F074 callers @9B34/9B39/9B4C/9B51/9B54 (all objdump-verified call 0x9b5c); interior
; ORIGIN 0x9B5C
	.sect ".text"
	.mmregs
	.global _start
_start:
	mar    *ar5+
	banz   0x9b63,*ar3
	mar    *ar3+
	retd
	stl    a,8,*ar1
