; ROM6 0xC38C BYTE_SPLIT_C38C -- 51w, symbols.yaml data_word.
; Evidence: Entry F074 06DA; bound C38C-C3BE; caller C1B9; RPTBD C3BD byte-split + MVDD swap + LD #64 SFTA/OR + SACCD; HYPOTHESIS.
; ORIGIN 0xC38C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6da
	ld     #0,asm
	stm    #11,brc
	stm    #10428,ar1
	stm    #12650,ar3
	stm    #12627,ar4
	stm    #12626,ar5
	rptbd  0xc3bd
	stm    #12594,ar2
	ld     *ar1,a
	and    #255,a,b
	stl    b,7,*ar4
	and    #-256,a
	stl    a,-1,*ar5
	andm   #32767,*ar5
	ld     0x45,a
	bc     0xc3ad,aeq
	mvdd   *ar4,*ar3
	b      0xc3b2
	sub    *ar4,*ar5,a
	nop
	mvdd   *ar5,*ar3
	xc     1,alt
	mvdd   *ar4,*ar3
	ld     #64,b
	add    *ar4,b,a
	and    #-128,a
	sfta   a,1
	add    *ar2,b
	or     b,-7,a
	sub    *ar3,*ar2,b
	stl    a,*ar1+
	ld     *ar3+,16,a
	saccd  a,*ar2+,blt
	ret
