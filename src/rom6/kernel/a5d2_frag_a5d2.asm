; ROM6 0xA5D2 FRAG_A5D2 -- 15w, symbols.yaml data_word.
; Evidence: Bound A5D2-A5E0 (15w; exit RET FC00@A5E0 byte-verified, exit scan clean); post-RET head only (FC00@A5D1 = ROUTINE_A5C6 exit, zero exterior refs — thin entry); HYPOTHESIS.
; ORIGIN 0xA5D2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65a
	cmpm   *(0x262a),#160
	rc     ntc
	ld     *(0x36d),a
	sub    *(0x250d),a
	rc     ageq
	orm    #8,*(0x2639)
	ret
