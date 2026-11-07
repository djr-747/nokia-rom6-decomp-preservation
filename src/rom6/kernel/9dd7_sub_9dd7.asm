; ROM6 0x9DD7 SUB_9DD7 -- 6w, symbols.yaml data_word.
; Evidence: Post-RET head rc-beq + CALLs 06C8/9ED0; first exit ret FC00 @9DDC; bound 9DD7-9DDC; branch-entered via 9DC1 bc verified; HYPOTHESIS.
; ORIGIN 0x9DD7
	.sect ".text"
	.mmregs
	.global _start
_start:
	rc     beq
	call   0x6c8
	call   0x9ed0
	ret
