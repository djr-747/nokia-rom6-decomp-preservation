; ROM6 0x45FA FRAG_45FA -- 5w, symbols.yaml data_word.
; Evidence: Bound 45FA-45FE (5w; exit RET FC00@45FE byte-verified, first and only unconditional exit-class; exit scan clean); entry = post-RET head (RET@45F9 = FRAG_45C2 [45C2-45F9] exit, CODE
; ORIGIN 0x45FA
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6f4
	call   0x2e2f
	ret
