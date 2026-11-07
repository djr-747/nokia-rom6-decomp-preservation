; ROM6 0x4944 SUB_4944 -- 66w, symbols.yaml data_word.
; Evidence: Entry F074 059C; bound 4944-4985 (exit F073@4984->4996 + operand 4985); caller F074@A4DB (byte- verified F074 4944); interior bc joins (image-wide sweep: bc->4925 etc.); HYPOTHESIS
; ORIGIN 0x4944
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	ld     *(0x262b),b
	sub    #176,b
	bc     0x4996,bneq
	cmpm   *(0x250f),#34
	bc     0x4986,ntc
	cmpm   *(0x34bf),#1
	bc     0x4974,tc
	cmpm   *(0x34bf),#4
	bc     0x4974,tc
	cmpm   *(0x34bf),#3
	ld     *(0x3670),b
	bc     0x4972,bleq
	ld     *(0x366f),b
	sub    #15,b
	bc     0x4972,beq
	addm   #-1,*(0x3670)
	stm    #10887,ar5
	xc     2,tc
	stm    #1173,ar5
	andm   #-513,*ar5
	bc     0x4996,ntc
	ld     *(0x37b1),b
	bc     0x4996,bleq
	ld     *(0x37b0),b
	sub    #15,b
	bc     0x4996,beq
	addm   #-1,*(0x37b1)
	andm   #-513,*(0x2a87)
	b      0x4996
