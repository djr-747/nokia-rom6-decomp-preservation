; ROM6 0x80F3 LEAF9_80F3 -- 8w, symbols.yaml data_word.
; Evidence: Entry 1282 771A 000F F072 80F9 F490 F591 8182; RET @80FB len 9; 4 callers 80AF/80B1/80CC/80CE; no inner calls; HYPOTHESIS. Head-fill Bound 80F3-80FA (wave-5: no-exit, falls into 80
; Pool: ROR/ROL rotates (oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0x80F3
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldu    *ar2,a
	stm    #15,brc
	rptb   0x80f9
	ror    a
	rol    b
	stl    b,*ar2
