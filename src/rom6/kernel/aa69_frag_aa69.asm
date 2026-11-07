; ROM6 0xAA69 FRAG_AA69 -- 19w, symbols.yaml data_word.
; Evidence: Bound AA69-AA7B (19w; exit RET FC00@AA7B byte-verified, exit scan clean); post-RET head (FC00@AA68); no interior exit-class; chain end (gap A9E9-AA7B fully covered); HYPOTHESIS.
; ORIGIN 0xAA69
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
	ld     #2,a
	calld  0xd0be
	stl    a,*(0xecc)
	ret
