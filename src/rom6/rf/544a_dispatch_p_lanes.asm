; ROM6 0x544A DISPATCH_P_LANES -- 33w, symbols.yaml data_word.
; Evidence: Bounds 5395-53B9 + 53BA-53D8 + 53D9-53EA + 53EB-541F + 5420-5433 + 5434-5449 + 544A-546A + 546B-5488 + 5489-54A3 (P1-P7c dispatch lanes, all converge F073->54BB; P4/P7b tail-merge 
; ORIGIN 0x544A
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6e4
	andm   #-873,*(0x537)
	andm   #-5,*(0x51d)
	andm   #-513,*(0x263a)
	mvkd   0x3f14,*(0x57b)
	ld     *(0x2477),a
	stm    #1308,ar2
	andm   #-129,*ar2
	xc     2,aeq
	orm    #128,*ar2
	st     #1,*(0xb67)
	cmpm   *(0x573),#-20196
	bc     0x546b,ntc
	b      0x54bb
