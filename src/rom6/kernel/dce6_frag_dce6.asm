; ROM6 0xDCE6 FRAG_DCE6 -- 84w, symbols.yaml data_word.
; Evidence: Bound DCE6-DD39 (88w; exit retd FE00@DD37 + delays DD38-DD39 absorbed (1AF8 0C4E); exit scan clean); post-RET head only (FE00@DCE5, zero ext refs); interior out-calls calld@DCF1->D
; ORIGIN 0xDCE6
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     0x69,16,a
	or     0x62,a
	bitf   *(0xa5a),#8
	ld     *(0xecc),a
	bc     0xdcf9,ntc
	bc     0xdcf9,aneq
	calld  0xdbc3
	stm    #2738,ar2
	sfta   b,15
	sfta   b,5
	sth    b,*(0xc4d)
	ld     *(0xc4e),16,a
	sth    a,0x62
	bitf   *(0xa5a),#16
	bc     0xdd2a,ntc
	calld  0xdbd4
	stm    #2738,ar2
	sth    b,0x67
	stm    #-1098,ar2
	ld     *(0xc4d),t
	stm    #103,ar3
	stm    #101,ar4
	stm    #104,ar5
	mpy    *ar2+,a
	st     a,*ar5 || ld     *ar3,a
	sub    *ar5+,16,a
	abs    a
	sth    a,*ar4
	st     #31,*ar5-
	stm    #30,brc
	mpy    *ar2+,a
	st     a,*ar5 || ld     *ar3,a
	sub    *ar5+,16,a
	rptbd  0xdd26
	abs    a
	sub    *ar4,16,a,b
	srccd  *ar5-,blt
	saccd  a,*ar4,blt
	mpy    *ar2+,a
	st     a,*ar5 || ld     *ar3,a
	sub    *ar5+,16,a
	abs    a
	sub    *ar4,16,a,b
	ld     #31,a
	sub    *ar5,a
	stl    a,*ar5
	ld     #20,dp
	calld  0xdb76
	ld     *(0xc4e),a
	ld     #0,dp
	stm    #3230,ar1
	ld     #-2381,a
	rpt    #3
	stl    a,*ar1+
	ld     0x69,16,a
	retd
	or     *(0xc4e),a
