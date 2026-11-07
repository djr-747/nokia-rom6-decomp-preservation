; ROM6 0xE442 SUB41_E442 -- 41w (overlap-split wave-12).
; Evidence: Bound E442-E46A (entry ld *ar3,10,a; mpya/maca lanes; first exit retd @E468 + delays E469-E46A incl operand, len 41 per original header). Callers F274 @E3B9/E3C7/E42E verified (retained). Former span dropped the delay words (39w); restored wave-12 (e46a twin, which held delay-word E46A, deleted). Recombine-clean.
; ORIGIN 0xE442
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar3,10,a
	add    *ar2+,14,a
	mpya   *ar3
	sth    a,0x70
	and    0x68,a
	stl    a,0x71
	ld     a,15,a
	mpya   a
	maca   0x64,b
	ld     b,1,a
	sub    0x6a,16,a
	add    *ar2+,14,a
	mpya   *ar3
	sth    a,0x72
	and    0x68,a
	stl    a,0x73
	ld     a,15,a
	mpya   a
	maca   0x64,b
	ld     b,1,a
	dsub   0x70,a
	add    *ar2+,14,a
	mpya   *ar3
	sth    a,0x70
	and    0x68,a
	stl    a,0x71
	ld     a,15,a
	mpya   a
	maca   0x64,b
	ld     b,1,a
	dsub   0x72,a
	add    *ar2+,14,a
	mpya   *ar3
	and    0x68,a
	ld     a,15,a
	mpya   a
	maca   0x64,b
	dsub   0x70,b
	retd
	; @E469 91cd add    *ar2+0%,13,b
	add    *ar2+0%,13,b
	; @E46A f666 sfta   b,6,a
	sfta   b,6,a
