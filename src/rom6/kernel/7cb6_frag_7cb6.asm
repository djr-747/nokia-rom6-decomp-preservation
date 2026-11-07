; ROM6 0x7CB6 FRAG_7CB6 -- 123w, symbols.yaml data_word.
; Evidence: Bound 7CB6-7D30 (123w; exit RET FC00@7D30 byte-verified); entry bc F830@7C8E->7CB6 byte-verified (cond, exterior pre-head); interior joins bd F273@7CCA->7CF9 in-span (uncond-delaye
; ORIGIN 0x7CB6
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	ld     *(0x264f),a
	bc     0x7d08,aneq
	stm    #9665,ar2
	st     #0,*ar2
	stm    #9702,ar3
	cmpm   *ar3,#176
	bc     0x7cce,ntc
	calld  0x807f
	st     #0,*ar3+
	bd     0x7cf9
	stm    #9717,ar2
	cmpm   *(0x250f),#34
	bc     0x7ce2,ntc
	stm    #9666,ar4
	ld     #769,16,a
	sth    a,*ar4+
	ld     #11009,16,a
	sth    a,*ar4+
	ld     #11051,16,a
	rpt    #8
	sth    a,*ar4+
	ld     #43,16,a
	sth    a,*ar4
	stm    #9680,ar2
	cmpm   *(0x250f),#34
	bc     0x7cee,ntc
	bitf   *(0x51e),#4096
	bc     0x7cf3,ntc
	bitf   *(0x2628),#8
	bc     0x7cfc,ntc
	calld  0x807f
	stm    #9666,ar3
	stm    #9680,ar2
	st     #8,*(0x2631)
	cmpm   *(0x250f),#34
	stm    #10951,ar3
	xc     2,tc
	stm    #11843,ar3
	calld  0x7e88
	stm    #14,ar1
	ld     *(0x2631),a
	bc     0x7d14,agt
	orm    #-32768,*(0x2627)
	st     #15,*(0x2656)
	b      0x7d2c
	ld     *(0x264f),a
	cmpm   *(0x250f),#34
	stm    #10892,ar0
	xc     2,tc
	stm    #11784,ar0
	calld  0x7eb3
	stm    #10884,ar2
	calld  0x7fc6
	stm    #10884,ar2
	orm    #1536,*(0x2a87)
	addm   #-1,*(0x2631)
	calld  0x7c9e
	stm    #9807,ar2
	ret
