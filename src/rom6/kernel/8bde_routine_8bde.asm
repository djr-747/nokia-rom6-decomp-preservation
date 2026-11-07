; ROM6 0x8BDE ROUTINE_8BDE -- 44w, symbols.yaml data_word.
; Evidence: Bound 8BDE-8C09 (FC00@8C09 objdump); callers F274 @9CB4/@A728 (both objdump-verified calld); 0612-prologue head; rptbd x2; abuts SUPERBLOCK_8C0A; HYPOTHESIS.
; ORIGIN 0x8BDE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x612
	pshm   st1
	rsbx   st1,cpl
	ssbx   st1,ovm
	ssbx   st1,frct
	ld     #94,dp
	stm    #12157,ar3
	mvmm   ar3,ar2
	stm    #159,brc
	rptbd  0x8bef
	stm    #-3,t
	ld     *ar4+,ts,a
	stl    a,2,*ar3+
	stm    #4096,ar3
	stm    #4097,ar4
	st     #16384,0x22
	ld     #-1,asm
	stm    #159,brc
	rptbd  0x8c07
	stm    #32735,t
	sub    *ar2,*ar3,a
	mvdd   *ar2,*ar3
	mpyr   *ar4+,b
	add    b,-15,a
	mac    *ar4,a
	sfta   a,-1,b
	sth    a,*ar4
	sub    *ar4-,16,a
	stl    a,asm,*ar4
	add    0x22,b
	sth    b,1,*ar2+
	popm   st1
	ret
