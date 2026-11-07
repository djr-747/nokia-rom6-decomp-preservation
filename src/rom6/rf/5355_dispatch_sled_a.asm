; ROM6 0x5355 DISPATCH_SLED_A -- 13w, symbols.yaml data_word.
; Evidence: Bounds 5282-52C3 + 52F7-5300 + 5301-5335 + 5336-5354 + 5355-5361 + 5362-538C + 538D-5394 (branch- entered sled/merge fragments, zero F074 callers; entries via F820/F84D/F830/FA20/B
; ORIGIN 0x5355
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2,b
	call   0x580b
	bc     0x5362,ntc
	ld     *(0x250f),b
	call   0x580b
	cc     0x84cf,ntc
	b      0x5371
