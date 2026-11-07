; ROM6 0x795D ROUTINE_795D -- 10w, symbols.yaml data_word.
; Evidence: Bound 795D-7966 (26w; exit retd FE00@7964 + delays E58E/E765 7965-7966 included per convention; exit scan clean); entries call F074@7946 + calld F274@7948/794D/7953->795D byte-veri
; ORIGIN 0x795D
	.sect ".text"
	.mmregs
	.global _start
_start:
	mpy    *ar5,*ar4+0%,a
	mpy    *ar5+,*ar4+0%,b
	mac    *ar5,*ar4+0%,a
	mac    *ar5+,*ar4+0%,b
	mac    *ar5,*ar2,a
	mvdd   *ar2+,*ar4+0%
	mac    *ar5,*ar2,b
	retd
	mvdd   *ar2+,*ar4+0%
	mvmm   ar6,ar5
