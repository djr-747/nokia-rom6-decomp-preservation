; ROM6 0x436C ROUTINE_436C -- 24w, symbols.yaml data_word.
; Evidence: Bound 436C-4383 (24w; exit RET FC00@4383 byte-verified, exit scan clean); entries sibling-only call@4362/calld@4366->436C (from ROUTINE_434F interior, chained-frag edge) + post-RET
; Pool: ROR rotate + ADDC carry + BANZD loop (rotate/carry oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0x436C
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #15,brc
	ldu    *ar2,a
	rptb   0x437e
	cmpm   *(0x10),#1023
	ror    a
	mar    *ar0+
	bc     0x437a,ntc
	stm    #0,ar0
	xc     2,c
	mvkd   0x10,*ar3+
	addc   *(0xe),b
	banzd  0x436c,*ar7-
	mar    *ar2-
	nop
	ret
