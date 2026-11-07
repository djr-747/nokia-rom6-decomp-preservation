; ROM6 0xDB76 SUB_DB76 -- 9w, symbols.yaml data_word.
; Evidence: Entry 7210 0A5B 605B 001B; first exit retd FE00 @DB7E; Bound DB7F-DB80 (RETD@DB7E delay slots — wave-11 spill fix); callers F074 @DCE2 + F274 @DD2B verified; HYPOTHESIS.
; ORIGIN 0xDB76
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdm   0xa5b,ar0
	cmpm   0x5b,#27
	stl    a,*ar0(0xab2)
	addm   #1,0x5b
	retd
