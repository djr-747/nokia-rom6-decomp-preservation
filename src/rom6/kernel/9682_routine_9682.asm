; ROM6 0x9682 ROUTINE_9682 -- 52w, symbols.yaml data_word.
; Evidence: Entry F074 05C4 F7BB F020; bound 9682-96B5 (exit FE00@96B3 + slots 96B4/96B5); callers F074 @93A0/979E/97B5/993E (all verified); interior F074 05C4; 96B6-96BC retd sliver belongs t
; ORIGIN 0x9682
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5c4
	ssbx   st1,intm
	ld     #8192,a
	stm    #8698,ar2
	stl    a,*ar2+
	stl    a,*ar2+
	ld     #8448,a
	stl    a,*ar2+
	stl    a,*ar2
	stm    #8442,ar2
	rptz   a,#4
	stl    a,*ar2+
	stm    #8702,ar2
	rpt    #3
	stl    a,*ar2+
	stm    #8447,ar2
	andm   #4095,*ar2
	bitf   *ar2,#512
	bc     0x96b6,tc
	bitf   *ar2,#256
	bc     0x96b6,tc
	portr  54,*(0xb)
	and    #128,b
	ld     #0,a
	bitf   *ar2,#2
	xc     1,beq
	ld     #2,a
	stl    a,*(0x20fc)
	ld     #1,a
	xc     1,tc
	ld     #0,a
	retd
	stl    a,*(0x2201)
