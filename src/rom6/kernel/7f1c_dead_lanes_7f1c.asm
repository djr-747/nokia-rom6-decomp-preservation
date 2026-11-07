; ROM6 0x7F1C DEAD_LANES_7F1C -- 57w (dead lane, annotated).
; Evidence: Post-bd head (prev 7eec span ends bd 7F75-class: whole run unreachable, no entries unconfirmed); repeated stm/calld/bd lane shapes preserved as dead code per 5886 precedent, not modeled; recombine-clean.
; ORIGIN 0x7F1C
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #0,t
	bd     0x7f75
	stm    #-20125,ar6
	stm    #-1,t
	bd     0x7f75
	stm    #-20076,ar6
	stm    #-2,t
	bd     0x7f75
	stm    #-20084,ar6
	stm    #-3,t
	bd     0x7f75
	stm    #-20092,ar6
	call   0x7fc0
	stm    #-4,t
	bd     0x7f95
	stm    #-20100,ar6
	call   0x7fc0
	stm    #-5,t
	bd     0x7f95
	stm    #-20108,ar6
	call   0x7fc0
	stm    #-6,t
	bd     0x7f95
	stm    #-20116,ar6
	call   0x7fc0
	stm    #-7,t
	bd     0x7f95
	stm    #-20124,ar6
	ret
