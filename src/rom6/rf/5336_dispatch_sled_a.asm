; ROM6 0x5336 DISPATCH_SLED_A -- 31w, symbols.yaml data_word.
; Evidence: Bounds 5282-52C3 + 52F7-5300 + 5301-5335 + 5336-5354 + 5355-5361 + 5362-538C + 538D-5394 (branch- entered sled/merge fragments, zero F074 callers; entries via F820/F84D/F830/FA20/B
; ORIGIN 0x5336
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #176,*(0x56f)
	stm    #9788,ar1
	ld     #32,a
	stl    a,*ar1+
	stl    a,*ar1
	cmpm   *(0x250f),#48
	bcd    0x5355,ntc
	stm    #9542,ar2
	cmpm   *ar2,#80
	bc     0x5355,ntc
	st     #1,*(0x574)
	st     #81,*ar2
	andm   #-17,*(0x2549)
	st     #8,*ar1
	b      0x5371
