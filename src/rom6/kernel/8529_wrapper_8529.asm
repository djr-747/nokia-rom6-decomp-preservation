; ROM6 0x8529 WRAPPER_8529 -- 11w, symbols.yaml data_word.
; Evidence: Entry 7712 B749 7715 30DC F074 8611; first exit ret FC00 @8533; callers F074 @45D5 + F274 @45D7 adjacent pair verified; interior call to existing 8611; HYPOTHESIS.
; ORIGIN 0x8529
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-18615,ar2
	stm    #12508,ar5
	call   0x8611
	stm    #-18591,ar6
	call   0x8555
	ret
