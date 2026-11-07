; ROM6 0x6753 FRAG_6753 -- 23w, symbols.yaml data_word.
; Evidence: Bound 6753-6769 (23w; NO own exit: exit scan clean of RET/FE00/BD/BACC/F073, falls into SEG_676A head — tail-frag abut, not a routine); entry bc F820@6742->6753 byte-verified (cond
; ORIGIN 0x6753
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x8),#2
	bc     0x676a,ntc
	stm    #1341,ar1
	ld     #51,a
	calld  0x6976
	stm    #12247,ar2
	sub    *(0x2fdd),b,a
	bc     0x676a,ageq
	call   0x697f
	calld  0x6987
	stm    #1341,ar2
