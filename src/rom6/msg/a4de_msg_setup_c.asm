; ROM6 0xA4DE MSG_SETUP_C -- 55w, symbols.yaml data_word.
; Evidence: Entry F074 0658 7713 262F 1183 7083; first-RET @0xA514 (len 55); 11 callers A27B A28F AFCA B057 B084 B0C9 B138 B161 B188 B2D2 B34B; body calls 0x658/0x463B/calld-ABD2; head exits: 
; ORIGIN 0xA4DE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x658
	stm    #9775,ar3
	ld     *ar3,b
	mvkd   0x262c,*ar3
	rcd    beq
	stm    #-1,ar4
	ld     *(0x2615),a
	cmpm   *(0x250f),#34
	bc     0xa4f3,ntc
	sub    #3650,a
	b      0xa4f5
	sub    #3400,a
	cmpm   *ar3,#80
	stm    #1,ar3
	xc     2,alt
	stm    #0,ar4
	ld     #0,a
	bc     0xa506,ntc
	ld     *(0x2639),a
	and    #256,a
	andm   #-257,*(0x2639)
	call   0x463b
	stl    a,*(0x262e)
	stm    #9361,ar3
	ld     #0,a
	stl    a,*ar3+
	stl    a,*ar3+
	calld  0xabd2
	stm    #9752,ar2
	ld     #1,b
	ret
