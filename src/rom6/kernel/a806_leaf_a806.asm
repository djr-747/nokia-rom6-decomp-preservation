; ROM6 0xA806 LEAF_A806 -- 15w, symbols.yaml data_word.
; Evidence: Entry F074 0660; bound A806-A814 ret (rc @A810 passed per ret/retd-only rule); zero interior calls; zero inbound + post-RET A805; HYPOTHESIS.
; ORIGIN 0xA806
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x660
	ld     *(0x565),a
	sub    *(0x915),a
	rc     aneq
	bitf   *(0x2629),#4096
	rc     ntc
	mvdk   *(0x22b),0x38a
	ret
