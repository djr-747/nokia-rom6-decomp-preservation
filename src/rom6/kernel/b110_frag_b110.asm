; ROM6 0xB110 FRAG_B110 -- 12w, symbols.yaml data_word.
; Evidence: Bound B110-B11B (12w, exit FC00@B11B); post-RET head (after FC00@B10F of STUB_B0F5); interior rc FE45@B115 (rcd aeq) + rc FC4C@B118 (rc bneq), both objdump-verified conditional ret
; ORIGIN 0xB110
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    *ar4,b
	and    #3,b
	add    a,b
	stlm   b,ar2
	rcd    aeq
	sub    #5,b
	rc     bneq
	stm    #1,ar2
	ret
