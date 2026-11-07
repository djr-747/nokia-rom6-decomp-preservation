; ROM6 0x2282 SUB_2282 -- 7w, symbols.yaml program_word.
; Evidence: Exterior calld x5 + in-gap calls; ST1-based T preset (ld/sub/stlm) with retd-delay bitt TC-out; no other entries, evidenced, flagged.
; ORIGIN 0x2282
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld #15,a
	sub *(0x12),a
	stlm a,t
	retd
	bitt *(0x537)
