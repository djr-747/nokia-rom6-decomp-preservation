; ROM6 0x4439 DISPATCH_TARGET_A -- 11w, symbols.yaml data_word.
; Evidence: Entry 4913: ldm ar3,b with sub-gate lanes; first-RET FC00 @4443; table-4433 arm; HYPOTHESIS.
; ORIGIN 0x4439
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar3,b
	sub    #1274,b
	bc     0x4442,bgt
	ldm    ar3,b
	sub    #1263,b
	rc     bgeq
	mvdd   *ar4+,*ar3+
	ret
