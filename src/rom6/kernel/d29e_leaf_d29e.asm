; ROM6 0xD29E LEAF_D29E -- 28w, symbols.yaml data_word.
; Evidence: Entry 4A07 7707 0740 F074 0682 EA14 105A F030; caller A946; first-RET FC00 @D2B9 (27w); inner call 0682 + calld D2BA; HYPOTHESIS trampoline leaf.
; ORIGIN 0xD29E
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   st1
	stm    #1856,st1
	call   0x682
	ld     #20,dp
	ld     0x5a,a
	and    #1,a
	ccd    0xdad2,aeq
	stm    #3798,ar2
	ld     #0,dp
	stm    #3798,ar2
	calld  0xd2ba
	stm    #9593,ar3
	ld     *(0xc4c),a
	and    #2,a
	cc     0xdc43,aneq
	popm   st1
	ret
