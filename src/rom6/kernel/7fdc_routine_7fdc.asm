; ROM6 0x7FDC ROUTINE_7FDC -- 24w, symbols.yaml data_word.
; Evidence: Bound 7FDC-7FF3 (24w; exit RET FC00@7FF3 byte-verified, exit scan clean); entries calld F274@4C19/ 4D60->7FDC byte-verified (CODE) + calld@8056/80EE->7FDC (upgraded to CODE — sourc
; Pool: ROL rotates + BANZD loop (rotate family oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0x7FDC
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	stm    #2,bk
	stm    #96,ar4
	stm    #97,ar5
	calld  0x7ea7
	stm    #31,brc
	rptb   0x7fed
	ld     *ar5,16,a
	rol    a
	sth    a,*ar5+%
	rol    b
	banzd  0x7fe4,*ar1-
	sth    b,*ar3-
	stl    b,*ar3-
	mar    *ar3+
	ret
