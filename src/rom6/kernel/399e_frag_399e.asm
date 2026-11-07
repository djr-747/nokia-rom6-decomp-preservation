; ROM6 0x399E FRAG_399E -- 6w, symbols.yaml data_word.
; Evidence: Bound 399E-39A3 (6w; exit RET FC00@39A3 byte-verified, first and only unconditional exit-class; exit scan clean); entry = fall-through abut from CMD_DISPATCH_PORT15 [3986-399D] tai
; ORIGIN 0x399E
	.sect ".text"
	.mmregs
	.global _start
_start:
	.word 0x3997 ; leading bare word
	; @399F f6bb rsbx   st1,intm
	rsbx   st1,intm
	; @39A0 68f8 andm   #-3,*(0x263a)
	andm   #-3,*(0x263a)
	; @39A3 fc00 ret
	ret
