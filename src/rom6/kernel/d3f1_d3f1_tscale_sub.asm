; ROM6 0xD3F1 D3F1_TSCALE_SUB -- 84w, symbols.yaml data_word.
; Evidence: Entry mpy #5462 T-scale, stores DP+0x01/0x05; first exit retd FE00 @D444 +2 delays (Bound D445-D446, executed delay slots — wave-11 spill fix); caller F274 @D818 verified; block B 
; ORIGIN 0xD3F1
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #2915,ar5
	stm    #2916,ar4
	mvkd   0xb65,0x05
	sub    a,b
	and    b,a
	bcd    0xd42a,aneq
	st     #0,0x01
	bit    *ar2,13
	bc     0xd417,tc
	ld     0x00,a
	sub    #463,a
	bc     0xd414,ageq
	ld     #5,a
	add    0x00,a
	stlm   a,t
	mpy    #5462,a
	ld     #17,b
	add    a,-16,b
	stl    b,0x05
	add    b,1
	ld     #105,a
	sub    b,1,a
	bd     0xd417
	add    0x00,a
	stl    a,0x01
	add    #95,a
	stl    a,0x05
	ld     0x05,a
	sub    #5,a
	ld     #18,b
	max    a
	stl    a,*ar5
	add    #9,a
	stl    a,*ar4
	ld     #143,b
	sub    b,a
	bc     0xd443,aleq
	sub    #9,b,a
	bd     0xd443
	stl    b,*ar4
	stl    a,*ar5
	bit    *ar2,13
	ld     0x00,a
	bcd    0xd443,tc
	sub    #61,a,b
	bc     0xd443,bgeq
	add    #5,a
	stlm   a,t
	mpy    #5462,a
	ldm    ah,a
	sub    #1,a
	add    *ar5,a,b
	stl    b,0x05
	add    a,1
	ld     0x00,b
	sub    #3,b
	sub    a,1,b
	stl    b,0x01
	ld     0x05,16,a
	retd
