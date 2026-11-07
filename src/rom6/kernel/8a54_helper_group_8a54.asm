; ROM6 0x8A54 HELPER_GROUP_8A54 -- 81w, symbols.yaml data_word.
; Evidence: 0612-prologue head F074 0612 4A07 4A12 F6BE F7B9 F7B6 ED00; first-RET @0x8AA4 (len 81); callers 9D79 A775 (F274); fans out 0x8AA5/0x8B03/0x8B30; HYPOTHESIS helper group.
; ORIGIN 0x8A54
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x612
	pshm   st1
	pshm   ar2
	rsbx   st1,cpl
	ssbx   st1,ovm
	ssbx   st1,frct
	ld     #0,asm
	ld     #94,dp
	st     #1,0x6f
	st     #-7,0x6e
	stm    #12144,ar4
	stm    #12440,ar5
	stm    #3,ar7
	pshm   ar4
	call   0x8aa5
	popm   ar4
	call   0x8b03
	banzd  0x8a67,*ar7-
	mar    *+ar5(0x11)
	stm    #12432,ar5
	stm    #-19522,ar3
	stm    #-19514,ar4
	ld     *ar4+,16,b
	stm    #7,brc
	rptbd  0x8a84
	stm    #-19506,ar2
	add    *ar5,*ar3+,a
	sfta   a,10
	sub    b,1,a
	ld     #0,b
	macar  *ar2+,b
	add    b
	st     b,*ar5+ || ld     *ar4+,b
	call   0x8b30
	stm    #12145,ar2
	stm    #4362,ar5
	mvmm   ar2,ar3
	stm    #159,brc
	ld     *ar2+,16,a
	rptbd  0x8a96
	stm    #28180,t
	macr   *ar5,a
	sth    a,*ar5
	add    a
	st     a,*ar3+ || ld     *ar2+,a
	popm   ar3
	stm    #12145,ar2
	ld     *ar2+,16,a
	stm    #159,brc
	rptbd  0x8aa2
	ld     #-8,16,b
	and    b,a
	st     a,*ar3+ || ld     *ar2+,a
	popm   st1
	ret
