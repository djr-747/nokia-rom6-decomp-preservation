; ROM6 0xDACF FRAG_DACF -- 3w, symbols.yaml data_word.
; Evidence: Bound DACF-DAD1 (3w micro: RETD FE00@DACF + delays DAD0-DAD1 (addm 2w), byte-verified; exit scan clean); entry bc F844@DACA->DACF byte-verified (cond aneq, exterior from FRAG_DAC9 
; ORIGIN 0xDACF
	.sect ".text"
	.mmregs
	.global _start
_start:
	retd
	addm   #-1,0x5e
