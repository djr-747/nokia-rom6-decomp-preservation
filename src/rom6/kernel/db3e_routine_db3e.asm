; ROM6 0xDB3E ROUTINE_DB3E -- 12w, symbols.yaml data_word.
; Evidence: Bound DB3E-DB49 (12w; exit RET FC00@DB49 byte-verified, exit scan clean); entries 3x calld F274@ D776/DDD2/DEF8->DB3E byte-verified head-exact + post-RET head (FC00@DB3D); HYPOTHES
; ORIGIN 0xDB3E
	.sect ".text"
	.mmregs
	.global _start
_start:
	rpt    #59
	mvdd   *ar5-,*ar4-
	stm    #9,brc
	rptbd  0xdb48
	stm    #-1,t
	ld     *ar2+,ts,a
	add    *ar3+,ts,a
	stl    a,*ar6+
	ret
