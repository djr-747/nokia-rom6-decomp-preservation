; ROM6 0x9118 BUTTERFLY_9146 -- 46w, symbols.yaml data_word.
; Evidence: Entry 7712 3138 4497; sth/neg ladder + mvdd block; RET @918B len 70; 1x F074 @90EC; HYPOTHESIS. Head Bound 9118-9145 (wave-5: exit FC00@9145 byte-verified; 2 F074 callers @90BC/90D
; ORIGIN 0x9118
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #13384,ar2
	ld     *ar7+,16,a
	sub    *ar7,16,a,b
	sth    b,*ar2-
	neg    b
	sth    b,*ar2
	add    *ar7+,16,a
	neg    a,b
	pshm   ar5
	stm    #12576,ar5
	sth    a,*ar5+
	mvdd   *ar2+,*ar5+
	mvdd   *ar2,*ar5+
	sth    b,*ar5+
	sth    b,*ar5+
	mvdd   *ar2-,*ar5+
	mvdd   *ar2+,*ar5+
	sth    a,*ar5+
	sth    b,*ar5+
	mvdd   *ar2-,*ar5+
	mvdd   *ar2,*ar5+
	sth    a,*ar5+
	sth    a,*ar5+
	mvdd   *ar2+,*ar5+
	mvdd   *ar2,*ar5+
	sth    b,*ar5+
	mvdd   *ar2-,*ar5+
	sth    b,*ar5+
	sth    a,*ar5+
	mvdd   *ar2,*ar5+
	mvdd   *ar2+,*ar5+
	sth    a,*ar5+
	sth    b,*ar5+
	mvdd   *ar2-,*ar5+
	mvdd   *ar2+,*ar5+
	sth    a,*ar5+
	sth    b,*ar5+
	mvdd   *ar2,*ar5+
	mvdd   *ar2-,*ar5+
	sth    b,*ar5+
	sth    a,*ar5+
	mvdd   *ar2,*ar5+
	popm   ar5
	ret
