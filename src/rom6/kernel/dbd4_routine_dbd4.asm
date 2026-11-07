; ROM6 0xDBD4 ROUTINE_DBD4 -- 6w, symbols.yaml data_word.
; Evidence: Bound DBD4-DBD9 (6w; exit RET FC00@DBD9 byte-verified, exit scan clean; micro-routine); entries calld F274@DD01->DBD4 byte-verified head-exact (from FRAG_DCE6 [DCE6-DD39] interior,
; ORIGIN 0xDBD4
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1136,t
	mpya   b
	rpt    #27
	mac    *ar2+,b
	ret
