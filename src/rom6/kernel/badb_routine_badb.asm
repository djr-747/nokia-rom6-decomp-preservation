; ROM6 0xBADB ROUTINE_BADB -- 59w, symbols.yaml data_word.
; Evidence: Bound BADB-BB15 (59w; exit RET FC00@BB15 byte-verified, first and only unconditional exit-class; exit scan clean); entries 3x calld F274@A78D/A917/A995->BADB byte-verified (from SU
; ORIGIN 0xBADB
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6aa
	bitf   *(0x2b08),#3
	rc     ntc
	bitf   *(0x577),#2048
	rc     ntc
	pshm   st1
	ssbx   st1,ovm
	ssbx   st1,frct
	ld     #0,asm
	bitf   *(0x2aeb),#1
	bcd    0xbaf8,tc
	stm    #11012,ar3
	ld     *(0x2b03),16,b
	ld     *(0x2207),t
	mpy    *ar3,a
	max    a
	b      0xbafc
	ld     *(0x2206),t
	mpy    *ar3,a
	sfta   a,1
	sth    a,*ar3
	mvmm   ar2,ar5
	stm    #23,ar6
	ld     *ar3,13,b
	ld     *(0x2b06),16,a
	sub    a,-3,b
	sth    b,*ar6
	stm    #6,brc
	rptb   0xbb0b
	add    *ar6,16,a
	mpya   *ar2+
	sth    b,*ar5+
	mpy    *ar3,*ar2+,a
	stm    #152,brc
	rptb   0xbb11
	st     a,*ar5+ || mpy    *ar2+,a
	mvdk   *ar3,0x2b06
	popm   st1
	ret
