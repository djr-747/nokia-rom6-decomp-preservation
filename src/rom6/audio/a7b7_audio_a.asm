; ROM6 0xA7B7 AUDIO_A -- 52w, symbols.yaml data_word.
; Evidence: Entry F074 0660 F074 3EE1 60F8 250F; first-RET @0xA7EA (len 52); objdump call 0x660 + call 0x3EE1; 8 callers AFF4 B0B8 B1E8 B21A B269 B303 B341 B353; HYPOTHESIS audio codec path A.
; ORIGIN 0xA7B7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x660
	call   0x3ee1
	cmpm   *(0x250f),#34
	bc     0xa7dd,ntc
	ld     *(0x542),b
	sub    #3,b
	bc     0xa7c9,bleq
	sub    #4118,a
	rc     ageq
	ld     *(0x34bf),a
	bc     0xa7d2,aneq
	st     #6,*(0x543)
	b      0xa7e8
	sub    #3,a
	bc     0xa7d8,agt
	b      0xa7e5
	st     #8,*(0x543)
	b      0xa7e8
	ld     *(0x542),-2,b
	bcd    0xa7e5,bleq
	sub    #3768,a
	rc     ageq
	st     #7,*(0x543)
	call   0x3986
	ret
