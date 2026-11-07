; ROM6 0x7C03 SUB84_7C03 -- 41w, symbols.yaml data_word.
; Evidence: Entry F074 05A0 60F8 0013 0001 F020; RET @7C56 len 84; 0 callers; inner 0x05A0/0x42B8; min/max+subc math; HYPOTHESIS. Head-fill Bound 7C03-7C2B (wave-5: exit B@7C2A->7BEE chained i
; ORIGIN 0x7C03
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5a0
	cmpm   *(0x13),#1
	ld     #8357,a
	min    a
	xc     1,ntc
	sfta   a,1
	stlm   a,ar6
	ld     *ar1,a
	ld     #1460,b
	min    a
	ld     #732,b
	max    a
	stm    #7000,t
	mpy    *(0x8),a
	sftl   a,-13
	mvdk   *(0x16),0xe
	mpy    *(0x8),a
	sftl   a,-13
	sub    *ar5,a,b
	bc     0x7c2c,blt
	rpt    #15
	subc   *ar5,a
	and    #-1,a
	add    #1,a
	b      0x7bee
