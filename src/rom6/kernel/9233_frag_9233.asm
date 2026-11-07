; ROM6 0x9233 FRAG_9233 -- 25w, symbols.yaml data_word.
; Evidence: Bound 9233-924B (25w; exit RET FC00@924B byte-verified); caller F074@0x92F6 (mid-lane backward call from SUB_92F4 span — interior-to-next-span caller, FRAG per B41C precedent); 921
; ORIGIN 0x9233
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmd   ar3,0x60
	stm    #32,ar0
	stm    #12128,ar3
	stm    #12032,ar5
	stm    #12096,ar4
	stm    #128,bk
	ld     #-16383,a
	rpt    #63
	stl    a,*ar5+
	stm    #12032,ar5
	ld     #0,a
	stl    a,*ar5
	stm    #12365,ar7
	stm    #12160,ar6
	ret
