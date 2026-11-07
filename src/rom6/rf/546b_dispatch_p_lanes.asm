; ROM6 0x546B DISPATCH_P_LANES -- 30w, symbols.yaml data_word.
; Evidence: Bounds 5395-53B9 + 53BA-53D8 + 53D9-53EA + 53EB-541F + 5420-5433 + 5434-5449 + 544A-546A + 546B-5488 + 5489-54A3 (P1-P7c dispatch lanes, all converge F073->54BB; P4/P7b tail-merge 
; ORIGIN 0x546B
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6e4
	cmpm   *(0x573),#-23991
	bc     0x5489,ntc
	andm   #-129,*ar2
	st     #0,*(0xb68)
	call   0xd970
	ld     #1,b
	stl    b,*(0xc4c)
	st     #3,*(0xa5a)
	call   0xb6e6
	call   0xc717
	call   0x9fa8
	ld     *(0x3fc9),a
	b      0x53cd
