; ROM6 0xE80C BLK_E80C -- 43w, symbols.yaml data_word.
; Evidence: Post-RET head; first-RET @E836 (43w); no callers listed; HYPOTHESIS.
; ORIGIN 0xE80C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b0
	st     #0,*(0x244d)
	st     #0,*(0x29a7)
	st     #0,*(0x29a8)
	st     #10927,*(0x29a6)
	andm   #4095,*(0x58f)
	orm    #4096,*(0x58f)
	st     #0,*(0x29af)
	stm    #-18560,ar2
	rpt    #9
	mvdk   *ar2+,0x2992
	andm   #-2,*(0x9f0)
	andm   #-2,*(0xb3a)
	andm   #-2,*(0xc84)
	andm   #-2,*(0xdce)
	call   0x5b0
	ret
