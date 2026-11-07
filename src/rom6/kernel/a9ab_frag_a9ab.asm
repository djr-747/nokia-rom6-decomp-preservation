; ROM6 0xA9AB FRAG_A9AB -- 62w, symbols.yaml data_word.
; Evidence: Bound A9AB-A9E8 (62w; exit RET FC00@A9E8 byte-verified, exit scan clean); post-RET head (FC00@A9AA); 5 interior out-calls call@A9AB->0686 + call@A9B5->AB2C + call@A9BB->BA56 + call
; ORIGIN 0xA9AB
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x686
	bitf   *(0x263a),#512
	rc     tc
	bitf   *(0x51c),#3
	rc     tc
	call   0xab2c
	st     #12854,*(0x337c)
	ld     #159,a
	call   0xba56
	ld     *(0xb67),a
	ccd    0xab7e,aneq
	stm    #12694,ar2
	bitf   *(0x51c),#3072
	ccd    0xbac2,ntc
	stm    #12694,ar2
	st     #0,*(0xb67)
	ld     *(0x51c),a
	and    #3072,a
	sub    #2048,a
	bc     0xa9e8,aeq
	call   0x68a
	st     #12854,*(0x337c)
	bitf   *(0x2b08),#3
	bc     0xa9e8,ntc
	st     #12854,*(0x337d)
	mvkd   0x54a,*(0x337b)
	ld     #159,a
	call   0xb750
	ret
