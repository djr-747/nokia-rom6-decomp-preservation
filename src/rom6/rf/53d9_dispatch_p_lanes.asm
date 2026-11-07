; ROM6 0x53D9 DISPATCH_P_LANES -- 18w, symbols.yaml data_word.
; Evidence: Bounds 5395-53B9 + 53BA-53D8 + 53D9-53EA + 53EB-541F + 5420-5433 + 5434-5449 + 544A-546A + 546B-5488 + 5489-54A3 (P1-P7c dispatch lanes, all converge F073->54BB; P4/P7b tail-merge 
; ORIGIN 0x53D9
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x672
	fcall  0x1a7f8
	fcall  0x1a7f1
	call   0xb6e6
	call   0xc717
	call   0x9fa8
	ld     *(0x3fc8),a
	call   0x54a4
	b      0x54bb
