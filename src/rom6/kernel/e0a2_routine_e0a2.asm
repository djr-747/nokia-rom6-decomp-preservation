; ROM6 0xE0A2 ROUTINE_E0A2 -- 19w, symbols.yaml data_word.
; Evidence: Bound E0A2-E0B4 (27w; exit retd FE00@E0B2 + delays E0B3-E0B4 (B04D B4AF) included per convention; exit scan clean); entries 2x calld F274@E1FB/E20C->E0A2 byte-verified head-exact (
; ORIGIN 0xE0A2
	.sect ".text"
	.mmregs
	.global _start
_start:
	add    #-1005,a,b
	stlm   b,ar3
	sub    a,1,b
	stlm   b,ar5
	mvmm   ar2,ar4
	xc     1,alt
	add    *ar2-,*ar3+0%,b
	xc     1,ageq
	add    *ar4+,*ar5+0%,b
	mpy    *ar2-,*ar3+0%,a
	mac    *ar4+,*ar5+0%,a
	mac    *ar2-,*ar3+0%,a
	mac    *ar4+,*ar5+0%,a
	mac    *ar2-,*ar3+0%,a
	mac    *ar4+,*ar5+0%,a
	retd
	mac    *ar2-,*ar3+0%,a
	macr   *ar4+,*ar5+0%,a
