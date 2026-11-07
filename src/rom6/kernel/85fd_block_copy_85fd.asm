; ROM6 0x85FD BLOCK_COPY_85FD -- 20w, symbols.yaml data_word.
; Evidence: Entry E742 EC05 7194 30D0 7712 30D0; first exit ret FC00 @8610 abutting existing 8611; callers F074 @8552/8559 verified; HYPOTHESIS.
; Pool: ROR/ROL rotates + self-BANZ (rotate family oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0x85FD
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar4,ar2
	rpt    #5
	mvdk   *ar4+,0x30d0
	stm    #12496,ar2
	stm    #5,ar3
	ld     *ar2+,a
	stm    #15,brc
	rptb   0x860b
	ror    a
	rol    b
	mar    *ar4-
	stl    b,*ar4
	banz   0x8605,*ar3-
	ret
