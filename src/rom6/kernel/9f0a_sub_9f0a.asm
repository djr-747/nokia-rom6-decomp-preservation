; ROM6 0x9F0A SUB_9F0A -- 15w, symbols.yaml data_word.
; Evidence: Post-RET head; interior CALLD 93CE @9F14; first exit ret FC00 @9F18; bound 9F0A-9F18; branch-entered via 9ED5 bc verified; next 9F19 stands; HYPOTHESIS.
; ORIGIN 0x9F0A
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #-32768,b
	or     *(0x914),b
	stl    b,*(0x29c8)
	ld     #40,a
	ld     #2,b
	stm    #243,ar0
	calld  0x93ce
	stm    #10696,ar2
	ret
