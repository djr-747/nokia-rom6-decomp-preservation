; ROM6 0x2D5E ISR_2D5E -- 45w, symbols.yaml data_word.
; Evidence: Entry F074 0626 61F8 054D 000C F820 2D7F 4A12; bound 2D5E-2D8A (FC00); callers 9x F274 image-wide (incl 50F9/5CE8/5E78/5ED5/7128/978A/21CD/2267 -- CORR: not sole @50F9); interior c
; ORIGIN 0x2D5E
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x626
	bitf   *(0x54d),#12
	bc     0x2d7f,ntc
	pshm   ar2
	pshm   ar3
	stm    #12032,ar3
	st     #1025,*ar3+
	ld     *(0x12),a
	and    #255,a,b
	or     #256,b
	stl    b,*ar3+
	and    #-256,a
	stl    a,*ar3
	ld     #5,b
	stm    #12032,ar2
	ld     #20,a
	stm    #244,ar0
	call   0x93ce
	popm   ar3
	popm   ar2
	ld     *ar3,a
	bc     0x2d8b,aneq
	ldm    ar2,a
	stl    a,*ar3
	orm    #8,*(0x29)
	andm   #-9,*(0x29)
	ret
