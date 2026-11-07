; ROM6 0x3775 FRAG_3775 -- 4w, symbols.yaml data_word.
; Evidence: Bound 3775-3778 (4w micro-arm: out-call F074 2E2F@3775 + exit B F073@3777->2E64 + operand 3778, byte-verified; exit scan clean); entry bc F820@3761->3775 byte-verified (chained fro
; ORIGIN 0x3775
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x2e2f
	b      0x2e64
