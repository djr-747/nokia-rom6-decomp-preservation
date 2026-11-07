; ROM6 0xC48C CALLD_GATE_C48C -- 92w, symbols.yaml data_word.
; Evidence: Entry F074 06DC; bound C48C-C4E7; caller C080; CALLD BF8C@C49A + LD #2242/#1536 + MPY #-4107 + RPTZ MAC + DST + RCD exits; HYPOTHESIS.
; ORIGIN 0xC48C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6dc
	xor    a
	stl    a,0x4d
	stm    #10409,ar2
	stm    #10408,ar5
	sub    *ar2,*ar5,a
	bcd    0xc4a8,ageq
	st     #32767,0x47
	ld     *ar5,a
	calld  0xbf8c
	stm    #12626,ar1
	ssbx   st1,sxm
	ld     *ar1+,t
	ld     #17,b
	add    *ar1,b
	ld     *(0xb),asm
	mpy    *ar2,a
	ld     a,asm,b
	sat    b
	sth    b,0x47
	ld     #2242,16,a
	sub    0x47,16,a
	bcd    0xc4b9,alt
	ld     #1536,16,a
	mpy    0x47,#-4107,a
	adds   0x42,a
	sat    a
	and    #-1,16,a
	add    #1817,16,a
	and    #-1,16,a
	stm    #12570,ar3
	stm    #2729,t
	rptz   b,#11
	mac    *ar3+,b
	adds   0x42,b
	sat    b
	sth    b,0x52
	sub    0x52,16,a
	ld     *(0x28a5),b
	sfta   b,1
	xc     1,alt
	or     0x41,b
	stl    b,*(0x28a5)
	ld     *(0x28aa),t
	ld     *ar2,ts,b
	ld     *(0xb),t
	mpyr   0x52,b
	sub    #95,16,b
	dld    *(0x3100),a
	xc     2,bgt
	st     #1,0x4d
	ld     #122,16,b
	or     #4608,b
	sub    b,a
	ld     *(0x28a5),b
	and    #3,b
	rcd    alt
	st     #0,0x45
	xc     2,bneq
	st     #1,0x45
	ret
