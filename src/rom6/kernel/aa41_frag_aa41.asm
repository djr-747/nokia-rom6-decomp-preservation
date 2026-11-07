; ROM6 0xAA41 FRAG_AA41 -- 21w, symbols.yaml data_word.
; Evidence: Bound AA41-AA55 (21w; exit RET FC00@AA55 byte-verified, exit scan clean); post-RET head (FC00@AA40); no interior exit-class; chain link; HYPOTHESIS.
; ORIGIN 0xAA41
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
	call   0xcfbd
	ld     #0,a
	calld  0xd0be
	stl    a,*(0xecc)
	ret
