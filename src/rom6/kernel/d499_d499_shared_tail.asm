; ROM6 0xD499 D499_SHARED_TAIL -- 51w, symbols.yaml data_word.
; Evidence: Entered only via 0xD45A bc bneq (intra-span); interior calld 0xD39E @D49D + call 0xDB81 @D4C4; cond rc @D4CA; first exit retd FE00 @D4CB +2 delays (Bound D4CC-D4CD, executed delay 
; ORIGIN 0xD499
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   0x68,#4
	bc     0xd4ce,ntc
	calld  0xd39e
	stm    #3119,ar2
	ld     0x5d,16,a
	mvdm   0xb5a,ar2
	min    a
	stm    #12290,ar6
	mpya   *ar2(0xfc3b)
	sth    b,0x5d
	sth    b,*ar6
	stm    #3096,ar2
	ld     *ar2+,16,b
	add    *ar2+,16,b
	add    *ar2+,16,b
	add    *ar2-,16,b
	sfta   b,-2
	ld     #-2381,16,a
	max    b
	delay  *ar2-
	delay  *ar2-
	delay  *ar2
	sth    b,*ar2
	stm    #3119,ar2
	rpt    #3
	mvkd   0xc30,*ar2+
	ld     0x61,a
	mvkd   0xb5d,*ar2
	xc     1,aeq
	ld     0x5e,a
	ld     #20,dp
	call   0xdb81
	ld     #22,dp
	ldm    ar5,a
	sub    #120,a
	rc     aneq
	retd
