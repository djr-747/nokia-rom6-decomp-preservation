; ROM6 0x5395 DISPATCH_P_LANES -- 37w, symbols.yaml data_word.
; Evidence: Bounds 5395-53B9 + 53BA-53D8 + 53D9-53EA + 53EB-541F + 5420-5433 + 5434-5449 + 544A-546A + 546B-5488 + 5489-54A3 (P1-P7c dispatch lanes, all converge F073->54BB; P4/P7b tail-merge 
; ORIGIN 0x5395
	.sect ".text"
	.mmregs
	.global _start
_start:
	nop
	call   0x672
	andm   #-873,*(0x537)
	andm   #-5,*(0x51d)
	andm   #-513,*(0x263a)
	ld     #572,a
	stm    #11988,ar2
	rpt    #29
	stl    a,*ar2+
	sth    a,*(0x2efd)
	stm    #1308,ar2
	andm   #-129,*ar2
	st     #1,*(0x2efe)
	mvkd   0x3f13,*(0x57b)
	cmpm   *(0x573),#-20565
	bc     0x53ba,ntc
	b      0x54bb
