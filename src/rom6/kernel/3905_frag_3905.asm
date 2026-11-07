; ROM6 0x3906 FRAG_3905 -- 1w (overlap-corrected wave-12).
; Evidence: Bound 3906 (ret FC00, byte-verified; exit scan clean); entry = fall-through abut from FRAG_38FB [38FB-3905] tail (CODE, ends or-accumulate, no exit). Former leading bare word 0x3905 re-homed to FRAG_38FB (or #0,a operand).
; ORIGIN 0x3906
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @3906 fc00 ret
	ret
