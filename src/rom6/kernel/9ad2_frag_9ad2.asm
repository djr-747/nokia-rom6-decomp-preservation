; ROM6 0x9AD2 FRAG_9AD2 -- 34w, symbols.yaml data_word.
; Evidence: Bound 9AD2-9AF3 (FC00@9AF3); entries F073@9ABD/@9ACB; interior calld 2C88@9AD4, bcd@9AD9->9AF4, joins 9AE9/9AF4; sliver 9AF4-9AFB (bcd-entry, retd@9AF9+slots, objdump-verified) + o
; ORIGIN 0x9AD2
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmd   ar2,0x21fb
	calld  0x2c88
	stm    #12032,ar3
	popm   al
	bcd    0x9af4,bneq
	popm   bl
	popm   ar2
	ssbx   st1,intm
	andm   #32767,*(0x20ff)
	bitf   *(0x8),#1
	bc     0x9ae9,ntc
	orm    #-32768,*(0x20ff)
	ld     *(0x20fe),a
	add    a,b
	stl    b,*(0x20fe)
	mvmd   ar2,0x21fb
	ld     #-1,a
	rsbx   st1,intm
	ret
