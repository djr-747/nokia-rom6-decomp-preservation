; ROM6 0x8B9D ROUTINE_8B9D -- 54w, symbols.yaml data_word.
; Evidence: Bound 8B9D-8BD2 (exit retd FE00@8BD0 + slots 8BD1-8BD2); 4x F274 call entries @8B51->8B9D + @8B69/83/98->8B9E (mid-entry overlap: single symbol only; 8B9D=4494 prefix falls into 8B
; ORIGIN 0x8B9D
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar4+,16,a
	stm    #12072,ar3
	ld     *ar3-,t
	rptbd  0x8bce
	stm    #4359,ar2
	mpyr   *ar2,b
	sub    b,a
	ld     *ar2+,16,b
	macar  t,b
	st     b,*ar2+0% || ld     *ar3-,t
	mpyr   *ar2,b
	sub    b,a
	ld     *ar2+,16,b
	macar  t,b
	st     b,*ar2+0% || ld     *ar3-,t
	mpyr   *ar2,b
	sub    b,a
	ld     *ar2+,16,b
	macar  t,b
	st     b,*ar2+0% || ld     *ar3-,t
	mpyr   *ar2,b
	sub    b,a
	ld     *ar2+,16,b
	macar  t,b
	st     b,*ar2+0% || ld     *ar3-,t
	mpyr   *ar2,b
	sub    b,a
	ld     *ar2+,16,b
	macar  t,b
	st     b,*ar2+0% || ld     *ar3-,t
	mpyr   *ar2,b
	sub    b,a
	ld     *ar2+,16,b
	macar  t,b
	st     b,*ar2+0% || ld     *ar3-,t
	mpyr   *ar2,b
	sub    b,a
	ld     *ar2+,16,b
	macar  t,b
	st     b,*ar2+0% || ld     *ar3+0%,t
	mpyr   *ar2,b
	sub    b,a
	ld     *ar2+,16,b
	macar  t,b
	st     b,*ar2- || ld     *ar3-,t
	sth    a,*ar2+0%
	st     a,*ar4 || ld     *ar4+,a
	sth    a,0x2c
	retd
	stm    #12432,ar2
