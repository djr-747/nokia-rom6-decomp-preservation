; ROM6 0xD95F ROUTINE_D95F -- 17w, symbols.yaml data_word.
; Evidence: Bound D95F-D96F (17w; exit retd FE00@D96D + delays D96E-D96F included per convention; exit scan clean); entries 2x calld F274@D91B/D953->D95F byte-verified head-exact + post-RET he
; ORIGIN 0xD95F
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,b
	rptbd  0xd965
	stm    #-936,ar3
	sub    *ar2+,*ar3+,a
	or     a,b
	ld     *(0xb68),a
	and    #-3,a
	xc     2,beq
	or     #2,a
	retd
	stl    a,*(0xb68)
