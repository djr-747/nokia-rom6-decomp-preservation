; ROM6 0x43BA ROUTINE_43BA -- 19w, symbols.yaml data_word.
; Evidence: Bound 43BA-43CC (19w; exit BACC F4E2@43CC computed-target, byte-verified — computed exit, no fall-through); entries call F074@2EC2->43BA byte-verified + post-RET head (FC00@43B9); 
; Pool: BACC computed jump exit (oracle-unbound dispatch) + circular MVKD; stays .asm, bytes verified.
; ORIGIN 0x43BA
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	ld     *ar2,-8,a
	and    #255,a
	mvdk   *ar2+%,0x2f00
	sub    #29,a,b
	bc     0x43cd,bgt
	add    #-20258,a
	stlm   a,ar1
	nop
	nop
	ld     *ar1,a
	bacc   a
