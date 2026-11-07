; ROM6 0x7967 SUB_7967 -- 21w, symbols.yaml data_word.
; Evidence: Entry F074 059E; bound 7967-797B (FC00@797B); caller F074@7726 objdump-verified (call 0x7967); rptbd zero-fill leaf (dst/st/xc), zero interior calls; HYPOTHESIS.
; ORIGIN 0x7967
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	stm    #15,brc
	rptbd  0x797a
	ld     #0,b
	dst    b,*ar4
	bit    *ar5,0
	ld     *ar3+,b
	sfta   a,1
	xc     1,tc
	neg    b
	add    *ar4,b
	stl    b,*ar4+
	ld     *ar3+,b
	xc     1,tc
	neg    b
	add    *ar4,b
	stl    b,*ar4-
	ret
