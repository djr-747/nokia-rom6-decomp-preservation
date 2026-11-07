; ROM6 0xFF69 SUB_FF69 -- 15w, symbols.yaml data_word.
; Evidence: Entry 7713 (interior call-entry of RUN_FF40); bound FF69-FF77 (exit FC00@FF77, run end); 2x F074 callers @FF44/FF4A objdump-verified; HYPOTHESIS.
; ORIGIN 0xFF69
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #14,ar3
	stm    #21845,t
	call   0xff61
	stm    #-21846,t
	call   0xff61
	stm    #18,ar3
	call   0xff61
	ret
