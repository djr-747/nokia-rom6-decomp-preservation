; ROM6 0x5301 DISPATCH_SLED_A -- 53w, symbols.yaml data_word.
; Evidence: Bounds 5282-52C3 + 52F7-5300 + 5301-5335 + 5336-5354 + 5355-5361 + 5362-538C + 538D-5394 (branch- entered sled/merge fragments, zero F074 callers; entries via F820/F84D/F830/FA20/B
; ORIGIN 0x5301
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #9808,ar2
	stm    #9487,ar1
	cmpm   *ar1,#128
	bc     0x5312,tc
	stm    #9807,ar2
	ld     #240,a
	and    *ar1,a
	cmpm   *(0x8),#32
	bc     0x5315,ntc
	ld     *ar2,a
	bc     0x56b9,aneq
	cmpm   *(0x2476),#5
	bc     0x5336,ntc
	stm    #9486,ar2
	stm    #9541,ar3
	rpt    #12
	mvdd   *ar3+,*ar2+
	stm    #9554,ar2
	stm    #9499,ar3
	rpt    #31
	mvdd   *ar2+,*ar3+
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     2,tc
	rpt    #3
	mvdd   *ar2+,*ar3+
	andm   #-9,*(0x2627)
	orm    #128,*(0x2512)
	b      0x56b7
