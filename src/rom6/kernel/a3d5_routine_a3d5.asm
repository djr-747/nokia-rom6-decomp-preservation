; ROM6 0xA3D5 ROUTINE_A3D5 -- 12w, symbols.yaml data_word.
; Evidence: Bound A3D5-A3E0 (exit retd FE00@A3DE + slots A3DF-A3E0 objdump); callers F074 @A3C5/@A3CE/@B35A; interior call 0654 + rc aeq early-return; HYPOTHESIS.
; ORIGIN 0xA3D5
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x654
	ld     *(0x262a),a
	or     *(0x262b),a
	rc     aeq
	ld     *(0x2512),a
	retd
	and    #512,a
