; ROM6 0xA482 MSG_SETUP_A -- 56w, symbols.yaml data_word.
; Evidence: Entry F074 0656 10F8 262C FC45 11F8; first-RET FC00 @0xA4B9 (len 56); 7 callers A27D A281 B059 B0CB B163 B2D4 B34D; body calls 0x656/0x3986/calld-AB82; role HYPOTHESIS.
; ORIGIN 0xA482
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x656
	ld     *(0x262c),a
	rc     aeq
	ld     *(0x2615),b
	cmpm   *(0x250f),#34
	bc     0xa492,ntc
	sub    #3650,b,a
	b      0xa494
	sub    #3400,b,a
	bc     0xa4b2,alt
	pshm   bl
	portr  16,*(0x8)
	sub    *(0x265a),a
	bc     0xa4b0,aneq
	st     #3,*(0x543)
	cmpm   *(0x250f),#34
	bc     0xa4ae,ntc
	cmpm   *(0x34bf),#0
	bc     0xa4ae,ntc
	st     #2,*(0x543)
	call   0x3986
	ld     #0,b
	popm   bl
	ld     *(0x262c),a
	calld  0xab82
	stm    #10,ar2
	ld     #1,a
	ret
