; ROM6 0x2875 FRAG_2875 -- 48w, symbols.yaml data_word.
; Evidence: Bound 2875-28A4 (48w, exit F073@28A3->283D + operand 28A4); entry bc F84C@2800 (inside STRETCH_2800, taken-path); TRIMMED from 2875-2969 team draft: two outside early-outs found by
; ORIGIN 0x2875
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5f6
	st     #28,*ar2
	nop
	portw  *ar2,1
	rpt    #14
	nop
	and    #16,a,b
	bc     0x2890,beq
	orm    #64,*(0x552)
	portr  2,*(0x8)
	or     #16,a
	nop
	portw  *(0x8),2
	b      0x2899
	and    #8,a,b
	bc     0x283d,beq
	bitf   *(0x2639),#512
	bc     0x28a5,tc
	st     #15000,*ar2
	nop
	portw  *ar2,15
	rpt    #14
	nop
	orm    #2,*(0x263a)
	b      0x283d
