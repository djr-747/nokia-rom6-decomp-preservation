; ROM6 0x3802 FRAG_3802 -- 4w, symbols.yaml data_word.
; Evidence: Bound 3802-3805 (4w micro-arm: out-call F074 8413@3802 + exit B F073@3804->37DF + operand 3805, byte-verified; exit scan clean); entry bc F84D@37F2->3802 byte-verified (cond beq, e
; ORIGIN 0x3802
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x8413
	b      0x37df
