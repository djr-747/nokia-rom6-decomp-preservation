; ROM6 0x5362 DISPATCH_SLED_A -- 43w, symbols.yaml data_word.
; Evidence: Bounds 5282-52C3 + 52F7-5300 + 5301-5335 + 5336-5354 + 5355-5361 + 5362-538C + 538D-5394 (branch- entered sled/merge fragments, zero F074 callers; entries via F820/F84D/F830/FA20/B
; ORIGIN 0x5362
	.sect ".text"
	.mmregs
	.global _start
_start:
	ssbx   st1,intm
	portr  2,*(0x8)
	orm    #128,*(0x8)
	nop
	portw  *(0x8),2
	rsbx   st1,intm
	andm   #-29,*(0x552)
	call   0x6e8
	ld     #240,a
	and    *(0x2547),a
	cmpm   *(0x8),#192
	ld     #3,a
	and    *(0x2547),a
	sfta   a,1
	xc     1,ntc
	ld     #4,a
	ld     #240,b
	and    *(0x2510),b
	cmpm   *(0xb),#192
	bc     0x538a,tc
	st     #-23991,*(0x573)
	add    #21389,a
	bacc   a
