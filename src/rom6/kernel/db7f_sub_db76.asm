; ROM6 0xDB7F SUB_DB76 -- 2w, symbols.yaml data_word.
; Evidence: Entry 7210 0A5B 605B 001B; first exit retd FE00 @DB7E; Bound DB7F-DB80 (RETD@DB7E delay slots — wave-11 spill fix); callers F074 @DCE2 + F274 @DD2B verified; HYPOTHESIS.
; ORIGIN 0xDB7F
	.sect ".text"
	.mmregs
	.global _start
_start:
	xc     1,tc
	sth    a,0x5b
