; ROM6 0xAA56 FRAG_AA56 -- 19w, symbols.yaml data_word.
; Evidence: Bound AA56-AA68 (19w; exit RET FC00@AA68 byte-verified, exit scan clean); post-RET head (FC00@AA55); no interior exit-class; chain link; HYPOTHESIS.
; ORIGIN 0xAA56
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
	ld     #1,a
	calld  0xd0be
	stl    a,*(0xecc)
	ret
