; ROM6 0xE049 RPTBD_FIR_C -- 33w, symbols.yaml data_word.
; Evidence: Entry E746 E725 F272 E068 1192 6D8C B239 B886 x8; first-RET @E069 (33w); post-RET head, no callers listed; HYPOTHESIS.
; ORIGIN 0xE049
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar4,ar6
	mvmm   ar2,ar5
	rptbd  0xe068
	ld     *ar2+,b
	mar    *ar4-
	mac    *ar5,*ar3+,b,a
	mas    *ar2+,*ar4-,a
	mas    *ar2+,*ar4-,a
	mas    *ar2+,*ar4-,a
	mas    *ar2+,*ar4-,a
	mas    *ar2+,*ar4-,a
	mas    *ar2+,*ar4-,a
	mas    *ar2+,*ar4-,a
	mas    *ar2+,*ar4-,a
	mas    *ar2+,*ar4-,a
	mas    *ar2,*ar4+,a
	sfta   a,3
	sth    a,*ar6+
	mac    *ar5,*ar3+,b,a
	mas    *ar2-,*ar4+,a
	mas    *ar2-,*ar4+,a
	mas    *ar2-,*ar4+,a
	mas    *ar2-,*ar4+,a
	mas    *ar2-,*ar4+,a
	mas    *ar2-,*ar4+,a
	mas    *ar2-,*ar4+,a
	mas    *ar2-,*ar4+,a
	mas    *ar2-,*ar4+,a
	mas    *ar2,*ar4+,a
	sfta   a,3
	sth    a,*ar6+
	ret
