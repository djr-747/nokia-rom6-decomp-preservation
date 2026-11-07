; ROM6 0x8A3A ROUTINE_8A3A -- 11w, symbols.yaml data_word.
; Evidence: Bound 8A3A-8A44 (19w; exit retd FE00@8A42 + delays F0FF/0783 8A43-8A44 included per convention (unusual delay words, flagged); exit scan clean); entries 4x calld F274@8A14/8A1C/8A2
; Pool: interior ADDC-with-carry + RPTBD (both oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0x8A3A
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #29,brc
	rptbd  0x8a41
	sftl   a,-1
	addc   *ar3,b
	sftl   a,-1
	addc   *ar3,b
	retd
	sftl   a,-1
	addc   *ar3,b
