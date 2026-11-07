; ROM6 0xE54B EXP_NORM_MATH -- 56w, symbols.yaml data_word.
; Evidence: Entry F847 E568 F48E E91E; callers F274 @E08C/E125; exp/norm/sfta lane; first-RET @E582 per survey (interior exit-class words present mid-stream, alignment-unverified, all-paths wa
; ORIGIN 0xE54B
	.sect ".text"
	.mmregs
	.global _start
_start:
	bc     0xe568,aleq
	exp    a
	ld     #30,b
	sub    0x0e,b
	stl    b,0x7d
	bitf   0x7d,#1
	sfta   b,-1
	norm   a
	add    #1,b
	xc     1,ntc
	sfta   a,-1
	sfta   a,-9
	neg    b
	stl    b,0x7d
	add    #-1318,16,a,b
	sth    b,0x12
	ldm    al,a
	sfta   a,-1
	stl    a,0x7e
	ld     *ar2+,16,b
	sub    *ar2-,16,b,a
	masa   0x7e,b
	retd
	ld     0x7d,t
	norm   b,a
	ld     #16383,16,a
	retd
	or     #-1,a
	bc     0xe581,aleq
	exp    a
	ld     #30,b
	sub    0x0e,b
	stl    b,0x7d
	norm   a
	sfta   a,-9
	add    #-1367,16,a,b
	sth    b,0x12
	ldm    al,a
	sfta   a,-1
	stl    a,0x7e
	ld     *ar2+,16,b
	sub    *ar2-,16,b,a
	masa   0x7e,b
	retd
	ld     b,-16,a
	add    0x7d,16,a
	ld     #0,a
	ret
