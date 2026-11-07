; ROM6 0x3753 FRAG_3753 -- 11w, symbols.yaml data_word.
; Evidence: Bound 3753-375D (11w; exit B F073@375C->2E64 + operand 375D, byte-verified; exit scan clean); entry bc F820@3731->3753 byte-verified (cond ntc, exterior from FRAG_372E [372E-3752] 
; ORIGIN 0x3753
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x8),#10
	bc     0x375e,ntc
	fcall  0x1aa2c
	call   0x2e2f
	b      0x2e64
