; ROM6 0x95A2 FRAG_95A2 -- 8w, symbols.yaml data_word.
; Evidence: Bound 95A2-95A9 (8w; exit BACC F5E2@95A9 byte-verified bacc-b); FOUR entries byte-verified: B F073@955D/958F->95A2 + bc F820@955F/9593->95A2 (uncond + cond pair, mid-shape zone); i
; Pool: BACC computed jump (target = B, oracle-unbound dispatch); stays .asm, bytes verified.
; ORIGIN 0x95A2
	.sect ".text"
	.mmregs
	.global _start
_start:
	add    #-19450,a
	stlm   a,ar1
	mvdm   0x21fa,ar4
	ld     *ar1,b
	ldm    ar3,a
	bacc   b
