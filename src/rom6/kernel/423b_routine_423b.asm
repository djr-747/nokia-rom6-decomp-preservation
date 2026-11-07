; ROM6 0x423B ROUTINE_423B -- 36w, symbols.yaml data_word.
; Evidence: Bound 423B-425E (36w; exit RET FC00@425E byte-verified, exit scan clean; 3w dark sliver 4238-423A retd@4238 split-off precedes); entries 2x call F074@32EB/6E94->423B byte-verified 
; ORIGIN 0x423B
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdm   0x51f,t
	andm   #15,*(0xe)
	mpy    #80,b
	add    b,a
	stlm   a,ar3
	stm    #139,ar4
	ld     *ar3,a
	mvmd   ar3,0x1234
	mvmd   al,0x1235
	ld     *(0x51f),a
	and    #15,a
	ld     *(0x263b),b
	and    #240,b
	or     b,a
	stl    a,*ar3
	calld  0x2c88
	stm    #162,ar5
	mvdm   0x1234,ar3
	nop
	mvkd   0x1235,*ar3
	ret
