; ROM6 0x99A4 MSG_HEADER_BUILDER -- 66w, symbols.yaml data_word.
; Evidence: Called from 0x9425; LD *(0x21FD) - *(0x21FC) ring-space math; header OR #0x1C00/#0x1E00 tag bits; RPTB XOR rolling-checksum copy *ar2+ -> *ar3+% with byte-lane AND #1/#-256; MVMD A
; ORIGIN 0x99A4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5cc
	rc     blt
	stlm   a,ar4
	ld     *(0x21fd),a
	sub    *(0x21fc),a
	nop
	nop
	xc     2,aleq
	add    #250,a
	add    a
	sub    b,a
	sub    #9,a
	rc     aleq
	ldm    ar4,a
	bitf   *(0x8),#-256
	bc     0x99c4,tc
	bitf   *(0x20ff),#2
	or     #7168,a
	xc     2,ntc
	or     #7680,a
	stlm   b,ar5
	stl    a,*ar3+%
	ld     a,b
	ldm    ar0,b
	stl    b,*ar3+%
	xor    b,a
	ldm    ar5,b
	stl    b,*ar3+%
	xor    b,a
	sftl   b,-1
	sub    #1,b
	stlm   b,brc
	bc     0x99d8,blt
	rptb   0x99d7
	ld     *ar2+,b
	xor    b,a
	stl    b,*ar3+%
	ldm    ar5,b
	and    #1,b
	bc     0x99e2,beq
	ld     *ar2+,b
	and    #-256,b
	xor    b,a
	stl    b,*ar3+%
	stl    a,*ar3+%
	retd
	mvmd   ar3,0x21fc
