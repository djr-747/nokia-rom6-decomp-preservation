; ROM6 0x5434 DISPATCH_P_LANES -- 22w, symbols.yaml data_word.
; Evidence: Bounds 5395-53B9 + 53BA-53D8 + 53D9-53EA + 53EB-541F + 5420-5433 + 5434-5449 + 544A-546A + 546B-5488 + 5489-54A3 (P1-P7c dispatch lanes, all converge F073->54BB; P4/P7b tail-merge 
; ORIGIN 0x5434
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6e4
	cmpm   *(0x573),#-23991
	bc     0x5446,tc
	stm    #631,brc
	ld     #0,a
	rptbd  0x5442
	stm    #11264,ar1
	stl    a,*ar1+
	ld     #4,b
	call   0xb4a8
	call   0xc717
	b      0x54bb
