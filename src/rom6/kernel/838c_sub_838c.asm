; ROM6 0x838C SUB_838C -- 20w, symbols.yaml data_word.
; Evidence: Entry 7716 B184 F274 7F55 770E FFFD; zero callers; first exit ret @839F (abuts 83A0); bound 838C-839F; HYPOTHESIS.
; ORIGIN 0x838C
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-20092,ar6
	calld  0x7f55
	stm    #-3,t
	stm    #-20124,ar6
	calld  0x7f95
	stm    #-7,t
	calld  0x7fc6
	stm    #10884,ar2
	orm    #1536,*(0x2a87)
	ret
