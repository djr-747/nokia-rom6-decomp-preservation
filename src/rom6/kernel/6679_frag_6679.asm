; ROM6 0x6679 FRAG_6679 -- 26w, symbols.yaml data_word.
; Evidence: Bound 6679-6692 (26w; exit B F073@6691->676A + operand 6692 — branch-tailed forward into BRANCH_TAIL_676A head; exterior-to-draft edge noted); entry bc F820@6605->6679 byte-verifie
; ORIGIN 0x6679
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0xb),#2
	bc     0x6693,ntc
	stm    #1341,ar1
	ld     #51,a
	calld  0x6976
	stm    #12247,ar2
	add    #3,b,a
	sub    *ar5,a
	bc     0x676a,agt
	stl    b,*ar5
	call   0x697f
	calld  0x6987
	stm    #1341,ar2
	b      0x676a
