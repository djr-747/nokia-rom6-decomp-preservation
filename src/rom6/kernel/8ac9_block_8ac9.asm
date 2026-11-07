; ROM6 0x8AC9 BLOCK_8AC9 -- 58w, symbols.yaml data_word.
; Evidence: Entry 802C 762C FFFC 762D; bound 8AC9-8B02 (FC00@8B02); fall-through after F273 bd slots @8AC6 (F273 8ACE); zero calls; HYPOTHESIS.
; ORIGIN 0x8AC9
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,0x2c
	st     #-4,0x2c
	st     #15,0x2d
	ld     0x2d,16,b
	sub    0x29,16,b
	sth    b,0x2d
	rptz   a,#39
	mvmd   al,0x2f2e
	ld     #-19474,a
	add    0x2d,a
	stlm   a,ar4
	ld     #6,a
	sub    0x2c,a
	stl    a,0x2a
	mvdk   *ar4,0x2f29
	sub    0x6f,a
	stl    a,0x2d
	ld     0x2d,t
	ld     0x6f,ts,a
	stl    a,0x2b
	ld     #12078,a
	add    *ar5(0x2),a
	stlm   a,ar2
	stm    #3,ar0
	ld     0x2a,a
	neg    a
	stl    a,0x2a
	ld     0x2a,asm
	ld     0x6e,a
	ld     0x2b,16,b
	stm    #0,bk
	stm    #12075,ar4
	stm    #12,brc
	mvmm   ar5,ar3
	rptbd  0x8b00
	mar    *+ar3(0x4)
	add    *ar3+,1,a
	sfta   a,13
	sfta   a,15
	macar  0x29,b
	ld     0x6e,a
	st     b,*ar2+0% || ld     *ar4,b
	ld     #0,asm
	ret
