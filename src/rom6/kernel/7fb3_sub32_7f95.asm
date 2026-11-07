; ROM6 0x7FB3 SUB32_7F95 -- 2w, symbols.yaml data_word.
; Evidence: Post-unconditional-b head (F073 b @7F93, backscan 7F7D-7F94 exit-free); entry F074 059E 7715 0006; bound shrunk to interior F073 b @7FB3->7F54 incl operand 7FB4 len 32, tail-merges. Word count corrected wave-12 (b is 2 words; operand 0x7FB4 homed here, 7fb4 span trimmed).
; ORIGIN 0x7FB3
	.sect ".text"
	.mmregs
	.global _start
_start:
	b      0x7f54
