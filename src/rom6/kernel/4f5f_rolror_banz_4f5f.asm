; ROM6 0x4F5F ROLROR_BANZ_4F5F -- 15w, symbols.yaml data_word.
; Evidence: Entry F074 059C E800 771A 000F F072 4F68; bound 4F5F-4F6D; callers calld@4E91(word- verified)/4EB7(objdump); rptb rol/ror/banz leaf; HYPOTHESIS.
; Pool: ROL/ROR-through-carry + BANZ loop (rotate/carry oracle-unbound; same class as the 436C/4839 ROR notes); stays .asm, bytes verified.
; ORIGIN 0x4F5F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	ld     #0,a
	stm    #15,brc
	rptb   0x4f68
	ld     *ar2+,16,b
	rol    b
	ror    a
	sth    a,*ar3+
	banz   0x4f62,*ar1-
	mar    *ar3-
	ret
