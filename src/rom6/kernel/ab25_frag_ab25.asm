; ROM6 0xAB25 FRAG_AB25 -- 7w, symbols.yaml data_word.
; Evidence: Bound AB25-AB2B (7w; exit RETD FE00@AB29 + delays AB2A-AB2B (add 2w), byte-verified; exit scan clean); entry bc F84x@AB1F->AB25 byte-verified (cond alt, exterior from SEQ_AAC7 [AAC
; ORIGIN 0xAB25
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #11264,16,b,a
	rc     ageq
	ld     a,b
	retd
	add    #11896,16,b
