; ROM6 0xB0E8 FRAG_B0E8 -- 13w, symbols.yaml data_word.
; Evidence: Bound B0E8-B0F4 (13w; exit RET FC00@B0F4 byte-verified, exit scan clean); entries bc F820@B0E2-> B0E8 byte-verified (head) + B F073@B0E6->B0F0 mid-span (bytes verify B0E6 = F073, n
; ORIGIN 0xB0E8
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #2504,ar4
	fcalld 0x1a8fd
	stm    #12074,ar3
	fcall  0x1a260
	calld  0xa2b9
	stm    #-8690,ar5
	ret
