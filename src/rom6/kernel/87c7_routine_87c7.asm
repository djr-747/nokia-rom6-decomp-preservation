; ROM6 0x87C7 ROUTINE_87C7 -- 12w, symbols.yaml data_word.
; Evidence: Bound 87C7-87D2 (12w; exit RET FC00@87D2 byte-verified, exit scan clean); entries 2x calld F274@87A7/87B1->87C7 byte-verified + post-RET head (FC00@87C6 = FRAG_87C3 exit); abuts FR
; Pool: ROLTC rotate-with-carry + BITT T-test (both oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0x87C7
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,a
	rptb   0x87d1
	ldm    ar4,b
	add    *ar1,-8,b
	stlm   b,ar2
	ld     *ar1+,t
	nop
	bitt   *ar2
	roltc  a
	ret
