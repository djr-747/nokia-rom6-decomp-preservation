; ROM6 0x9C8F ROUTINE_9C8F -- 10w, symbols.yaml data_word.
; Evidence: Bound 9C8F-9C98 (10w; exit RET FC00@9C98 byte-verified, exit scan clean); entries call F074@9C89-> 9C8F byte-verified (from WRAP_9C61 span 9C61-9C8E — exterior, pre-head) + pre-wor
; ORIGIN 0x9C8F
	.sect ".text"
	.mmregs
	.global _start
_start:
	xor    a,b
	and    #255,b
	add    #-8620,b
	stlm   b,ar4
	sftl   a,-8
	nop
	xor    *ar4,a
	ret
