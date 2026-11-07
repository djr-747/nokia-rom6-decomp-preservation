; ROM6 0x9CE7 FRAG_9CE7 -- 36w, symbols.yaml data_word.
; Evidence: Bound 9CE7-9D0A (exit F073@9D09->9D15 objdump); entries F073@9CCD + F820@9CD2 (both interior branches of existing CHAIN_HEAD_9C99: nesting noted, no address overlap); interior call
; ORIGIN 0x9CE7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6c8
	bitf   *(0x85d),#32
	bc     0x9d0b,ntc
	stm    #10697,ar2
	stm    #2342,ar3
	rpt    *(0xb)
	mvdd   *ar2+,*ar3+
	bitf   *(0x861),#1
	stm    #2159,ar2
	st     #1,*ar2
	xc     2,tc
	orm    #2,*(0x861)
	orm    #1,*(0x861)
	orm    #8,*(0x29)
	andm   #-9,*(0x29)
	b      0x9d15
