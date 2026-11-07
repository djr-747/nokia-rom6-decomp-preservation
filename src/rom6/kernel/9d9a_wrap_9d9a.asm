; ROM6 0x9D9A WRAP_9D9A -- 61w, symbols.yaml data_word.
; Evidence: Entry F074 06BE 10F8 085D 771A 009F 60F8 0573; callers F274@9E00/9E10; first-RET @0x9DD6 (61w); HYPOTHESIS.
; ORIGIN 0x9D9A
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6be
	ld     *(0x85d),a
	stm    #159,brc
	cmpm   *(0x573),#-20649
	bc     0x9dad,ntc
	and    #8,a,b
	bc     0x9dbb,beq
	and    #4,a
	b      0x9db3
	and    #4,a,b
	bc     0x9dbb,beq
	and    #8,a
	rptbd  0x9dba
	stm    #10697,ar2
	ld     *ar3+,16,b
	xc     1,aneq
	add    *ar2,16,b
	sth    b,*ar2+
	ld     *(0x85d),a
	and    #3,a,b
	and    #12,a
	bc     0x9dd7,aeq
	bitf   *(0x2aeb),#1
	andm   #-24577,*(0x860)
	bitf   *(0x2aee),#1
	xc     2,tc
	orm    #8192,*(0x860)
	xc     2,tc
	orm    #16384,*(0x860)
	call   0x9c99
	ret
