; ROM6 0xE8BD FBACC_E8BD -- 10w (dark-gap wave-13).
; Evidence: Pool: fbacc b (F5E6) with runtime target has no grounded C form. Post-fbacc head; stm; rptz; stl; stl; popm; popm; fbacc @E8C6 (no fall-through). No exterior refs; entry unconfirmed. Recombine-clean.
; ORIGIN 0xE8BD
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #9034,ar1
	rptz   a,#159
	stl    a,*ar1+
	stl    a,*(0x2964)
	popm   bh
	popm   bl
	fbacc  b
