; ROM6 0x6871 SUB14_6871 -- 14w, symbols.yaml data_word.
; Evidence: Entry E900 10F8 2FD7 F010 0002 F843 687E 0886 F010 0003 F846 687E E901 FC00; first exit ret @687E len 14 entry-linear, interior bc cond only; callers F074 @6497/@6522 objdump-verif
; ORIGIN 0x6871
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,b
	ld     *(0x2fd7),a
	sub    #2,a
	bc     0x687e,alt
	sub    *ar6,a
	sub    #3,a
	bc     0x687e,agt
	ld     #1,b
	ret
