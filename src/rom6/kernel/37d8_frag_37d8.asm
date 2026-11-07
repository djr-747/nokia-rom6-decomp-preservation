; ROM6 0x37D8 FRAG_37D8 -- 42w, symbols.yaml data_word.
; Evidence: Bound 37D8-3801 (42w + operand; exit F073@3800->3862); caller F074@2E52 (dispatcher clause; branch- vs-call weak per critic); interior calls 05A0/942E; exits to 2E64/676A/3862 chai
; ORIGIN 0x37D8
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5a0
	bitf   *(0x860),#144
	cc     0x9e85,ntc
	call   0x942e
	stm    #1,ar0
	mvmm   ar3,ar6
	stlm   a,ar4
	rc     aeq
	ldm    ar3,a
	and    #255,a
	sub    #0,a,b
	bc     0x3862,bneq
	ldm    ar4,a
	and    #255,a
	sub    #240,a,b
	bc     0x3802,beq
	sub    #242,a,b
	bc     0x3806,beq
	sub    #244,a,b
	bc     0x381b,beq
	sub    #247,a,b
	bc     0x3879,beq
	b      0x3862
