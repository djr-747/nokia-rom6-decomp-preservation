; ROM6 0x2983 FRAG_2983 -- 46w, symbols.yaml data_word.
; Evidence: Bound 2983-29B0 (14w; exit F073@29AF->2A8A + operand 29B0 — TRIMMED at first outside exit per mesh rule; 8 more outside-targeting F073s follow in dark zone); entry bc F830@2977->29
; ORIGIN 0x2983
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b8
	bitf   *ar2,#64
	bc     0x2979,ntc
	bitf   *(0x3ec8),#2
	bc     0x2acc,tc
	bitf   *(0x3ec8),#32
	bc     0x2a73,ntc
	mvdm   0x265e,ar2
	mvdm   0x2660,ar3
	cmpm   *(0x13d0),#0
	bc     0x2a8a,tc
	stm    #5072,ar3
	bitf   *ar3,#1
	bc     0x29b9,ntc
	call   0x3ee1
	ld     *ar2(0x1),b
	sub    b,a
	bc     0x29b1,agt
	sub    *(0x126f),b
	bc     0x29b1,bgt
	mvdm   0x2660,ar3
	b      0x2a8a
