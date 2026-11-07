; ROM6 0x32EE WORKER_32EE -- 24w, symbols.yaml data_word.
; Evidence: Entry 771A 0001 (stm #1,brc + rptbd), post-ret (FC00@32ED); bound 32EE-3305 (24w, exit F073@3304->2E64); interior call 3302->2E2F; no interior joins; HYPOTHESIS.
; ORIGIN 0x32EE
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1,brc
	rptbd  0x32f8
	stm    #9765,ar4
	ldu    *ar2+0%,a
	sftl   a,-8,b
	sftl   a,8
	or     a,b
	stl    b,*ar4+
	bitf   *ar2+%,#-1
	stm    #1309,ar3
	andm   #-65,*ar3
	xc     2,tc
	orm    #64,*ar3
	call   0x2e2f
	b      0x2e64
