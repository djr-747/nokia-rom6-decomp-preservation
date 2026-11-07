; ROM6 0xA3E1 ROUTINE_A3E1 -- 15w, symbols.yaml data_word.
; Evidence: Bound A3E1-A3EF (exit RET FC00@A3EF objdump); callers 7x F074 @AFC8/B136/B17F/B1EF/B221/B270/B30C; interior calls 0656/AB82 + rc aeq; abuts MEASUREMENT_A3F0; HYPOTHESIS.
; ORIGIN 0xA3E1
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x656
	ld     *(0x262a),a
	rc     aeq
	mvdm   0x2628,ar2
	ld     *(0x2659),b
	andm   #1024,*(0x12)
	call   0xab82
	ret
