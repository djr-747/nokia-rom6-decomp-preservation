; ROM6 0xE4CB BLK_E4CB -- 18w, symbols.yaml data_word.
; Evidence: Post-RET head; first-RET @E4DC (18w); no callers listed; HYPOTHESIS.
; ORIGIN 0xE4CB
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #9,brc
	rptbd  0xe4db
	ld     #-1252,b
	add    *ar2,-8,b,a
	stlm   a,ar4
	ld     #255,a
	and    *ar2+,a
	stlm   a,t
	ld     *ar4-,16,a
	sub    *ar4,16,a
	mpya   a
	add    *ar4,9,a
	sth    a,7,*ar3+
	ret
