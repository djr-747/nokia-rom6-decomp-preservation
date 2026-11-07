; ROM6 0x7C57 CHECK_DISPATCH_7C57 -- 71w, symbols.yaml data_word.
; Evidence: Entry F074 059E F94C 7D31 7713 2657; first exit ret FC00 @7C9D entry-linear; caller F074 @A4D2 objdump-verified; interior cc 7D31 + bc 810A(existing); HYPOTHESIS. Caller alignment 
; ORIGIN 0x7C57
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	cc     0x7d31,bneq
	stm    #9815,ar3
	st     #10884,*ar3-
	mvdd   *ar2,*ar3
	cmpm   *ar2,#192
	bc     0x810a,tc
	cmpm   *ar2,#177
	bc     0x810a,tc
	cmpm   *ar2,#193
	bc     0x7d74,tc
	cmpm   *ar2,#217
	mvpd   0x6fb,*(0x8)
	bc     0x80fc,tc
	cmpm   *ar2,#213
	mvpd   0x6fa,*(0x8)
	bc     0x80fc,tc
	cmpm   *ar2,#211
	mvpd   0x6fc,*(0x8)
	bc     0x80fc,tc
	cmpm   *ar2,#219
	mvpd   0x6fe,*(0x8)
	bc     0x80fc,tc
	cmpm   *ar2,#112
	bc     0x7ff4,tc
	cmpm   *ar2,#176
	bc     0x7cb6,tc
	cmpm   *ar2,#128
	bc     0x8038,tc
	cmpm   *ar2,#224
	bc     0x80a3,tc
	ld     #4,b
	call   0x4590
	st     #15,*ar3
	ret
