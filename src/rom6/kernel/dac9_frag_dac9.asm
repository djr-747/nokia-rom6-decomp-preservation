; ROM6 0xDAC9 FRAG_DAC9 -- 6w, symbols.yaml data_word.
; Evidence: Bound DAC9-DACE (6w; exit retd FE00@DACC + delays DACD-DACE (765F 0000) included per convention; micro-span); entry bc F84A@DABC->DAC9 byte-verified (from FRAG_DA7E [DA7E-DAC8] int
; ORIGIN 0xDAC9
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     0x5e,a
	bc     0xdacf,aneq
	retd
	st     #0,0x5f
