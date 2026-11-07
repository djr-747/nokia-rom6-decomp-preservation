; ROM6 0xA4D5 MSG_SETUP_B -- 9w, symbols.yaml data_word.
; Evidence: Entry F074 0658 7712 262B 1082 FC45; exits: rc FC45 (aeq) @A4DA + ret FC00 @A4DD (true end A4DD span 9 kept; head-rc exit new per all-paths walk); 5 callers B18A B1F5 B227 B276 B31
; ORIGIN 0xA4D5
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x658
	stm    #9771,ar2
	ld     *ar2,a
	rc     aeq
	call   0x4944
	ret
