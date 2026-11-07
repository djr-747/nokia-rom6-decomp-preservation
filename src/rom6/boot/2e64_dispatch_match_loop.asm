; ROM6 0x2E64 DISPATCH_MATCH_LOOP -- 32w, symbols.yaml program_word.
; Evidence: Match loop, not an epilogue. Every clause converges here with B 0x2E64 for re-match. Wave-7: referenced from uploaded code (block01 + block30 ROM-xref targets) — exterior callers e
; ORIGIN 0x2E64
	.sect ".text"
	.global _start
_start:
	call   0x5a0
	bitf   *(0x54d),#4
	bc     0x2e8f,ntc
	call   0x942e
	rc     aeq
	stlm   b,ar4
	and    #255,a
	xor    #244,a
	rc     aneq
	mar    *ar4-
	ldu    *ar2,a
	sftl   a,-8,b
	xor    #5,b
	bc     0x2e84,beq
	sftl   a,-8,b
	xor    #0,b
	rc     bneq
	and    #255,a
	stl    a,*(0x54d)
	ret
