; ROM6 0x52F7 DISPATCH_SLED_A -- 10w, symbols.yaml data_word.
; Evidence: Bounds 5282-52C3 + 52F7-5300 + 5301-5335 + 5336-5354 + 5355-5361 + 5362-538C + 538D-5394 (branch- entered sled/merge fragments, zero F074 callers; entries via F820/F84D/F830/FA20/B
; ORIGIN 0x52F7
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #9337,ar1
	ldu    *ar1,b
	bc     0x5301,beq
	sub    #1,b
	stl    b,*ar1
	b      0x56b9
