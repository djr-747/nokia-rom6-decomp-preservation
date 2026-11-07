; ROM6 0xE795 FBACC_E795 -- 8w (dark-gap wave-13).
; Evidence: Pool: fbacc a (F4E6) with runtime target has no grounded C form (5C4F cala rule). Post-fbacc head; calls 5AE/2C88; popm/popm; fbacc; ret @E79C. No exterior refs; entry unconfirmed. Recombine-clean.
; ORIGIN 0xE795
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5ae
	call   0x2c88
	popm   ah
	popm   al
	fbacc  a
	ret
