; ROM6 0xDBC1 EXP_NORM_DB8C -- 2w, symbols.yaml data_word.
; Evidence: Entry E721 770E 0010 771A 0027 F4B9; caller F274 @D23F verified; first exit retd FE00 @DBC0 +delays (Bound DBC1-DBC2, executed delay slots — wave-11 spill fix) F495/F48F abutting e
; ORIGIN 0xDBC1
	.sect ".text"
	.mmregs
	.global _start
_start:
	nop
	norm   a
