; ROM6 0x2BAA FRAG_2BAA -- 67w, symbols.yaml data_word.
; Evidence: Bounds 2BAA-2BEC + 2BED-2C02 (exit F073@2BEB->283D + operand 2BEC; second segment entered via interior forward join F073@2BE2->2BED, exit F073@2C01->283D + operand 2C02); entry bc 
; ORIGIN 0x2BAA
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #2048,*ar2
	nop
	portw  *ar2,1
	rpt    #22
	nop
	portr  56,*(0x8)
	and    #8,a
	bc     0x283d,aeq
	stm    #13456,ar4
	ld     *ar4,a
	and    #112,a
	stm    #1235,ar2
	stm    #14978,ar3
	bc     0x2bcd,aeq
	sub    #1,4,a
	stm    #13459,ar2
	stm    #14982,ar3
	bc     0x2bcd,aeq
	stm    #13474,ar2
	call   0x39f0
	ld     *(0x34bf),a
	bc     0x2bed,aeq
	ld     *(0x3490),a
	and    #112,a,b
	bc     0x2be4,beq
	cmpm   *(0x34bf),#4
	bc     0x2bed,ntc
	sub    #1,4,b
	bc     0x2be4,beq
	b      0x2bed
	addm   #16,*(0x3490)
	stm    #2324,ar2
	call   0x39a4
	b      0x283d
