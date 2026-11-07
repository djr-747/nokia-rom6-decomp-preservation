; ROM6 0xE5D1 ROUTINE_E5D1 -- 85w, symbols.yaml data_word.
; Evidence: Bound E5D1-E625 (85w; exit RET FC00@E625 byte-verified); entry F274 calld @CF6A word-verified (F074 0680 head, pre FFFF = E5CE retd delay tail); bytes F074 0680 4A0B E801; far call
; ORIGIN 0xE5D1
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x680
	pshm   bl
	ld     #1,a
	stm    #9034,ar1
	stm    #9056,ar0
	stm    #9057,ar5
	stm    #9059,ar6
	fcalld 0x1a50d
	stm    #9058,ar7
	popm   t
	stm    #9034,ar1
	stm    #9060,ar3
	fcalld 0x1a54e
	stm    #9069,ar2
	stm    #9069,ar3
	stm    #9078,ar2
	fcalld 0x1a4f6
	stm    #9087,ar5
	stm    #3670,ar1
	stm    #9079,ar3
	ld     *(0x237f),b
	fcalld 0x1a59c
	stm    #9060,ar2
	stm    #9052,ar6
	pshm   bl
	fcalld 0x1a5f0
	stm    #9088,ar1
	stm    #3,t
	stm    #9088,ar1
	stm    #2635,ar6
	stm    #9078,ar2
	stm    #9087,ar3
	stm    #9056,ar0
	stm    #9094,ar5
	ld     #0,b
	popm   bl
	rpt    #5
	mvkd   0xb630,*ar5-
	mar    *ar5+
	fcalld 0x1a622
	stm    #9058,ar7
	ld     *(0x2360),a
	fcalld 0x1a6e2
	ld     *(0x2361),b
	ld     #10,a
	stlm   a,t
	fcall  0x1a704
	ret
