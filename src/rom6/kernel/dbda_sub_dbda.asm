; ROM6 0xDBDA SUB_DBDA -- 32w, symbols.yaml data_word.
; Evidence: Entry E751 F071 0027 8095; first exit ret FC00 @DBF9; callers F274 @D84B + @D24A verified; HYPOTHESIS.
; ORIGIN 0xDBDA
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar5,ar1
	rptz   a,#39
	stl    a,*ar5+
	stlm   a,ar4
	stm    #4096,ar6
	stm    #9,brc
	ld     #0,dp
	rptbd  0xdbf8
	stm    #5,t
	mvmm   ar1,ar5
	calld  0xdbfa
	stm    #1,ar7
	mpya   a
	add    0x14,a
	stl    a,0x10
	calld  0xdbfa
	stm    #0,ar7
	mar    *ar5+0
	ld     0x16,16,b
	xc     1,aleq
	neg    b
	st     b,*ar5 || ld     *ar4+,a
	ret
