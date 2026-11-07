; ROM6 0x7EEC SUB_7EEC -- 48w, symbols.yaml program_word.
; Evidence: Bound 7EEC-7F1B (48w); entry TRACE (same histogram: 7EEC-7F1A heads x9); stm/calld/bd lane run with interior bd->7F95 dispatch exits (delay slots fall into next lane); ends after b
; ORIGIN 0x7EEC
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #0,t
	calld  0x7f55
	stm    #-20125,ar6
	stm    #-4,t
	bd     0x7f95
	stm    #-20100,ar6
	stm    #-1,t
	calld  0x7f55
	stm    #-20076,ar6
	stm    #-5,t
	bd     0x7f95
	stm    #-20108,ar6
	stm    #-2,t
	calld  0x7f55
	stm    #-20084,ar6
	stm    #-6,t
	bd     0x7f95
	stm    #-20116,ar6
	stm    #-3,t
	calld  0x7f55
	stm    #-20092,ar6
	stm    #-7,t
	bd     0x7f95
	stm    #-20124,ar6
