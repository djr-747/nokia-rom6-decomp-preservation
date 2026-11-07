; ROM6 0x670D FRAG_670D -- 70w, symbols.yaml data_word.
; Evidence: Bound 670D-6752 (exit F073@6751->676A + operand 6752, byte-verified; SHORT form — res1 long 670D-6866 draft killed: interior outside-exit @6751); entries bc F820@64B1 + F830@64B6 (
; ORIGIN 0x670D
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0xb),#64
	bc     0x6717,tc
	cmpm   *(0xb),#128
	bc     0x676a,ntc
	stm    #9794,ar1
	ld     #51,b
	calld  0x6961
	stm    #12247,ar2
	stm    #12253,ar0
	stl    b,*ar0
	ld     #51,b
	calld  0x6961
	stm    #9795,ar1
	ld     *ar0,a
	min    b
	stl    b,*ar0
	stm    #9792,ar1
	ld     #102,b
	calld  0x6961
	stm    #12250,ar2
	ld     *ar0,a
	min    b
	stl    b,*ar0
	stm    #9793,ar1
	ld     #102,b
	calld  0x6961
	stm    #12250,ar2
	ld     *ar0,a
	min    b
	stl    b,*ar0
	ld     *(0x53c),a
	cmpm   *(0x8),#4
	bc     0x6753,ntc
	sub    #14,b,a
	bc     0x676a,alt
	call   0x697f
	st     #0,*(0x2615)
	calld  0x6987
	stm    #12247,ar2
	b      0x676a
