; ROM6 0x6FDA CMPSTASH_6FDA -- 32w, symbols.yaml data_word.
; Evidence: Entry F074 05B4; bound 6FDA-6FF9 (FC00; interior FC20@6FE3 + FC4B@6FF8 conditional only); callers F074 6F5D/6F6E; call 712D@6FE1; HYPOTHESIS.
; ORIGIN 0x6FDA
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b4
	cmpm   *(0x250f),#34
	bc     0x6fe4,ntc
	call   0x712d
	rc     ntc
	ld     #0,a
	mvdm   0x245e,ar4
	stm    #9310,ar2
	mvdd   *ar4+,*ar3
	mvdm   0x265c,al
	add    #9633,a
	sub    *(0x14),a
	bcd    0x6ff6,agt
	ldm    ar4,a
	nop
	ld     #9633,a
	stl    a,*ar2
	sub    *ar3,b
	rc     blt
	ret
