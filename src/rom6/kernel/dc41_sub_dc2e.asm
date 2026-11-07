; ROM6 0xDC41 SUB_DC2E -- 2w, symbols.yaml data_word.
; Evidence: Entry 771A 009F 7713 0008; first exit retd FE00 @DC40; Bound DC41-DC42 (RETD@DC40 delay slots — wave-11 spill fix); caller F274 @DFE6 verified; HYPOTHESIS.
; ORIGIN 0xDC41
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,*(0xc4c)
