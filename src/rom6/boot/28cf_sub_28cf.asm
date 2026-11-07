; ROM6 0x28CF SUB_28CF -- 7w, symbols.yaml program_word.
; Evidence: Bound 28CF-28D5 (7w); entry TRACE (8210 boot-to-registration DSP PC histogram docs/evidence/dsp-pchist-8210-boot-20261106/pchist.txt: 28CF/D1/D4 x10681); COBBA bring-up head (stm/c
; ORIGIN 0x28CF
	.sect ".text"
	.global _start
_start:
	stm    #1160,ar2
	cmpm   *(0x250f),#34
	bc     0x2917,ntc
