; ROM6 0xBA08 FRAG_BA08 -- 34w, symbols.yaml data_word.
; Evidence: Bound BA08-BA29 (34w; exit retd FE00@BA29 byte-verified, delays BA2A-BA2B spill onto FRAG_BA2A head (shared words, coverage-merged — 8AA5 precedent); exit scan otherwise clean); en
; ORIGIN 0xBA08
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #6,*ar1
	bitf   *ar1,#2
	bc     0xba22,ntc
	ld     *(0x2adb),a
	sub    #5,a
	bc     0xba22,aleq
	ld     #10,a
	add    *(0x2adf),a
	sub    *(0x2ae0),a
	bc     0xba22,ageq
	mpy    *(0x2ae9),#22938,a
	sub    *(0x2ae8),16,a
	bc     0xba07,agt
	st     #5,*ar1
	ld     *(0x2afd),a
	rcd    aneq
	stl    b,*(0x2adb)
	retd
