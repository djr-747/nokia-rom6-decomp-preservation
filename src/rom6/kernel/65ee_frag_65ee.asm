; ROM6 0x65EE FRAG_65EE -- 105w, symbols.yaml data_word.
; Evidence: Bound 65EE-6656 (exit F073@6655->6666 + operand); 9 conditional-branch entries (F845@65D6/65F0/6613, F844@6617, F842@662F/6638/6640, F843@6644, F84C@6633) targeting 65EE/65FA/6619/
; ORIGIN 0x65EE
	.sect ".text"
	.mmregs
	.global _start
_start:
	and    #64,b,a
	bc     0x65fa,aeq
	andm   #-65,*ar0
	orm    #512,*ar2
	bd     0x676a
	st     #0,*ar5
	andm   #-1025,*(0x51e)
	st     #0,*(0x56c)
	ld     *(0x53c),b
	cmpm   *(0xb),#3
	bc     0x6679,ntc
	stm    #1341,ar1
	stm    #1359,ar2
	bitf   *ar2,#4096
	bc     0x6657,ntc
	ld     *(0x250c),a
	sub    #2,a
	bc     0x6619,aeq
	sub    #2,a
	bc     0x6650,aneq
	pshm   ar1
	calld  0x6993
	stm    #12248,ar1
	popm   ar1
	ld     #-1,b
	ld     *ar1,a
	sub    *(0x2fd9),a
	add    *(0x2fd7),a
	nop
	nop
	xc     2,alt
	add    #204,a
	add    #1,b
	sub    #51,a
	bc     0x662b,ageq
	sub    *(0x563),b
	bc     0x6650,bneq
	ld     *ar1,a
	sub    #51,a
	bc     0x6636,ageq
	add    #51,a
	ld     #7,b
	add    *(0x2642),b
	sub    b,a
	bc     0x6650,ageq
	add    #13,a
	bc     0x6650,alt
	ld     #51,a
	add    *ar1,a
	sub    #204,a
	nop
	nop
	xc     2,alt
	add    #204,a
	stl    a,*ar1
	stm    #12249,ar2
	ld     #204,a
	call   0x6976
	b      0x6666
