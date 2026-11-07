; ROM6 0xDB4A MAC_RPTBD_DB4A -- 19w, symbols.yaml data_word.
; Evidence: Entry 770E 1249 771A 0009 2092 F272 DB5B; caller F274 calld @D670 verified; first exit ret FC00 @DB5C; bound DB4A-DB5C (task-parenthetical retd DBC0 rejected: crosses ret DB5C + ex
; ORIGIN 0xDB4A
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #4681,t
	stm    #9,brc
	mpy    *ar2+,a
	rptbd  0xdb5b
	stm    #10,ar0
	mac    *ar3+0,a
	mac    *ar3+0,a
	mac    *ar3+0,a
	mac    *ar3+0,a
	mac    *ar3+0,a
	macr   *ar3+0,a
	st     a,*ar4+ || mpy    *ar2+,a
	mar    *+ar3(0xffc5)
	ret
