; ROM6 0xB036 FRAG_B036 -- 21w, symbols.yaml data_word.
; Evidence: Bound B036-B04A (21w, exit FC00@B04A); post-RET head (after FC00@B035 of LANE_B017); HYPOTHESIS.
; ORIGIN 0xB036
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #2504,ar4
	fcalld 0x1a8fd
	stm    #12074,ar3
	fcall  0x1a260
	call   0xa5e1
	ld     *(0x2efe),a
	bc     0xb046,aneq
	fcall  0x180a7
	calld  0xa2b9
	stm    #-8739,ar5
	ret
