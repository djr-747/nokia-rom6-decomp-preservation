; ROM6 0x953C FRAG_953C -- 35w, symbols.yaml data_word.
; Evidence: Bound 953C-955E (exit F073@955D->95A2); entry F84C@280D (objdump bc->953C); interior call 05D8, joins 955F/956E/9667; sub-fragment 955F-956D (bc-entry, bd-exit->9667) folded in not
; ORIGIN 0x953C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5d8
	stm    #250,bk
	ld     #0,a
	portr  53,*(0x8)
	stlm   a,ar3
	ld     #512,b
	nop
	portw  *(0xb),1
	rpt    #20
	nop
	stm    #542,ar2
	portr  54,*ar2
	bitf   *ar2,#1536
	ld     *(0x20fc),a
	sub    #6,a,b
	bc     0x955f,beq
	bc     0x956e,aneq
	bc     0x9667,tc
	b      0x95a2
