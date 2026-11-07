; ROM6 0x68F7 SUB_68F7 -- 23w, symbols.yaml data_word.
; Evidence: Bound 68F7-690D (exit FE00@690B + slots 690C/690D); caller F074@64F4 (objdump-verified call 0x68f7; 64F4 is branch-entered frag, forward call); BC@6901/6909 fall through; preceded 
; ORIGIN 0x68F7
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #907,ar1
	ld     *ar1,a
	stm    #9767,ar2
	st     #0,*(0x545)
	sub    #16,a,b
	bc     0x690e,bgt
	sub    #1,a
	stlm   a,t
	nop
	bitt   *+ar1(0x2)
	bc     0x6928,tc
	retd
	orm    #256,*ar2
