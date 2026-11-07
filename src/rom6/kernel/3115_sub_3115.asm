; ROM6 0x3115 SUB_3115 -- 10w, symbols.yaml program_word.
; Evidence: Bound 3115-311E (10w); entry TRACE (same histogram: 3115-311E heads x1); ld/stm/andm/xc/orm leaf; ret FC00@311E; abuts claimed 311F; HYPOTHESIS.
; ORIGIN 0x3115
	.sect ".text"
	.global _start
_start:
	ld     *(0x11),a
	stm    #1310,ar3
	andm   #-4097,*ar3
	xc     2,agt
	orm    #4096,*ar3
	ret
