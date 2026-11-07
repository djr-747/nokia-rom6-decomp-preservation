; ROM6 0x6961 SUB_6961 -- 18w, symbols.yaml data_word.
; Evidence: Bound 6961-6972 (exit FC00@6972); 6x callers: F074@6545 + F274 @65B6/671A/6722/672C/6736 (all objdump-verified call/calld 0x6961); contains out-call F074@6962->6973 (forward call i
; ORIGIN 0x6961
	.sect ".text"
	.mmregs
	.global _start
_start:
	stlm   b,t
	call   0x6973
	ld     *ar0,16,a
	mpya   a
	add    b,a
	stlm   a,ar3
	sub    *(0xe),b,a
	add    #6,a
	nop
	nop
	xc     1,agt
	ld     #0,b
	ldm    ar3,a
	ret
