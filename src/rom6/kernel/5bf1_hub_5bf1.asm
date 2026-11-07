; ROM6 0x5BF1 HUB_5BF1 -- 67w, symbols.yaml data_word.
; Evidence: Entry F074 0674 F6BE EA00; bound 5BF1-5C33 (FC00@5C33); caller F074@4CD3 (objdump-verified); interior F074 0674 + 8x F274 calld 5C34 @5C00/05/0D/1C/21/29/2E (verified); HYPOTHESIS 
; ORIGIN 0x5BF1
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x674
	rsbx   st1,cpl
	ld     #0,dp
	ld     #0,a
	stlm   a,ar7
	stlm   a,ar1
	st     #64,0x60
	st     #15,0x61
	st     #3,0x16
	stm    #11036,ar0
	calld  0x5c34
	stm    #-9021,ar5
	ld     #150,a
	calld  0x5c34
	stm    #57,ar1
	ld     #1,a
	stm    #342,ar1
	mar    *ar7+
	calld  0x5c34
	stm    #-9021,ar5
	ld     #151,a
	calld  0x5c34
	stm    #399,ar1
	ld     #0,a
	mar    *ar7-
	stm    #114,ar1
	stm    #11093,ar0
	calld  0x5c34
	stm    #-9021,ar5
	ld     #150,a
	calld  0x5c34
	stm    #171,ar1
	ld     #1,a
	stm    #228,ar1
	mar    *ar7+
	calld  0x5c34
	stm    #-9021,ar5
	ld     #151,a
	calld  0x5c34
	stm    #285,ar1
	ssbx   st1,cpl
	ret
