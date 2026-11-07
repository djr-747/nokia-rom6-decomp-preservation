; ROM6 0x2AFC FRAG_2AFC -- 73w, symbols.yaml data_word.
; Evidence: Bound 2AFC-2B44 (73w; exit F073@2B43->2E64 + operand 2B44, single exit-class word, byte-verified); entry bc F84C@281F->2AFC byte-verified (cond, from WORKER_2E84-precursor zone); i
; ORIGIN 0x2AFC
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x64c
	st     #128,*ar2
	nop
	portw  *ar2,1
	rpt    #2
	nop
	stm    #1338,ar4
	stm    #1362,ar2
	mvkd   0x53b,*ar4
	st     #0,*(0x53b)
	bitf   *ar2,#32
	bc     0x2b18,ntc
	bitf   *ar2,#4
	bc     0x2b18,ntc
	orm    #8,*ar2
	stm    #6,bk
	mvdm   0x553,ar3
	orm    #32,*ar2
	portr  19,*ar3+%
	portr  20,*ar3
	andm   #16383,*ar3+%
	portr  21,*ar3
	ld     *ar3+%,a
	mvmd   ar3,0x553
	sub    *(0x557),a
	bc     0x2b35,aneq
	portr  14,*(0x8)
	sub    #4999,a
	neg    a
	add    *ar4,a
	stl    a,*ar4
	bitf   *ar2,#256
	bcd    0x2b43,ntc
	andm   #-257,*ar2
	ld     #1,16,a
	stm    #0,al
	sub    #1,a
	call   0x3ffa
	b      0x283d
