; ROM6 0x54A4 MSG_FETCH_ROUTINE -- 23w, symbols.yaml program_word.
; Evidence: Called after LD *(0x3FC7/0x3FC9) on every taken producer path. Bound 54A4-54BA (RET FC00@54BA); callers 4x F074 @53CF/53E7/5430/54A0 (53CF/53E7/5430/54A0 byte-verified F074 54A4); 
; ORIGIN 0x54A4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6e6
	st     #11264,*(0x1f3)
	st     #11264,*(0x243)
	add    #11264,a
	stl    a,*(0x54a)
	stl    a,*(0x54b)
	stm    #631,brc
	ld     #0,a
	rptbd  0x54b9
	stm    #11264,ar1
	stl    a,*ar1+
	ret
