; ROM6 0xDAFD SUB_DAFD -- 28w, symbols.yaml data_word.
; Evidence: Entry 4A07 F7B8 767A 000F; first exit ret FC00 @DB18 (survey DAFD->DA18 rejected, 0xDA18<entry; rptbd 0xDB16 loop, BRC 94); zero callers (caller-less boundable); HYPOTHESIS.
; ORIGIN 0xDAFD
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   st1
	ssbx   st1,sxm
	st     #15,0x7a
	stm    #-5313,ar1
	stm    #94,brc
	ldm    ar2,b
	add    *ar1,-8,b
	rptbd  0xdb16
	st     #1,0x7b
	ld     *ar1+,a
	stlm   b,ar3
	and    0x7a,a
	xor    0x7a,a
	stlm   a,t
	ldm    ar2,b
	add    *ar1,-8,b
	ld     0x7b,ts,a
	or     *ar3,a
	stl    a,*ar3
	popm   st1
	ret
