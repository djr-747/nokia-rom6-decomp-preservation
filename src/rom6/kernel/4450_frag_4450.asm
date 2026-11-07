; ROM6 0x4450 FRAG_4450 -- 3w, symbols.yaml data_word.
; Evidence: Bound 4450-4452 (3w micro: mvdp 2w + RET FC00@4452, byte-verified; exit scan clean); entry = post-RET head (RET@444F = DISPATCH_TARGET_B [4444-444F] exit, CODE); abuts DISPATCH_TAR
; ORIGIN 0x4450
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdp   *ar4+,0x4500
	ret
