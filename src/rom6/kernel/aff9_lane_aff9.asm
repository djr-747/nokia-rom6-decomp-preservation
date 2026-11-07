; ROM6 0xAFF9 LANE_AFF9 -- 30w, symbols.yaml data_word.
; Evidence: Bound AFF9-B016 (30w, exit FC00@B016); post-RET head (after FC00@AFF8); entry F274 A2B9 calld (AFB5-table arm); F820@B000 falls THROUGH to B002 (paradigm case for F820-conditional)
; ORIGIN 0xAFF9
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8751,ar5
	cmpm   *(0x2510),#192
	bc     0xb012,ntc
	bitf   *(0x51f),#6144
	bc     0xb012,tc
	bitf   *(0x51c),#3
	ld     *(0x2efe),a
	bc     0xb012,tc
	bc     0xb012,aneq
	fcall  0x18060
	calld  0xa2b9
	stm    #-8746,ar5
	ret
