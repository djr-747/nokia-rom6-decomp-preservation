; ROM6 0x53EB DISPATCH_P_LANES -- 53w, symbols.yaml data_word.
; Evidence: Bounds 5395-53B9 + 53BA-53D8 + 53D9-53EA + 53EB-541F + 5420-5433 + 5434-5449 + 544A-546A + 546B-5488 + 5489-54A3 (P1-P7c dispatch lanes, all converge F073->54BB; P4/P7b tail-merge 
; ORIGIN 0x53EB
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6e2
	andm   #-873,*(0x537)
	andm   #-5,*(0x51d)
	andm   #-513,*(0x263a)
	mvkd   0x3f12,*(0x57b)
	ld     *(0x2477),a
	stm    #1308,ar2
	andm   #-129,*ar2
	xc     2,aeq
	orm    #128,*ar2
	cmpm   *(0x573),#-20649
	bc     0x5409,ntc
	b      0x54bb
	call   0x6e2
	cmpm   *(0x573),#-23991
	bc     0x5420,ntc
	andm   #-129,*ar2
	call   0x8641
	call   0x864e
	call   0xb6e6
	call   0xc717
	call   0x9fa8
	ld     *(0x3fc7),a
	b      0x53cd
