; ROM6 0x7167 TSWEEP_MPYU_PROBE -- 60w, symbols.yaml data_word.
; Evidence: Entry F074 05B4; bound 7167-71A2; callers 6CA9/6CAE(d)/6CD5; stm T=33..2097 + mpyu/sfta/sub ageq lane; HYPOTHESIS.
; ORIGIN 0x7167
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b4
	ld     #0,b
	stm    #33,t
	mpyu   *ar3-,a
	sfta   a,2
	sub    *ar3+,16,a
	rc     ageq
	add    #1,b
	stm    #66,t
	mpyu   *ar3-,a
	sfta   a,2
	sub    *ar3+,16,a
	rc     ageq
	add    #1,b
	stm    #131,t
	mpyu   *ar3-,a
	sfta   a,2
	sub    *ar3+,16,a
	rc     ageq
	add    #1,b
	stm    #262,t
	mpyu   *ar3-,a
	sfta   a,2
	sub    *ar3+,16,a
	rc     ageq
	add    #1,b
	stm    #524,t
	mpyu   *ar3-,a
	sfta   a,2
	sub    *ar3+,16,a
	rc     ageq
	add    #1,b
	stm    #1049,t
	mpyu   *ar3-,a
	sfta   a,2
	sub    *ar3+,16,a
	rc     ageq
	add    #1,b
	stm    #2097,t
	mpyu   *ar3-,a
	sfta   a,2
	sub    *ar3+,16,a
	rc     ageq
	add    #1,b
	ret
