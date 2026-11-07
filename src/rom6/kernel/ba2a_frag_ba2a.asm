; ROM6 0xBA2A FRAG_BA2A -- 8w, symbols.yaml data_word.
; Evidence: Bound BA2A-BA31 (8w; exit retd FE00@BA2F + delays BA30-BA31 included per convention; exit scan clean); entries bc F846@B964->BA2C byte-verified (from FRAG_B948 interior, chained ed
; ORIGIN 0xBA2A
	.sect ".text"
	.mmregs
	.global _start
_start:
	addm   #1,0x04
	st     #0,*(0x2adc)
	retd
	andm   #3,*ar1
