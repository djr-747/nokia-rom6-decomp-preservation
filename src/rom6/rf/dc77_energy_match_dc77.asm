; ROM6 0xDC77 ENERGY_MATCH_DC77 -- 111w, symbols.yaml data_word.
; Evidence: Entry 8062 7663 8000 61F8 0A5A 0001 FA20; callers F074 @D1D6/@D24E verified; first exit retd FE00 @DCE5 +delays abutting DCE8; interior bcd cond + calld E56D/E583 + call DB76; HYPO
; ORIGIN 0xDC77
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,0x62
	st     #-32768,0x63
	bitf   *(0xa5a),#1
	bcd    0xdce8,ntc
	stm    #3354,ar3
	squr   *ar3+,a
	rpt    #38
	squra  *ar3+,a
	stm    #26214,t
	calld  0xe56d
	adds   0x63,a
	mpya   a
	sub    #30,16,a
	sth    a,0x64
	sub    0x64,16,a
	sfta   a,1
	add    0x64,16,a
	stm    #3230,ar2
	stm    #-335,ar3
	ld     #11,16,b
	or     #-2691,b
	rpt    #3
	mac    *ar2+,*ar3+,b
	sub    a,b
	ld     b,-1,a
	sth    a,0x64
	sub    0x64,16,a
	calld  0xe583
	sfta   a,-1
	add    0x64,16,a
	sfta   a,15
	sfta   a,5
	sth    a,0x66
	ld     0x66,t
	stm    #-1098,ar2
	stm    #98,ar3
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
	rptbd  0xdcc4
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
	add    #-1098,a
	stlm   a,ar2
	stm    #102,ar3
	stm    #3232,ar4
	stm    #3233,ar5
	rpt    #2
	mvdd   *ar4-,*ar5-
	mpy    *ar2,*ar3,a
	calld  0xe56d
	sth    a,0x62
	ld     *ar2,a
	sth    a,0x64
	sub    0x64,16,a
	ld     a,-5,a
	ld     0x64,16,b
	sub    #11,16,b
	add    b,-6,a
	stl    a,*ar5
	ld     0x62,a
	ld     #20,dp
	call   0xdb76
	ld     #0,dp
	retd
