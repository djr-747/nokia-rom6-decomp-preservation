; ROM6 0x687F SUB14_687F -- 14w, symbols.yaml data_word.
; Evidence: Entry E900 10F8 2FD9 F010 009F F843 688C 0886 F010 0003 F846 688C E901 FC00; first exit ret @688C len 14; callers F074 @64A5/@652A verified; HYPOTHESIS.
; ORIGIN 0x687F
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,b
	ld     *(0x2fd9),a
	sub    #159,a
	bc     0x688c,alt
	sub    *ar6,a
	sub    #3,a
	bc     0x688c,agt
	ld     #1,b
	ret
