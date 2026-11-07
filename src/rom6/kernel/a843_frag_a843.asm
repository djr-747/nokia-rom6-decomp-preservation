; ROM6 0xA843 FRAG_A843 -- 60w, symbols.yaml data_word.
; Evidence: Bound A843-A87E (60w; exit RET FC00@A87E byte-verified, exit scan clean); post-RET head only (FC00@A842 = ROUTINE_A815 exit, zero ext calls/branches — multi-call body, FRAG by entr
; ORIGIN 0xA843
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x67c
	ld     #2,a
	sub    *(0x2efe),a
	bc     0xa84c,aneq
	stl    a,*(0x2efe)
	cmpm   *(0x2510),#192
	rc     ntc
	bitf   *(0x51c),#3
	rc     tc
	bitf   *(0x51f),#6144
	rc     tc
	bitf   *(0x51c),#64
	cc     0xab2c,ntc
	stm    #12694,ar1
	rpt    #159
	mvkd   0x32e5,*ar1+
	ld     *(0x2efe),a
	ccd    0xab7e,aneq
	stm    #12694,ar2
	ld     *(0x2efe),a
	cc     0x9e2f,aeq
	call   0xa8fe
	st     #12854,*(0x337c)
	st     #12854,*(0x337d)
	ld     #159,a
	call   0xba56
	calld  0xbac2
	stm    #12694,ar2
	st     #0,*(0x2efe)
	ret
