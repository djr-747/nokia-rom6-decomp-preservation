; ROM6 0x4F3A SUB_4F3A -- 37w, symbols.yaml data_word.
; Evidence: Bound 4F3A-4F5E (exit FE00@4F5C + slots = gap end); caller F274@4BC1; HYPOTHESIS.
; ORIGIN 0x4F3A
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	mvdm   0x2f80,al
	mvdm   0x2f81,ah
	stm    #15,brc
	stm    #1,ar1
	ld     #698,b
	rptb   0x4f4c
	sfta   a,-1
	nop
	nop
	xc     1,c
	xor    b,a
	mvdm   0x2f82,ah
	banzd  0x4f46,*ar1-
	stm    #8,brc
	and    #1023,a
	cmpm   *(0x8),#1023
	stm    #0,ar1
	xc     1,ntc
	mar    *ar1+
	retd
	mvmd   ar1,0x2f20
