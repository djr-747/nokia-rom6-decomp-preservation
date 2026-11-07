; ROM6 0x952E FRAG_952E -- 14w, symbols.yaml data_word.
; Evidence: Bound 952E-953B (exit F073@953A->283D); entry F84C@2809 (objdump bc bneq->952E, far dispatcher entry); interior calls 05D6/97DD + portw/rpt; HYPOTHESIS.
; ORIGIN 0x952E
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5d6
	call   0x97dd
	ld     #256,a
	nop
	portw  *(0x8),1
	rpt    #20
	nop
	b      0x283d
