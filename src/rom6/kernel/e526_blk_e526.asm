; ROM6 0xE526 BLK_E526 -- 12w, symbols.yaml data_word.
; Evidence: Post-RET head; BOUND CORRECTED entry-linear: straight-line to first exit retd @0xE52F, bound E526-E531 (incl delay); was E54A (overclaim); no callers listed; HYPOTHESIS.
; Pool: RPTBD + SACCD conditional-MAC + dual-dest SUB (all oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0xE526
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #8,brc
	rptbd  0xe52e
	sth    a,*ar5
	sub    *ar2,16,a,b
	saccd  a,*ar2,bgt
	add    *ar5,*ar2+,a
	sub    *ar2,16,a,b
	retd
	nop
	saccd  a,*ar2,bgt
