; ROM6 0x7EC6 DELAY_ABUT_7EC6 -- 38w, symbols.yaml program_word.
; Evidence: Post-bd head (prev 7ebe span bd 7F95: first 2w (one stm) run once as its delay slot, then the bd takes effect -- cross-span delay abut per D581/oracle two-word slots); remainder 7EC8-7EEB dead (no entries, unconfirmed); tail calld/bd lane shapes preserved but unreachable.
; ORIGIN 0x7EC6
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-20100,ar6
	stm    #-1,t
	calld  0x7f55
	stm    #-20076,ar6
	stm    #-13,t
	bd     0x7f95
	stm    #-20108,ar6
	stm    #-2,t
	calld  0x7f55
	stm    #-20084,ar6
	stm    #-14,t
	bd     0x7f95
	stm    #-20116,ar6
	stm    #-3,t
	calld  0x7f55
	stm    #-20092,ar6
	stm    #-15,t
	bd     0x7f95
	stm    #-20124,ar6
