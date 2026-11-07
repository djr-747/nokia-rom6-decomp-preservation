; ROM6 0xA6AE SUB_A6AE -- 52w, symbols.yaml data_word.
; Evidence: Entry F074 065E; bound A6AE-A6E1 ret; interior BA56 @A6BF + B750 @A6CF + 9FCF @A6D1 + C5F9 @A6D6 + A109 @A6DF + ccd @A6DB (FB20 to BAC2 per correction, not counted) + rc @A6B3; zer
; ORIGIN 0xA6AE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65e
	cmpm   *(0x2510),#193
	rc     ntc
	ld     *(0x51c),a
	and    #3072,a
	sub    #2048,a
	rc     aeq
	st     #12950,*(0x337c)
	ld     #63,a
	call   0xba56
	bitf   *(0x2b08),#3
	bc     0xa6e1,ntc
	bitf   *(0x2aff),#-32768
	bc     0xa6d1,ntc
	andm   #32767,*(0x2aff)
	ld     #63,a
	call   0xb750
	call   0x9fcf
	st     #12854,*(0x337c)
	call   0xc5f9
	bitf   *(0x577),#4096
	ccd    0xbcfc,tc
	stm    #12854,ar1
	call   0xa109
	ret
