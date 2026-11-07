; ROM6 0x36F0 FRAG_36F0 -- 11w, symbols.yaml data_word.
; Evidence: Bound 36F0-36FA (11w; exit B F073@36F9->2E64 + operand 36FA, byte-verified; exit scan clean); entry bc F820@36E4->36F0 byte-verified (chained from FRAG_36E1 interior); dispatcher-c
; ORIGIN 0x36F0
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x8),#3
	bc     0x36fb,ntc
	fcall  0x1aa2c
	call   0x2e2f
	b      0x2e64
