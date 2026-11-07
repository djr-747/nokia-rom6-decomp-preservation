; ROM6 0xC851 STATE_WORKER -- 12w, symbols.yaml program_word.
; Evidence: Mini-kernel call, 0x20F4/0x51C flag setup, pa0 strobe, worker call. EXIT CORRECTED -- word at 0xC85C is E900 (ld #0,b), NOT a RET; no FC00 in 0xC851-0xC85C, routine falls through i
; ORIGIN 0xC851
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5ea
	andm   #-3073,*(0x51c)
	andm   #-1792,*(0x20f4)
	orm    #2,*(0x20f4)
	ld     #0,b
