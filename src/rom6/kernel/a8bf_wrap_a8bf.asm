; ROM6 0xA8BF WRAP_A8BF -- 21w, symbols.yaml data_word.
; Evidence: Entry F074 067C 10F8 2EFD FC45 60F8; bound A8BF-A8D3 (FC00@A8D3); callers F074 @B01B/B088/B0CF (objdump-verified); interior calls 067C + 4BA8@A8CE; HYPOTHESIS audio-adjacent worker
; ORIGIN 0xA8BF
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x67c
	ld     *(0x2efd),a
	rc     aeq
	cmpm   *(0x2510),#192
	bc     0xa8cd,ntc
	cmpm   *(0x2ef5),#0
	rc     ntc
	ld     #0,b
	call   0x4ba8
	st     #0,*(0x2efd)
	ret
