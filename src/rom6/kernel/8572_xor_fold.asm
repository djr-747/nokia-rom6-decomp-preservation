; ROM6 0x8572 XOR_FOLD_8572 -- 5w leaf, trace-corroborated Wave-18.
; ORIGIN 0x8572
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld #0,a
	xor *ar2,a
	xor *ar3+,a
	stl a,*ar2+
	ret
