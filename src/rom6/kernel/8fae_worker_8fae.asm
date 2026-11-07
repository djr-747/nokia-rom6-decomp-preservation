; ROM6 0x8FAE WORKER_8FAE -- 86w, symbols.yaml data_word.
; Evidence: Entry F074 0668 4A11 E800; bound 8FAE-9003 (FC00@9003); caller F274@8C92 (objdump-verified calld); interior F074 0668; HYPOTHESIS.
; ORIGIN 0x8FAE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x668
	pshm   ar1
	ld     #0,a
	max    b
	stm    #12047,ar0
	pshm   bl
	stm    #12048,ar5
	stm    #12050,ar6
	fcalld 0x1a50d
	stm    #12049,ar7
	ld     #0,b
	popm   bl
	sfta   b,1
	stlm   b,t
	popm   ar1
	ld     #0,a
	stm    #12328,ar3
	fcalld 0x1a54e
	stm    #12346,ar2
	stm    #12346,ar3
	stm    #12038,ar2
	fcalld 0x1a4f6
	stm    #12035,ar5
	stm    #3277,ar1
	stm    #12039,ar3
	ld     *(0x2f03),b
	fcalld 0x1a59c
	stm    #12328,ar2
	stm    #12052,ar6
	ld     *(0xa44),a
	add    *(0xa43),a
	sfta   a,-2
	sth    b,*ar6
	stm    #0,t
	xc     2,agt
	st     #1,*ar6
	stm    #12038,ar2
	stm    #12035,ar3
	stm    #12047,ar0
	stm    #12060,ar5
	rpt    #5
	mvkd   0xb3b0,*ar5-
	mar    *ar5+
	fcalld 0x1a622
	stm    #12049,ar7
	ld     *(0x2f0f),a
	fcalld 0x1a6e2
	ld     *(0x2f10),b
	fcalld 0x1a704
	stm    #5,t
	ret
