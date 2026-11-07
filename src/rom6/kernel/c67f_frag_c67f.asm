; ROM6 0xC67F FRAG_C67F -- 51w, symbols.yaml data_word.
; Evidence: Bound C67F-C6B1 (55w; exit RET FC00@C6B1 byte-verified, exit scan clean); post-RET head only (FC00@C67E); full coverage with sibling FRAG_C6B2, no remainder; HYPOTHESIS.
; ORIGIN 0xC67F
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshd   *(0x1265)
	pshm   ar0
	stm    #14,ar0
	; long RPT: gas picks ECxx short, ROM uses F070 -- hand-forced
	.word 0xF070
	.word 14
	pshd   *ar0+
	ssbx   st1,frct
	stm    #0,bk
	ld     #0,asm
	stm    #4709,ar2
	stl    a,*ar2
	stm    #8735,ar3
	stm    #4714,ar7
	stm    #4698,ar5
	stm    #4684,ar6
	bitf   *(0x577),#512
	ccd    0x698,tc
	stm    #0,brc
	bitf   *(0x577),#4
	ld     *(0x224f),a
	ccd    0x69e,tc
	stm    #4709,ar1
	rsbx   st1,frct
	stm    #28,ar0
	; long RPT: gas picks ECxx short, ROM uses F070 -- hand-forced
	.word 0xF070
	.word 14
	popd   *ar0-
	popm   ar0
	ld     *(0x1265),a
	popd   *(0x1265)
	ret
