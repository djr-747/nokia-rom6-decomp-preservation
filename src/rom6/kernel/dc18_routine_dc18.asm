; ROM6 0xDC18 ROUTINE_DC18 -- 22w, symbols.yaml data_word.
; Evidence: Bound DC18-DC2D (22w; exit RET FC00@DC2D byte-verified, exit scan clean); entries 2x calld F274@ D67D/D782->DC18 byte-verified head-exact (D67D inside ROUTINE_D667 draft — sibling 
; Pool: LMS adaptive filter + MACR rounded (both oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0xDC18
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #2884,ar3
	ld     #-879,a
	add    0x61,a
	stlm   a,ar2
	stm    #9,brc
	ld     #16384,1,b
	sub    *ar2,b
	stlm   b,t
	ld     #0,b
	rptbd  0xdc2c
	stm    #2874,ar4
	lms    *ar2,*ar3+
	macr   *ar4+,b
	sth    b,*ar5+
	ld     #0,b
	ret
