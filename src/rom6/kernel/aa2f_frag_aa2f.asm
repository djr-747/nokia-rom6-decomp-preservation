; ROM6 0xAA2F FRAG_AA2F -- 18w, symbols.yaml data_word.
; Evidence: Bound AA2F-AA40 (18w; exit RET FC00@AA40 byte-verified, exit scan clean); post-RET head (FC00@AA2E = FRAG_A9E9 exit, zero exterior refs); no interior exit-class; chain link; HYPOTH
; ORIGIN 0xAA2F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x688
	bitf   *(0x263a),#512
	rc     tc
	ld     *(0xb67),a
	rc     aneq
	bitf   *(0x51c),#3
	rc     tc
	call   0xcf25
	call   0xcf4b
	ret
