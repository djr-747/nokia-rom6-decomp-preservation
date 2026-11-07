; ROM6 0xA687 SUB_A687 -- 39w, symbols.yaml data_word.
; Evidence: Entry F074 065E; bound A687-A6AD; interior AB2C @A692 + BA56 @A69F + B750 @A6A8 (ccd @A6DB STRUCK per critic: belongs to A6AE only); zero inbound + post-retd A684+2; OVERLAP interi
; ORIGIN 0xA687
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65e
	cmpm   *(0x2510),#193
	rc     ntc
	stm    #1308,ar2
	bitf   *ar2,#3
	rc     tc
	call   0xab2c
	ld     *(0x51c),a
	and    #3072,a
	sub    #2048,a
	rc     aeq
	st     #12854,*(0x337c)
	ld     #95,a
	call   0xba56
	st     #12854,*(0x337d)
	mvkd   0x54a,*(0x337b)
	ld     #95,a
	call   0xb750
	orm    #-32768,*(0x2aff)
	ret
