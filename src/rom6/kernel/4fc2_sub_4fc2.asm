; ROM6 0x4FC2 SUB_4FC2 -- 52w, symbols.yaml data_word.
; Evidence: Entry F074 059C; bound 4FC2-4FF5 (exit FE00@4FF3 + stl delays 4FF4/4FF5); caller F274@4C21 objdump- verified (calld 0x4fc2); rptbd squra/abs leaf; interior call F074@4FDF->4348; HY
; Pool: SQURA/SQUR squares (square family oracle-unbound; same class as the 4146 squr note) plus retd-delayed exit; stays .asm, bytes verified.
; ORIGIN 0x4FC2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	stm    #9312,ar2
	stm    #7,brc
	rptbd  0x4fcd
	ld     #0,a
	ld     #0,b
	squra  *ar2,b
	add    *ar2+,16,a
	sub    #121,16,a
	bc     0x4ff2,aleq
	add    #121,16,a
	exp    a
	nop
	norm   a
	norm   b
	norm   b
	squr   a,a
	stm    #12065,ar4
	sth    a,*ar4
	sub    a,-3,b
	abs    b,a
	call   0x4348
	stm    #8,ar4
	mpy    *ar4,#20,a
	sfta   a,-12
	add    #44,a
	ld     #50,b
	max    a
	ld     #65,b
	min    a
	stm    #12137,ar4
	sub    *ar4,a
	ld     #0,b
	nop
	xc     1,alt
	ld     #1,b
	retd
	stl    b,*(0x2f1d)
