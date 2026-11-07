; ROM6 0x2E84 WORKER_2E84 -- 66w, symbols.yaml data_word.
; Evidence: Entry 12D2 F030 00FF (ldu *ar2+%,a; and#255); bound 2E84-2EC5 (66w, exit F073@2EC4->2E64 + operand 2EC5); ret-boundary entry (FC00@2E83; interior join 2E84<-2E79/F84D); interior jo
; ORIGIN 0x2E84
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldu    *ar2+%,a
	and    #255,a
	ldu    *ar2,b
	sftl   b,-8
	stlm   b,ar1
	ldm    ar5,b
	sub    #2,b
	b      0x2eb7
	bitf   *(0x866),#1
	bc     0x2ead,ntc
	call   0x2d8f
	bc     0x2eb7,agt
	ssbx   st1,intm
	ld     #2,a
	nop
	portw  *(0x8),1
	rpt    #20
	nop
	andm   #-2,*(0x866)
	portr  2,*(0x8)
	and    #-3,a
	nop
	portw  *(0x8),2
	rsbx   st1,intm
	bitf   *(0x866),#2
	rc     ntc
	andm   #-3,*(0x866)
	call   0x2de4
	rc     aeq
	call   0x620
	stlm   b,ar4
	sub    #87,a,b
	bc     0x2ecd,bleq
	sub    #112,a,b
	bc     0x2ec6,bneq
	call   0x43ba
	b      0x2e64
