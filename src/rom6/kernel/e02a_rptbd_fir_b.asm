; ROM6 0xE02A RPTBD_FIR_B -- 31w, symbols.yaml data_word.
; Evidence: Entry F272 E047 1182 F495 B285 B085 x8; first-RET @E048 (31w); post-RET head, no callers listed; HYPOTHESIS.
; ORIGIN 0xE02A
	.sect ".text"
	.mmregs
	.global _start
_start:
	rptbd  0xe047
	ld     *ar2,b
	nop
	mac    *ar2+,*ar3-,b,a
	mac    *ar2+,*ar3-,a
	mac    *ar2+,*ar3-,a
	mac    *ar2+,*ar3-,a
	mac    *ar2+,*ar3-,a
	mac    *ar2+,*ar3-,a
	mac    *ar2+,*ar3-,a
	mac    *ar2+,*ar3-,a
	mac    *ar2+,*ar3-,a
	mac    *ar2+,*ar3-,a
	mac    *ar2,*ar3+,a
	sfta   a,3
	sth    a,*ar4+
	mac    *ar2-,*ar3+,b,a
	mac    *ar2-,*ar3+,a
	mac    *ar2-,*ar3+,a
	mac    *ar2-,*ar3+,a
	mac    *ar2-,*ar3+,a
	mac    *ar2-,*ar3+,a
	mac    *ar2-,*ar3+,a
	mac    *ar2-,*ar3+,a
	mac    *ar2-,*ar3+,a
	mac    *ar2-,*ar3+,a
	mac    *ar2,*ar3+,a
	sfta   a,3
	sth    a,*ar4+
	ret
