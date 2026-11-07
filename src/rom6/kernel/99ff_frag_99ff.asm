; ROM6 0x99FF FRAG_99FF -- 18w, symbols.yaml data_word.
; Evidence: Bound 99FF-9A10 (18w; exit FC00@9A10 byte-verified); entry BCD FA45@99F4->99FF (FA45 = BCD- conditional per catalog mask, valid branch-entry class); abuts MSG_VERIFY_LOOP tail (no 
; ORIGIN 0x99FF
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar1,ar2
	addm   #-1,*(0x20fe)
	ldu    *ar2+%,a
	stlm   a,ar3
	ldu    *ar2+%,a
	ldu    *ar2+%,b
	stlm   b,ar5
	ldu    *ar2,b
	sftl   b,-8
	and    #255,b
	stlm   b,ar1
	ldm    ar5,b
	sub    #1,b
	ret
