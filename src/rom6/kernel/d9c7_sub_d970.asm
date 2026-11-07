; ROM6 0xD9C7 SUB_D970 -- 2w, symbols.yaml data_word.
; Evidence: Entry 4A07 7707 0740 EA16; first exit retd FE00 @D9C6 entry-linear; Bound D9C7-D9C8 (RETD@D9C6 delay slots — wave-11 spill fix); callers F074 @5477 + @5490 verified; HYPOTHESIS.
; ORIGIN 0xD9C7
	.sect ".text"
	.mmregs
	.global _start
_start:
	rpt    #39
	sth    a,*ar3+
