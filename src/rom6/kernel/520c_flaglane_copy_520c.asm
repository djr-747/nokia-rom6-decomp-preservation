; ROM6 0x520C FLAGLANE_COPY_520C -- 118w, symbols.yaml data_word.
; Evidence: Entry F074 059C 7711 2628 6181 0001 FA20 5218; bound 520C-5281; caller existing 51D8 (post-RET abut 520B); flag lanes 2628/265C/2627/263B/2639 + triple rpt-mvdd; interior b@5261->5
; ORIGIN 0x520C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	stm    #9768,ar1
	bitf   *ar1,#1
	bcd    0x5218,ntc
	stm    #9767,ar2
	andm   #-8193,*ar2
	bitf   *(0x2512),#128
	bc     0x5220,ntc
	bitf   *ar1,#32
	rc     ntc
	ld     *(0x265c),a
	ld     *ar2,b
	bc     0x5228,aeq
	or     #8192,b
	stl    b,*ar2
	and    #16,b,a
	rc     aeq
	and    #-17,b
	stl    b,*ar2
	orm    #2,*ar1
	stm    #9786,ar2
	andm   #-2,*ar2
	ld     *(0x2639),b
	and    #1,b
	or     *ar2,b
	stl    b,*ar2
	mvdk   *(0x2655),0x2654
	stm    #9633,ar2
	stm    #12554,ar3
	rpt    #31
	mvdd   *ar2+,*ar3+
	stm    #9364,ar2
	stm    #12586,ar3
	rpt    #95
	mvdd   *ar2+,*ar3+
	stm    #985,ar2
	stm    #12682,ar3
	rpt    #31
	mvdd   *ar2+,*ar3+
	mvdk   *(0x265c),0x31aa
	bitf   *(0x3ec8),#16
	bc     0x5263,ntc
	stm    #949,ar2
	stm    #9633,ar3
	rpt    #31
	mvdd   *ar2+,*ar3+
	ld     *(0x588),b
	stl    b,*(0x265c)
	b      0x5273
	stm    #980,ar2
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     2,tc
	mar    *+ar2(0x4)
	calld  0x434f
	stm    #9633,ar3
	stl    b,*(0x265c)
	stm    #9767,ar2
	rcd    beq
	andm   #-8193,*ar2
	orm    #8192,*ar2
	bitf   *(0x263a),#4096
	bc     0x5282,ntc
	call   0x6f79
	ret
