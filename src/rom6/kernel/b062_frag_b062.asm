; ROM6 0xB062 FRAG_B062 -- 30w, symbols.yaml data_word.
; Evidence: Bound B062-B07F (30w, exit FC00@B07F); post-RET head (after FC00@B061); AFF9-idiom lane; HYPOTHESIS.
; ORIGIN 0xB062
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8716,ar5
	cmpm   *(0x2510),#192
	bc     0xb07b,ntc
	bitf   *(0x51f),#6144
	bc     0xb07b,tc
	bitf   *(0x51c),#3
	ld     *(0x2efe),a
	bc     0xb07b,tc
	bc     0xb07b,aneq
	fcall  0x18060
	calld  0xa2b9
	stm    #-8711,ar5
	ret
