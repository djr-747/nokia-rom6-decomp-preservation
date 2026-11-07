; ROM6 0xACBB FRAG_ACBB -- 56w, symbols.yaml data_word.
; Evidence: Bound ACBB-ACF2 (56w; exit B F073@ACF1->AE22 + operand ACF2 — branch-tailed outside gap into AE70 filler zone; exit scan otherwise clean); post-RET head only (FC00@ACBA, zero ext e
; ORIGIN 0xACBB
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-20813,ar5
	stm    #9718,ar2
	bitf   *(0x3ec8),#2
	ld     #259,b
	nop
	xc     1,tc
	ld     #192,b
	stm    #4,brc
	rptb   0xacd6
	ldm    ar5,a
	mar    *ar5+
	stl    b,*ar2+
	reada  *ar2+
	bitf   *(0x3ec8),#2
	ld     #256,b
	nop
	xc     1,tc
	ld     #180,b
	stl    b,*ar2+
	st     #15000,*ar2+
	stm    #9730,ar2
	rpt    #9
	mvkd   0x3e81,*ar2+
	bitf   *(0x3ec8),#2
	bc     0xacf3,ntc
	stm    #16003,ar5
	mvdd   *ar5+,*ar2+
	mvdd   *ar5+,*ar2+
	portr  12,*(0x8)
	or     #16,a
	nop
	portw  *(0x8),12
	b      0xae22
