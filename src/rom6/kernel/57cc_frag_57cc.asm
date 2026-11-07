; ROM6 0x57CC FRAG_57CC -- 50w, symbols.yaml data_word.
; Evidence: Bound 57CC-57FD (50w; exit RET FC00@57FD byte-verified, exit scan clean); entries bc F820@57AC-> 57D3 + F820@57BC->57EE + F845@57C1->57CC + F845@57C5->57F2 + BD F273@57C8->57F4 (al
; ORIGIN 0x57CC
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #1,*(0x2eff)
	bd     0x57f4
	or     #4,b
	ld     *(0x2628),b
	cmpm   *(0x250f),#47
	bc     0x57de,tc
	cmpm   *(0x250f),#34
	rc     ntc
	ld     *(0x918),a
	sub    #52,a
	bc     0x57ee,aeq
	rc     alt
	sub    #7,a
	bc     0x57f2,aeq
	rc     agt
	bd     0x57f4
	or     #4,b
	bd     0x57f4
	or     #12,b
	or     #20,b
	cmpm   *(0x2510),#177
	rcd    ntc
	stl    b,*(0x2628)
	andm   #-25,*(0x2628)
	ret
