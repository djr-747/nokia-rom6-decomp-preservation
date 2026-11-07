; ROM6 0x6AE9 FRAG_6AE9 -- 61w, symbols.yaml data_word.
; Evidence: Bound 6AE9-6B25 (61w; NO own exit: exit scan clean of RET/FE00/BD/BACC/F073 — falls into SPANHEAD_ 6B26, tail-frag abut like FRAG_6753; interior join B F073@6B13->6B22); entries br
; ORIGIN 0x6AE9
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    *ar4,b
	stm    #21845,t
	mpyr   *(0xb),b
	sfta   b,-16
	ld     #3,a
	min    b
	stlm   b,t
	dld    *ar2,a
	norm   a
	dst    a,*ar2
	mpy    #3,a
	add    *ar4,a
	stl    a,*ar4
	call   0x5a2
	cmpm   *(0x250f),#34
	bc     0x6b26,ntc
	bitf   *(0x2639),#32
	ld     #7,b
	and    *(0x3490),b
	add    #15060,b,a
	stlm   a,ar3
	ld     #1,a
	and    *(0x2628),a
	xc     2,tc
	mvdk   *ar3,0x245c
	bc     0x6b15,aeq
	st     #0,*ar3
	b      0x6b22
	sub    #1,b
	bc     0x6b22,tc
	xc     2,beq
	mvkd   0x3483,*ar3
	xc     2,blt
	mvkd   0x248d,*ar3
	xc     2,bgt
	mvkd   0x348b,*ar3
	call   0x712d
	bc     0x6b3f,ntc
