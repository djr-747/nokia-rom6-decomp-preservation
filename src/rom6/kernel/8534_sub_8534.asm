; ROM6 0x8534 SUB_8534 -- 7w, symbols.yaml data_word.
; Evidence: Entry 7715 B743 7716 B76D F074 853B; caller F274 calld @4616 verified; interior call 853B @8538 (target existing 853B); first exit ret @853A; bound 8534-853A; HYPOTHESIS.
; ORIGIN 0x8534
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-18621,ar5
	stm    #-18579,ar6
	call   0x853b
	ret
