; ROM6 0x3267 FRAG_3267 -- 12w, symbols.yaml data_word.
; Evidence: Bound 3267-3272 (12w, exit F073@3271->2E64 + operand 3272; TRIMMED from 3267-32ED: second outside early-out F073@32B2->2E64); post-ret head (orphan FC00@3266 after WORKER_3199 ends
; ORIGIN 0x3267
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldu    *ar2+%,a
	ld     #12,b
	call   0x4007
	stl    a,*(0x581)
	stl    a,*(0x582)
	call   0x2e2f
	b      0x2e64
