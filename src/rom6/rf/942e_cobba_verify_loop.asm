; ROM6 0x942E COBBA_VERIFY_LOOP -- 37w, symbols.yaml data_word.
; Evidence: Branch-reached (F073 @0x9449, F846 @0x944F/0x9457); PORTR pa12 74 82 00 0c @0x94BD; dual bc-bneq verdict ->0x94D0 @0x9464-74 + ldu/xor/bcd verdict @0x94A9-0x94B8; call 0x97A2 @0x94
; ORIGIN 0x942E
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5be
	stm    #250,bk
	mvdm   0x21fb,ar2
	ld     *(0x20fe),a
	bcd    0x9459,aeq
	stm    #8447,ar0
	bitf   *ar0,#1024
	bc     0x9459,tc
	bitf   *ar0,#256
	bc     0x9453,tc
	bitf   *ar0,#512
	bc     0x944b,tc
	call   0x99e6
	rc     aneq
	b      0x942e
	calld  0x9a50
	stm    #155,ar4
	bc     0x942e,agt
	b      0x9459
