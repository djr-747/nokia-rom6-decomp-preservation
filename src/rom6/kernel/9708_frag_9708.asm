; ROM6 0x9708 FRAG_9708 -- 3w, symbols.yaml data_word.
; Evidence: Bound 9708-970A (3w micro: RETD FE00@9708 + delays 9709-970A (orm 2w), byte-verified; exit scan clean); entry bc F820@9702->9708 byte-verified (cond ntc, exterior from FRAG_9700 [9
; ORIGIN 0x9708
	.sect ".text"
	.mmregs
	.global _start
_start:
	retd
	orm    #2048,*ar4
