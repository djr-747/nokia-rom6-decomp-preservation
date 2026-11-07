; ROM6 0x9A50 ROUTINE_9A50 -- 32w, symbols.yaml data_word.
; Evidence: Bound 9A50-9A6F (32w; exit RET FC00@9A6F byte-verified; exit scan clean); entries 2x calld F274@944B/9453->9A50 byte-verified (from COBBA_VERIFY_LOOP [942E-9452] interior, CODE) — 
; ORIGIN 0x9A50
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5d2
	stm    #8446,ar3
	ld     *ar3,a
	rc     aleq
	ld     *(0x2202),a
	bc     0x9a82,aneq
	bitf   *(0x20ff),#512
	bc     0x9a70,ntc
	ld     *ar3,a
	sub    #95,a
	bc     0x9a82,ageq
	bitf   *(0x20ff),#32
	bc     0x9a82,tc
	ldu    *(0x20fb),a
	sub    #3,a
	bc     0x9a82,ageq
	ret
