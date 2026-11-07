; ROM6 0x80FB LEAF9_80F3 -- 1w (overlap-split wave-12).
; Evidence: RET FC00 @0x80FB (prior-span fall-through return abut; 80F3 head-fill falls into it). Former tail (call 059E/stlm/calld 2282/stm/bc) duplicated the 80fc_sub_80fc span head word-for-word (owned there, C-verified). Recombine-clean.
; ORIGIN 0x80FB
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
