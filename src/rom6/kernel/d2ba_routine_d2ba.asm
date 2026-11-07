; ROM6 0xD2BA ROUTINE_D2BA -- 40w, symbols.yaml data_word.
; Evidence: Entry F074 070E 4A07 4A13 61F8 0A5A 0001 F920; caller D2AE calld; first-RET FC00 @D2E1; inner call 070E + calld D31D + RPTBD; HYPOTHESIS 070e-family head.
; ORIGIN 0xD2BA
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x70e
	pshm   st1
	pshm   ar3
	bitf   *(0xa5a),#1
	cc     0xdafd,ntc
	mvmm   ar2,ar3
	ld     #0,dp
	calld  0xd31d
	mar    *+ar3(0x39)
	popm   ar3
	stm    #16,ar7
	stm    #-5650,ar1
	stm    #15,brc
	rptbd  0xd2da
	ld     #0,b
	ldm    ar2,a
	add    *ar1,-8,a
	stlm   a,ar4
	ld     *ar1+,t
	ldm    ar2,a
	bitt   *ar4
	roltc  b
	stl    b,*ar3+
	banzd  0xd2d0,*ar7-
	stm    #15,brc
	popm   st1
	ret
