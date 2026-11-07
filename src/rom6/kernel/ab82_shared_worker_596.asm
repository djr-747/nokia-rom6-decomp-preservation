; ROM6 0xAB82 SHARED_WORKER_596 -- 80w, symbols.yaml data_word.
; Evidence: Entry F074 0596 4A12 7712 0013 60F8; first-RET @0xABD1 (len 80); objdump call 0x596 + cmpm *(0x250F)/*(0x34BF); 3 callers A3ED A47F A4B4-calld; HYPOTHESIS audio/message shared work
; ORIGIN 0xAB82
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x596
	pshm   ar2
	stm    #19,ar2
	cmpm   *(0x250f),#34
	bc     0xab9c,ntc
	cmpm   *(0x34bf),#4
	stm    #39,ar2
	xc     2,tc
	stm    #58,ar2
	cmpm   *(0x34bf),#0
	nop
	nop
	xc     2,tc
	stm    #19,ar2
	stm    #9831,ar3
	sub    #64,a
	bc     0xaba8,aneq
	stm    #23,ar2
	stm    #128,ar3
	sub    #64,b
	ld     #0,a
	popm   al
	stm    #10,ar4
	sub    #294,b
	bc     0xabb4,aneq
	stm    #2,ar4
	sub    #-192,b
	bc     0xabbd,bgeq
	ld     #0,a
	portr  14,*(0x8)
	and    #16383,a
	add    a,b
	stlm   b,ar1
	cmpm   *(0x262c),#64
	bc     0xabcc,tc
	cmpm   *(0x262c),#80
	bc     0xabcc,tc
	ld     *(0x2611),b
	b      0xabce
	ld     *(0x260e),b
	ldm    ar4,a
	call   0x3d79
	ret
